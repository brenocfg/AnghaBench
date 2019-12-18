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
struct vk_buffer_chain {scalar_t__ offset; int /*<<< orphan*/  head; int /*<<< orphan*/  current; } ;

/* Variables and functions */

void vulkan_buffer_chain_discard(struct vk_buffer_chain *chain)
{
   chain->current = chain->head;
   chain->offset = 0;
}