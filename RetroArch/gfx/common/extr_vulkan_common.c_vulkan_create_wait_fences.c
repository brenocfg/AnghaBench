#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int num_swapchain_images; int /*<<< orphan*/ * swapchain_fences; int /*<<< orphan*/  device; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
typedef  TYPE_2__ gfx_ctx_vulkan_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ VkFenceCreateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_FENCE_CREATE_INFO ; 
 int /*<<< orphan*/  vkCreateFence (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_create_wait_fences(gfx_ctx_vulkan_data_t *vk)
{
   VkFenceCreateInfo fence_info =
   { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };

   unsigned i;
   for (i = 0; i < vk->context.num_swapchain_images; i++)
   {
      if (!vk->context.swapchain_fences[i])
      {
         vkCreateFence(vk->context.device, &fence_info, NULL,
               &vk->context.swapchain_fences[i]);
      }
   }
}