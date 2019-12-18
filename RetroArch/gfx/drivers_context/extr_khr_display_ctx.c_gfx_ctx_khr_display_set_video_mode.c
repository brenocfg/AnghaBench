#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  monitor_index; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct vulkan_display_surface_info {unsigned int width; unsigned int height; int /*<<< orphan*/  monitor_index; } ;
struct TYPE_6__ {int /*<<< orphan*/  swapchain_height; int /*<<< orphan*/  swapchain_width; } ;
struct TYPE_9__ {TYPE_1__ context; } ;
struct TYPE_8__ {TYPE_4__ vk; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  swap_interval; } ;
typedef  TYPE_3__ khr_display_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  VULKAN_WSI_DISPLAY ; 
 int /*<<< orphan*/  gfx_ctx_khr_display_destroy (void*) ; 
 int /*<<< orphan*/  vulkan_surface_create (TYPE_4__*,int /*<<< orphan*/ ,struct vulkan_display_surface_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gfx_ctx_khr_display_set_video_mode(void *data,
      video_frame_info_t *video_info,
      unsigned width, unsigned height,
      bool fullscreen)
{
   struct vulkan_display_surface_info info;
   khr_display_ctx_data_t *khr = (khr_display_ctx_data_t*)data;

   if (!fullscreen)
   {
      width = 0;
      height = 0;
   }

   info.width         = width;
   info.height        = height;
   info.monitor_index = video_info->monitor_index;

   if (!vulkan_surface_create(&khr->vk, VULKAN_WSI_DISPLAY, &info, NULL,
            0, 0, khr->swap_interval))
   {
      RARCH_ERR("[Vulkan]: Failed to create KHR_display surface.\n");
      goto error;
   }

   khr->width = khr->vk.context.swapchain_width;
   khr->height = khr->vk.context.swapchain_height;

   return true;

error:
   gfx_ctx_khr_display_destroy(data);
   return false;
}