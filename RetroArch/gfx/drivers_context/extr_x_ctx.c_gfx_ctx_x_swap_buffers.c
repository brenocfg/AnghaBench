#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  current_swapchain_index; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
struct TYPE_6__ {TYPE_3__ vk; int /*<<< orphan*/  g_glx_win; int /*<<< orphan*/  g_is_double; int /*<<< orphan*/  sbc; scalar_t__ msc; int /*<<< orphan*/  ust; int /*<<< orphan*/  remainder; int /*<<< orphan*/  divisor; scalar_t__ g_interval; int /*<<< orphan*/  swap_mode; } ;
typedef  TYPE_2__ gfx_ctx_x_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 131 
#define  GFX_CTX_OPENGL_API 130 
#define  GFX_CTX_OPENGL_ES_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  RARCH_LOG (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_x11_dpy ; 
 int /*<<< orphan*/  glXSwapBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXSwapBuffersMscOML (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glXWaitForMscOML (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_acquire_next_image (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_present (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int x_api ; 

__attribute__((used)) static void gfx_ctx_x_swap_buffers(void *data, void *data2)
{
   gfx_ctx_x_data_t *x = (gfx_ctx_x_data_t*)data;

   switch (x_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
#if defined(HAVE_OPENGL) || defined(HAVE_OPENGL1) || defined(HAVE_OPENGL_CORE)
         if (x->swap_mode)
         {
            if (x->g_interval)
            {
               glXWaitForMscOML(g_x11_dpy, x->g_glx_win, x->msc + x->g_interval,
                     0, 0, &x->ust, &x->msc, &x->sbc);
               glXSwapBuffersMscOML(g_x11_dpy, x->g_glx_win, 0, 0, 0);
            }
            else
               glXSwapBuffersMscOML(g_x11_dpy, x->g_glx_win, 0, x->divisor, x->remainder);
#if 0
            RARCH_LOG("UST: %d, MSC: %d, SBC: %d\n", x->ust, x->msc, x->sbc);
#endif
         }
         else
         {
            if (x->g_is_double)
               glXSwapBuffers(g_x11_dpy, x->g_glx_win);
         }
#endif
         break;

      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         vulkan_present(&x->vk, x->vk.context.current_swapchain_index);
         vulkan_acquire_next_image(&x->vk);
#endif
         break;

      case GFX_CTX_NONE:
      default:
         break;
   }
}