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
struct dlm_lock_resource {int state; int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; scalar_t__ migration_pending; int /*<<< orphan*/  asts_reserved; } ;
struct dlm_ctxt {int /*<<< orphan*/  migration_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_RES_MIGRATING ; 
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dlm_lockres_release_ast(struct dlm_ctxt *dlm,
			     struct dlm_lock_resource *res)
{
	if (!atomic_dec_and_lock(&res->asts_reserved, &res->spinlock))
		return;

	if (!res->migration_pending) {
		spin_unlock(&res->spinlock);
		return;
	}

	BUG_ON(res->state & DLM_LOCK_RES_MIGRATING);
	res->migration_pending = 0;
	res->state |= DLM_LOCK_RES_MIGRATING;
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);
	wake_up(&dlm->migration_wq);
}