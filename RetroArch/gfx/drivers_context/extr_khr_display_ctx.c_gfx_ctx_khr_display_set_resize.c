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
struct TYPE_7__ {int need_new_swapchain; TYPE_1__ context; scalar_t__ created_new_swapchain; } ;
struct TYPE_6__ {unsigned int width; unsigned int height; TYPE_3__ vk; int /*<<< orphan*/  swap_interval; } ;
typedef  TYPE_2__ khr_display_ctx_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  vulkan_acquire_next_image (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_create_swapchain (TYPE_3__*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gfx_ctx_khr_display_set_resize(void *data,
      unsigned width, unsigned height)
{
   khr_display_ctx_data_t *khr = (khr_display_ctx_data_t*)data;

   khr->width = width;
   khr->height = height;
   if (!vulkan_create_swapchain(&khr->vk, khr->width, khr->height,
            khr->swap_interval))
   {
      RARCH_ERR("[Vulkan]: Failed to update swapchain.\n");
      return false;
   }

   if (khr->vk.created_new_swapchain)
      vulkan_acquire_next_image(&khr->vk);

   khr->vk.context.invalid_swapchain = true;
   khr->vk.need_new_swapchain = false;
   return false;
}