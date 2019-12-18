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
struct TYPE_2__ {int /*<<< orphan*/ * g_ctx; int /*<<< orphan*/  g_glx_win; } ;

/* Variables and functions */
#define  GFX_CTX_NONE 130 
#define  GFX_CTX_OPENGL_API 129 
#define  GFX_CTX_OPENGL_ES_API 128 
 int /*<<< orphan*/  None ; 
 TYPE_1__* current_context_data ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 int /*<<< orphan*/  glXMakeContextCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int x_api ; 

__attribute__((used)) static void gfx_ctx_x_make_current(bool release)
{
   if (!current_context_data)
      return;

   switch (x_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         if (release)
            glXMakeContextCurrent(g_x11_dpy, None, None, NULL);
         else
            glXMakeContextCurrent(g_x11_dpy,
                  current_context_data->g_glx_win,
                  current_context_data->g_glx_win, current_context_data->g_ctx);
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}