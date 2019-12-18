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
struct dlm_ctxt {scalar_t__ joining_node; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  dlm_state; int /*<<< orphan*/  dlm_join_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CTXT_LEAVING ; 
 scalar_t__ DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  dlm_no_joining_node (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlm_mark_domain_leaving(struct dlm_ctxt *dlm)
{
	/* Yikes, a double spinlock! I need domain_lock for the dlm
	 * state and the dlm spinlock for join state... Sorry! */
again:
	spin_lock(&dlm_domain_lock);
	spin_lock(&dlm->spinlock);

	if (dlm->joining_node != DLM_LOCK_RES_OWNER_UNKNOWN) {
		mlog(0, "Node %d is joining, we wait on it.\n",
			  dlm->joining_node);
		spin_unlock(&dlm->spinlock);
		spin_unlock(&dlm_domain_lock);

		wait_event(dlm->dlm_join_events, dlm_no_joining_node(dlm));
		goto again;
	}

	dlm->dlm_state = DLM_CTXT_LEAVING;
	spin_unlock(&dlm->spinlock);
	spin_unlock(&dlm_domain_lock);
}