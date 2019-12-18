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
struct upid {TYPE_1__* ns; int /*<<< orphan*/  pid_chain; } ;
struct pid {int level; int /*<<< orphan*/  rcu; struct upid* numbers; } ;
struct TYPE_2__ {scalar_t__ nr_hashed; int /*<<< orphan*/  proc_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delayed_put_pid ; 
 int /*<<< orphan*/  free_pidmap (struct upid*) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pidmap_lock ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void free_pid(struct pid *pid)
{
	/* We can be called with write_lock_irq(&tasklist_lock) held */
	int i;
	unsigned long flags;

	spin_lock_irqsave(&pidmap_lock, flags);
	for (i = 0; i <= pid->level; i++) {
		struct upid *upid = pid->numbers + i;
		hlist_del_rcu(&upid->pid_chain);
		if (--upid->ns->nr_hashed == 0)
			schedule_work(&upid->ns->proc_work);
	}
	spin_unlock_irqrestore(&pidmap_lock, flags);

	for (i = 0; i <= pid->level; i++)
		free_pidmap(pid->numbers + i);

	call_rcu(&pid->rcu, delayed_put_pid);
}