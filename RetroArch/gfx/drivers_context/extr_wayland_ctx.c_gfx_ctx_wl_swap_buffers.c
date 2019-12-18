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
struct TYPE_6__ {int /*<<< orphan*/  input; TYPE_3__ vk; int /*<<< orphan*/  egl; } ;
typedef  TYPE_2__ gfx_ctx_wayland_data_t ;

/* Variables and functions */
#define  GFX_CTX_NONE 132 
#define  GFX_CTX_OPENGL_API 131 
#define  GFX_CTX_OPENGL_ES_API 130 
#define  GFX_CTX_OPENVG_API 129 
#define  GFX_CTX_VULKAN_API 128 
 int /*<<< orphan*/  egl_swap_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_wayland_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_acquire_next_image (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_present (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int wl_api ; 

__attribute__((used)) static void gfx_ctx_wl_swap_buffers(void *data, void *data2)
{
   gfx_ctx_wayland_data_t *wl = (gfx_ctx_wayland_data_t*)data;

   switch (wl_api)
   {
      case GFX_CTX_OPENGL_API:
      case GFX_CTX_OPENGL_ES_API:
      case GFX_CTX_OPENVG_API:
#ifdef HAVE_EGL
         egl_swap_buffers(&wl->egl);
#endif
         break;
      case GFX_CTX_VULKAN_API:
#ifdef HAVE_VULKAN
         vulkan_present(&wl->vk, wl->vk.context.current_swapchain_index);
         vulkan_acquire_next_image(&wl->vk);
         flush_wayland_fd(&wl->input);
#endif
         break;
      case GFX_CTX_NONE:
      default:
         break;
   }
}