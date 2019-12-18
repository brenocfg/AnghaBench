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
struct proc {int /*<<< orphan*/  p_klist; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_proc; } ;
struct knote {TYPE_1__ kn_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int /*<<< orphan*/  PROC_NULL ; 
 struct knote* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_klist_lock () ; 
 int /*<<< orphan*/  proc_klist_unlock () ; 

void
proc_knote_drain(struct proc *p)
{
	struct knote *kn = NULL;

	/*
	 * Clear the proc's klist to avoid references after the proc is reaped.
	 */
	proc_klist_lock();
	while ((kn = SLIST_FIRST(&p->p_klist))) {
		kn->kn_ptr.p_proc = PROC_NULL;
		KNOTE_DETACH(&p->p_klist, kn);
	}
	proc_klist_unlock();
}