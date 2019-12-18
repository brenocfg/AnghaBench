#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  GFX_CTX_NONE 129 
#define  GFX_CTX_OPENGL_API 128 
 int /*<<< orphan*/  wglMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int win32_api ; 
 int /*<<< orphan*/  win32_hdc ; 
 int /*<<< orphan*/  win32_hrc ; 
 int /*<<< orphan*/  win32_hw_hrc ; 
 int win32_use_hw_ctx ; 

__attribute__((used)) static void gfx_ctx_wgl_bind_hw_render(void *data, bool enable)
{
   switch (win32_api)
   {
      case GFX_CTX_OPENGL_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         win32_use_hw_ctx = enable;

         if (win32_hdc)
            wglMakeCurrent(win32_hdc, enable ? win32_hw_hrc : win32_hrc);
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}