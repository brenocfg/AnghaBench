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
struct TYPE_4__ {int swap_interval; TYPE_1__ vk; int /*<<< orphan*/  egl; } ;
typedef  TYPE_2__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 132 
#define  GFX_CTX_OPENGL_API 131 
#define  GFX_CTX_OPENGL_ES_API 130 
#define  GFX_CTX_OPENVG_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  egl_set_swap_interval (int /*<<< orphan*/ *,int) ; 
 int wl_api ; 

__attribute__((used)) static void gfx_ctx_wl_set_swap_interval(void *data, int swap_interval)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   switch (wl_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         egl_set_swap_interval(&wl->egl, swap_interval);
#endif
         break;
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         if (wl->swap_interval != swap_interval)
         {
            wl->swap_interval = swap_interval;
            if (wl->vk.swapchain)
               wl->vk.need_new_swapchain = true;
         }
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }
}