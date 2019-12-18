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
struct queue_item {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int handler_enabled ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_queue_head ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_queue_item_cache ; 
 int /*<<< orphan*/  tipc_tasklet ; 

int tipc_handler_start(void)
{
	tipc_queue_item_cache =
		kmem_cache_create("tipc_queue_items", sizeof(struct queue_item),
				  0, SLAB_HWCACHE_ALIGN, NULL);
	if (!tipc_queue_item_cache)
		return -ENOMEM;

	INIT_LIST_HEAD(&signal_queue_head);
	tasklet_enable(&tipc_tasklet);
	handler_enabled = 1;
	return 0;
}