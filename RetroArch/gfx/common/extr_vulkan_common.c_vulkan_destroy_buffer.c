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
struct vk_buffer {int /*<<< orphan*/  buffer; int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  VkDevice ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vk_buffer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkDestroyBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkFreeMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkUnmapMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vulkan_destroy_buffer(
      VkDevice device,
      struct vk_buffer *buffer)
{
   vkUnmapMemory(device, buffer->memory);
   vkFreeMemory(device, buffer->memory, NULL);

   vkDestroyBuffer(device, buffer->buffer, NULL);

   memset(buffer, 0, sizeof(*buffer));
}