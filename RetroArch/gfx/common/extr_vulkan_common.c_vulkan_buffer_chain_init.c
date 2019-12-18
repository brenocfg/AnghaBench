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
struct vk_buffer_chain {int /*<<< orphan*/ * current; int /*<<< orphan*/ * head; int /*<<< orphan*/  usage; scalar_t__ offset; void* alignment; void* block_size; } ;
typedef  void* VkDeviceSize ;
typedef  int /*<<< orphan*/  VkBufferUsageFlags ;

/* Variables and functions */

struct vk_buffer_chain vulkan_buffer_chain_init(
      VkDeviceSize block_size,
      VkDeviceSize alignment,
      VkBufferUsageFlags usage)
{
   struct vk_buffer_chain chain;

   chain.block_size = block_size;
   chain.alignment  = alignment;
   chain.offset     = 0;
   chain.usage      = usage;
   chain.head       = NULL;
   chain.current    = NULL;

   return chain;
}