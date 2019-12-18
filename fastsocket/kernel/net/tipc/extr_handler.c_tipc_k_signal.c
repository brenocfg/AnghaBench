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
struct queue_item {unsigned long data; int /*<<< orphan*/  next_signal; int /*<<< orphan*/  handler; } ;
typedef  int /*<<< orphan*/  Handler ;

/* Variables and functions */
 unsigned int ENOMEM ; 
 unsigned int ENOPROTOOPT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  handler_enabled ; 
 struct queue_item* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qitem_lock ; 
 int /*<<< orphan*/  signal_queue_head ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tipc_queue_item_cache ; 
 int /*<<< orphan*/  tipc_tasklet ; 

unsigned int tipc_k_signal(Handler routine, unsigned long argument)
{
	struct queue_item *item;

	if (!handler_enabled) {
		err("Signal request ignored by handler\n");
		return -ENOPROTOOPT;
	}

	spin_lock_bh(&qitem_lock);
	item = kmem_cache_alloc(tipc_queue_item_cache, GFP_ATOMIC);
	if (!item) {
		err("Signal queue out of memory\n");
		spin_unlock_bh(&qitem_lock);
		return -ENOMEM;
	}
	item->handler = routine;
	item->data = argument;
	list_add_tail(&item->next_signal, &signal_queue_head);
	spin_unlock_bh(&qitem_lock);
	tasklet_schedule(&tipc_tasklet);
	return 0;
}