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
struct TYPE_5__ {int invalid_swapchain; } ;
struct TYPE_7__ {int need_new_swapchain; int /*<<< orphan*/  created_new_swapchain; TYPE_1__ context; } ;
struct TYPE_6__ {int /*<<< orphan*/  buffer_scale; int /*<<< orphan*/  surface; TYPE_3__ vk; int /*<<< orphan*/  swap_interval; int /*<<< orphan*/  win; } ;
typedef  TYPE_2__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 132 
#define  GFX_CTX_OPENGL_API 131 
#define  GFX_CTX_OPENGL_ES_API 130 
#define  GFX_CTX_OPENVG_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  vulkan_acquire_next_image (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_create_swapchain (TYPE_3__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int wl_api ; 
 int /*<<< orphan*/  wl_egl_window_resize (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gfx_ctx_wl_set_resize(void *data, unsigned width, unsigned height)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   switch (wl_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         wl_egl_window_resize(wl->win, width, height, 0, 0);
#endif
         break;
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         if (vulkan_create_swapchain(&wl->vk, width, height, wl->swap_interval))
         {
            wl->vk.context.invalid_swapchain = true;
            if (wl->vk.created_new_swapchain)
               vulkan_acquire_next_image(&wl->vk);
         }
         else
         {
            RARCH_ERR("[Wayland/Vulkan]: Failed to update swapchain.\n");
            return false;
         }

         wl->vk.need_new_swapchain = false;
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }

   wl_surface_set_buffer_scale(wl->surface, wl->buffer_scale);
   return true;
}