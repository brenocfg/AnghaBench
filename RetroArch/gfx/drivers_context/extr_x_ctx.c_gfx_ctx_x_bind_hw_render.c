#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int g_use_hw_ctx; int /*<<< orphan*/  g_ctx; int /*<<< orphan*/  g_hw_ctx; int /*<<< orphan*/  g_glx_win; } ;
typedef  TYPE_1__ gfx_ctx_x_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 130 
#define  GFX_CTX_OPENGL_API 129 
#define  GFX_CTX_OPENGL_ES_API 128 
 int /*<<< orphan*/  g_x11_dpy ; 
 int /*<<< orphan*/  glXMakeContextCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int x_api ; 

__attribute__((used)) static void gfx_ctx_x_bind_hw_render(void *data, bool enable)
{
   gfx_ctx_x_data_t *x = (gfx_ctx_x_data_t*)data;

   if (!x)
      return;

   switch (x_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         x->g_use_hw_ctx = enable;
         if (!g_x11_dpy || !x->g_glx_win)
            return;
         glXMakeContextCurrent(g_x11_dpy, x->g_glx_win,
               x->g_glx_win, enable ? x->g_hw_ctx : x->g_ctx);
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}