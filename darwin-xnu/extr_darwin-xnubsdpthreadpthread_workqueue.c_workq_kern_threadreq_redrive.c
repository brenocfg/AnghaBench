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
struct workqueue {int dummy; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 struct workqueue* proc_get_wqptr_fast (struct proc*) ; 
 int /*<<< orphan*/  workq_lock_spin (struct workqueue*) ; 
 int /*<<< orphan*/  workq_schedule_creator (struct proc*,struct workqueue*,int) ; 
 int /*<<< orphan*/  workq_unlock (struct workqueue*) ; 

void
workq_kern_threadreq_redrive(struct proc *p, int flags)
{
	struct workqueue *wq = proc_get_wqptr_fast(p);

	workq_lock_spin(wq);
	workq_schedule_creator(p, wq, flags);
	workq_unlock(wq);
}