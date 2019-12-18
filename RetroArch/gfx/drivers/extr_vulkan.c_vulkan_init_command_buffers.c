#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned int num_swapchain_images; TYPE_2__* swapchain; TYPE_1__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_12__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  queueFamilyIndex; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ VkCommandPoolCreateInfo ;
struct TYPE_13__ {int commandBufferCount; int /*<<< orphan*/  level; int /*<<< orphan*/  commandPool; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ VkCommandBufferAllocateInfo ;
struct TYPE_10__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  cmd_pool; } ;
struct TYPE_9__ {int /*<<< orphan*/  device; int /*<<< orphan*/  graphics_queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_COMMAND_BUFFER_LEVEL_PRIMARY ; 
 int /*<<< orphan*/  VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO ; 
 int /*<<< orphan*/  vkAllocateCommandBuffers (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkCreateCommandPool (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_init_command_buffers(vk_t *vk)
{
   /* RESET_COMMAND_BUFFER_BIT allows command buffer to be reset. */
   unsigned i;

   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      VkCommandPoolCreateInfo pool_info = {
         VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
      VkCommandBufferAllocateInfo info  = {
         VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO };

      pool_info.queueFamilyIndex = vk->context->graphics_queue_index;
      pool_info.flags            =
         VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

      vkCreateCommandPool(vk->context->device,
            &pool_info, NULL, &vk->swapchain[i].cmd_pool);

      info.commandPool           = vk->swapchain[i].cmd_pool;
      info.level                 = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
      info.commandBufferCount    = 1;

      vkAllocateCommandBuffers(vk->context->device,
            &info, &vk->swapchain[i].cmd);
   }
}