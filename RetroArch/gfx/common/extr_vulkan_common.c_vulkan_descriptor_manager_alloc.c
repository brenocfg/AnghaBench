#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vk_descriptor_manager {scalar_t__ count; TYPE_1__* current; } ;
typedef  int /*<<< orphan*/  VkDevice ;
typedef  int /*<<< orphan*/  VkDescriptorSet ;
struct TYPE_3__ {int /*<<< orphan*/ * sets; struct TYPE_3__* next; } ;

/* Variables and functions */
 scalar_t__ VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS ; 
 int /*<<< orphan*/  retro_assert (TYPE_1__*) ; 
 TYPE_1__* vulkan_alloc_descriptor_pool (int /*<<< orphan*/ ,struct vk_descriptor_manager*) ; 

VkDescriptorSet vulkan_descriptor_manager_alloc(
      VkDevice device, struct vk_descriptor_manager *manager)
{
   if (manager->count < VULKAN_DESCRIPTOR_MANAGER_BLOCK_SETS)
      return manager->current->sets[manager->count++];

   while (manager->current->next)
   {
      manager->current = manager->current->next;
      manager->count   = 0;
      return manager->current->sets[manager->count++];
   }

   manager->current->next = vulkan_alloc_descriptor_pool(device, manager);
   retro_assert(manager->current->next);

   manager->current = manager->current->next;
   manager->count   = 0;
   return manager->current->sets[manager->count++];
}