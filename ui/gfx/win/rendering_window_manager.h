// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_WIN_RENDERING_WINDOW_MANAGER_H_
#define UI_GFX_WIN_RENDERING_WINDOW_MANAGER_H_

#include <windows.h>

#include <map>

#include "base/synchronization/lock.h"
#include "ui/gfx/gfx_export.h"

namespace base {
template <typename T>
struct DefaultSingletonTraits;
}

namespace gfx {

// This keeps track of whether a given HWND has a child window which the GPU
// process renders into.
class GFX_EXPORT RenderingWindowManager {
 public:
  static RenderingWindowManager* GetInstance();

  void RegisterParent(HWND parent);
  bool RegisterChild(HWND parent, HWND child_window);
  void DoSetParentOnChild(HWND parent);
  void UnregisterParent(HWND parent);
  bool HasValidChildWindow(HWND parent);

 private:
  friend struct base::DefaultSingletonTraits<RenderingWindowManager>;

  RenderingWindowManager();
  ~RenderingWindowManager();

  base::Lock lock_;
  std::map<HWND, HWND> info_;

  DISALLOW_COPY_AND_ASSIGN(RenderingWindowManager);
};

}  // namespace gfx

#endif  // UI_GFX_WIN_RENDERING_WINDOW_MANAGER_H_
