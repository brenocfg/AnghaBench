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
struct dlm_lock_resource {int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  dlm_thread_wq; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dlm_dirty_lockres (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  mlog_entry (char*,struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dlm_kick_thread(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	mlog_entry("dlm=%p, res=%p\n", dlm, res);
	if (res) {
		spin_lock(&dlm->spinlock);
		spin_lock(&res->spinlock);
		__dlm_dirty_lockres(dlm, res);
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);
	}
	wake_up(&dlm->dlm_thread_wq);
}