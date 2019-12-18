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
struct vmbus_channel {int /*<<< orphan*/  controlwq; int /*<<< orphan*/  sc_list; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  inbound_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_workqueue (char*) ; 
 int /*<<< orphan*/  kfree (struct vmbus_channel*) ; 
 struct vmbus_channel* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vmbus_channel *alloc_channel(void)
{
	struct vmbus_channel *channel;

	channel = kzalloc(sizeof(*channel), GFP_ATOMIC);
	if (!channel)
		return NULL;

	spin_lock_init(&channel->inbound_lock);
	spin_lock_init(&channel->sc_lock);

	INIT_LIST_HEAD(&channel->sc_list);

	channel->controlwq = create_workqueue("hv_vmbus_ctl");
	if (!channel->controlwq) {
		kfree(channel);
		return NULL;
	}

	return channel;
}