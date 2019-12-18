#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  set_layout; } ;
struct TYPE_11__ {unsigned int num_swapchain_images; TYPE_3__ pipelines; TYPE_2__* context; TYPE_1__* swapchain; } ;
typedef  TYPE_4__ vk_t ;
struct TYPE_12__ {int /*<<< orphan*/  const member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ VkDescriptorPoolSize ;
struct TYPE_9__ {int /*<<< orphan*/  device; } ;
struct TYPE_8__ {int /*<<< orphan*/  descriptor_manager; } ;

/* Variables and functions */
#define  VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER 130 
#define  VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER 129 
#define  VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS 128 
 int /*<<< orphan*/  vulkan_create_descriptor_manager (int /*<<< orphan*/ ,TYPE_5__ const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vulkan_init_descriptor_pool(vk_t *vk)
{
   unsigned i;
   static const VkDescriptorPoolSize pool_sizes[2] = {
      { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS },
      { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS },
   };

   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      vk->swapchain[i].descriptor_manager =
         vulkan_create_descriptor_manager(
               vk->context->device,
               pool_sizes, 2, vk->pipelines.set_layout);
   }
}