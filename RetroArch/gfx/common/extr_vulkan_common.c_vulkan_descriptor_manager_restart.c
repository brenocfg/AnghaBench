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
struct vk_descriptor_manager {scalar_t__ count; int /*<<< orphan*/  head; int /*<<< orphan*/  current; } ;

/* Variables and functions */

void vulkan_descriptor_manager_restart(struct vk_descriptor_manager *manager)
{
   manager->current = manager->head;
   manager->count = 0;
}