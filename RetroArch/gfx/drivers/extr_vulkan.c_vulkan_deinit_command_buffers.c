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
struct TYPE_7__ {unsigned int num_swapchain_images; TYPE_1__* swapchain; TYPE_2__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {int /*<<< orphan*/  cmd_pool; scalar_t__ cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  vkDestroyCommandPool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkFreeCommandBuffers (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static void vulkan_deinit_command_buffers(vk_t *vk)
{
   unsigned i;
   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      if (vk->swapchain[i].cmd)
         vkFreeCommandBuffers(vk->context->device,
               vk->swapchain[i].cmd_pool, 1, &vk->swapchain[i].cmd);

      vkDestroyCommandPool(vk->context->device,
            vk->swapchain[i].cmd_pool, NULL);
   }
}