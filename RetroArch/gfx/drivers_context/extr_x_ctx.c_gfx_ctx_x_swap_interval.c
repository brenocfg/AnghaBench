#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int need_new_swapchain; int /*<<< orphan*/  swapchain; } ;
struct TYPE_4__ {int g_interval; TYPE_1__ vk; int /*<<< orphan*/  g_glx_win; } ;
typedef  TYPE_2__ gfx_ctx_x_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 131 
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  RARCH_LOG (char*,int) ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  g_pglSwapInterval (int) ; 
 int /*<<< orphan*/  g_pglSwapIntervalEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_pglSwapIntervalSGI (int) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 int x_api ; 

__attribute__((used)) static void gfx_ctx_x_swap_interval(void *data, int interval)
{
   gfx_ctx_x_data_t *x = (gfx_ctx_x_data_t*)data;

   switch (x_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         x->g_interval = interval;

         if (g_pglSwapIntervalEXT)
         {
            RARCH_LOG("[GLX]: glXSwapIntervalEXT(%i)\n", x->g_interval);
            g_pglSwapIntervalEXT(g_x11_dpy, x->g_glx_win, x->g_interval);
         }
         else if (g_pglSwapInterval)
         {
            RARCH_LOG("[GLX]: glXSwapInterval(%i)\n", x->g_interval);
            if (g_pglSwapInterval(x->g_interval) != 0)
               RARCH_WARN("[GLX]: glXSwapInterval() failed.\n");
         }
         else if (g_pglSwapIntervalSGI)
         {
            RARCH_LOG("[GLX]: glXSwapIntervalSGI(%i)\n", x->g_interval);
            if (g_pglSwapIntervalSGI(x->g_interval) != 0)
               RARCH_WARN("[GLX]: glXSwapIntervalSGI() failed.\n");
         }
#endif
         break;

      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         if (x->g_interval != interval)
         {
            x->g_interval = interval;
            if (x->vk.swapchain)
               x->vk.need_new_swapchain = true;
         }
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}