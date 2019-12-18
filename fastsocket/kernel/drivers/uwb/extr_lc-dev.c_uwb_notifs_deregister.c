#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;
struct uwb_rc {TYPE_1__ notifs_chain; } ;
struct uwb_notifs_handler {int /*<<< orphan*/  list_node; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int uwb_notifs_deregister(struct uwb_rc *rc, struct uwb_notifs_handler *entry)
{
	if (mutex_lock_interruptible(&rc->notifs_chain.mutex))
		return -ERESTARTSYS;
	list_del(&entry->list_node);
	mutex_unlock(&rc->notifs_chain.mutex);
	return 0;
}