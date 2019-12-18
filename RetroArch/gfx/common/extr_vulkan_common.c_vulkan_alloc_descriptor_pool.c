#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vk_descriptor_pool {int /*<<< orphan*/ * sets; int /*<<< orphan*/  pool; } ;
struct vk_descriptor_manager {int /*<<< orphan*/  set_layout; int /*<<< orphan*/  sizes; int /*<<< orphan*/  num_sizes; } ;
typedef  int /*<<< orphan*/  VkDevice ;
struct TYPE_5__ {int descriptorSetCount; int /*<<< orphan*/ * pSetLayouts; int /*<<< orphan*/  descriptorPool; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ VkDescriptorSetAllocateInfo ;
struct TYPE_6__ {unsigned int maxSets; int /*<<< orphan*/  flags; int /*<<< orphan*/  pPoolSizes; int /*<<< orphan*/  poolSizeCount; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ VkDescriptorPoolCreateInfo ;

/* Variables and functions */
 int /*<<< orphan*/  VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO ; 
 unsigned int VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  vkAllocateDescriptorSets (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkCreateDescriptorPool (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vk_descriptor_pool *vulkan_alloc_descriptor_pool(
      VkDevice device,
      const struct vk_descriptor_manager *manager)
{
   unsigned i;
   VkDescriptorPoolCreateInfo pool_info   = {
      VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO };
   VkDescriptorSetAllocateInfo alloc_info = {
      VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO };

   struct vk_descriptor_pool *pool        =
      (struct vk_descriptor_pool*)calloc(1, sizeof(*pool));
   if (!pool)
      return NULL;

   pool_info.maxSets       = VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS;
   pool_info.poolSizeCount = manager->num_sizes;
   pool_info.pPoolSizes    = manager->sizes;
   pool_info.flags         = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

   vkCreateDescriptorPool(device, &pool_info, NULL, &pool->pool);

   /* Just allocate all descriptor sets up front. */
   alloc_info.descriptorPool     = pool->pool;
   alloc_info.descriptorSetCount = 1;
   alloc_info.pSetLayouts        = &manager->set_layout;

   for (i = 0; i < VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS; i++)
      vkAllocateDescriptorSets(device, &alloc_info, &pool->sets[i]);

   return pool;
}