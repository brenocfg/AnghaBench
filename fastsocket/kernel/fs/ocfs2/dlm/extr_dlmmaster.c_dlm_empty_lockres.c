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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {scalar_t__ owner; TYPE_1__ lockname; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {scalar_t__ node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_MIGRATION_RETRY_MS ; 
 int ENOTEMPTY ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  O2NM_MAX_NODES ; 
 int /*<<< orphan*/  __dlm_lockres_unused (struct dlm_lock_resource*) ; 
 int dlm_is_lockres_migrateable (struct dlm_ctxt*,struct dlm_lock_resource*,int*) ; 
 int dlm_migrate_lockres (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_empty_lockres(struct dlm_ctxt *dlm, struct dlm_lock_resource *res)
{
	int ret;
	int lock_dropped = 0;
	int numlocks;

	spin_lock(&res->spinlock);
	if (res->owner != dlm->node_num) {
		if (!__dlm_lockres_unused(res)) {
			mlog(ML_ERROR, "%s:%.*s: this node is not master, "
			     "trying to free this but locks remain\n",
			     dlm->name, res->lockname.len, res->lockname.name);
		}
		spin_unlock(&res->spinlock);
		goto leave;
	}

	/* No need to migrate a lockres having no locks */
	ret = dlm_is_lockres_migrateable(dlm, res, &numlocks);
	if (ret >= 0 && numlocks == 0) {
		spin_unlock(&res->spinlock);
		goto leave;
	}
	spin_unlock(&res->spinlock);

	/* Wheee! Migrate lockres here! Will sleep so drop spinlock. */
	spin_unlock(&dlm->spinlock);
	lock_dropped = 1;
	while (1) {
		ret = dlm_migrate_lockres(dlm, res, O2NM_MAX_NODES);
		if (ret >= 0)
			break;
		if (ret == -ENOTEMPTY) {
			mlog(ML_ERROR, "lockres %.*s still has local locks!\n",
		     		res->lockname.len, res->lockname.name);
			BUG();
		}

		mlog(0, "lockres %.*s: migrate failed, "
		     "retrying\n", res->lockname.len,
		     res->lockname.name);
		msleep(DLM_MIGRATION_RETRY_MS);
	}
	spin_lock(&dlm->spinlock);
leave:
	return lock_dropped;
}