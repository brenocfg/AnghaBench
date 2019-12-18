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
struct TYPE_6__ {unsigned int current_swapchain_index; scalar_t__* swapchain_fences; int* swapchain_fences_signalled; int /*<<< orphan*/  device; } ;
struct TYPE_7__ {TYPE_1__ context; } ;
typedef  TYPE_2__ gfx_ctx_vulkan_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ VkFenceCreateInfo ;
typedef  scalar_t__ VkFence ;

/* Variables and functions */
 int /*<<< orphan*/  UINT64_MAX ; 
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_FENCE_CREATE_INFO ; 
 int /*<<< orphan*/  vkCreateFence (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  vkResetFences (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  vkWaitForFences (int /*<<< orphan*/ ,int,scalar_t__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vulkan_acquire_wait_fences(gfx_ctx_vulkan_data_t *vk)
{
   VkFenceCreateInfo fence_info =
   { VK_STRUCTURE_TYPE_FENCE_CREATE_INFO };

   unsigned index = vk->context.current_swapchain_index;
   VkFence *next_fence = &vk->context.swapchain_fences[index];

   if (*next_fence != VK_NULL_HANDLE)
   {
      if (vk->context.swapchain_fences_signalled[index])
         vkWaitForFences(vk->context.device, 1, next_fence, true, UINT64_MAX);
      vkResetFences(vk->context.device, 1, next_fence);
   }
   else
      vkCreateFence(vk->context.device, &fence_info, NULL, next_fence);
   vk->context.swapchain_fences_signalled[index] = false;
}