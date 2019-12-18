#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vk_descriptor_manager {unsigned int num_sizes; int head; int /*<<< orphan*/  set_layout; int /*<<< orphan*/  sizes; } ;
typedef  int /*<<< orphan*/  manager ;
typedef  int /*<<< orphan*/  VkDevice ;
typedef  int /*<<< orphan*/  VkDescriptorSetLayout ;
typedef  int /*<<< orphan*/  VkDescriptorPoolSize ;

/* Variables and functions */
 unsigned int VULKAN_MAX_DESCRIPTOR_POOL_SIZES ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct vk_descriptor_manager*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 int vulkan_alloc_descriptor_pool (int /*<<< orphan*/ ,struct vk_descriptor_manager*) ; 

struct vk_descriptor_manager vulkan_create_descriptor_manager(
      VkDevice device,
      const VkDescriptorPoolSize *sizes,
      unsigned num_sizes,
      VkDescriptorSetLayout set_layout)
{
   struct vk_descriptor_manager manager;
   memset(&manager, 0, sizeof(manager));
   retro_assert(num_sizes <= VULKAN_MAX_DESCRIPTOR_POOL_SIZES);
   memcpy(manager.sizes, sizes, num_sizes * sizeof(*sizes));
   manager.num_sizes  = num_sizes;
   manager.set_layout = set_layout;

   manager.head       = vulkan_alloc_descriptor_pool(device, &manager);
   retro_assert(manager.head);
   return manager;
}