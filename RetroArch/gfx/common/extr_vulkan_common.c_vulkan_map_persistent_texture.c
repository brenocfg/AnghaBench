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
struct vk_texture {int /*<<< orphan*/  mapped; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  VkDevice ;

/* Variables and functions */
 int /*<<< orphan*/  vkMapMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vulkan_map_persistent_texture(
      VkDevice device,
      struct vk_texture *texture)
{
   vkMapMemory(device, texture->memory, texture->offset,
         texture->size, 0, &texture->mapped);
}