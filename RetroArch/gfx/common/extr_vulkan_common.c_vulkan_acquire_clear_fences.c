#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int num_swapchain_images; int* swapchain_fences_signalled; scalar_t__* swapchain_fences; int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ context; } ;
typedef  TYPE_2__ gfx_ctx_vulkan_data_t ;

/* Variables and functions */
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  vkDestroyFence (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_acquire_clear_fences(gfx_ctx_vulkan_data_t *vk)
{
   unsigned i;
   for (i = 0; i < vk->context.num_swapchain_images; i++)
   {
      if (vk->context.swapchain_fences[i])
      {
         vkDestroyFence(vk->context.device,
               vk->context.swapchain_fences[i], NULL);
         vk->context.swapchain_fences[i] = VK_NULL_HANDLE;
      }
      vk->context.swapchain_fences_signalled[i] = false;
   }
}