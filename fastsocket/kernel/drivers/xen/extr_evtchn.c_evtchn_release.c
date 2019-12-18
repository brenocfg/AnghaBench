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
struct per_user_data {struct per_user_data* name; scalar_t__ ring; } ;
struct inode {int dummy; } ;
struct file {struct per_user_data* private_data; } ;

/* Variables and functions */
 int NR_EVENT_CHANNELS ; 
 int /*<<< orphan*/  evtchn_unbind_from_user (struct per_user_data*,int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct per_user_data*) ; 
 struct per_user_data** port_user ; 
 int /*<<< orphan*/  port_user_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evtchn_release(struct inode *inode, struct file *filp)
{
	int i;
	struct per_user_data *u = filp->private_data;

	spin_lock_irq(&port_user_lock);

	free_page((unsigned long)u->ring);

	for (i = 0; i < NR_EVENT_CHANNELS; i++) {
		if (port_user[i] != u)
			continue;

		evtchn_unbind_from_user(port_user[i], i);
	}

	spin_unlock_irq(&port_user_lock);

	kfree(u->name);
	kfree(u);

	return 0;
}