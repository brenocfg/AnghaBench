#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {scalar_t__ real_master; scalar_t__ extra_ref; struct dlm_lock_resource* lockres; } ;
struct TYPE_5__ {TYPE_1__ ml; } ;
struct dlm_work_item {TYPE_2__ u; struct dlm_ctxt* dlm; } ;
struct dlm_migratable_lockres {int flags; int /*<<< orphan*/  master; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {TYPE_3__ lockname; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 scalar_t__ DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int DLM_MRES_ALL_DONE ; 
 int DLM_MRES_MIGRATION ; 
 int dlm_finish_migration (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lockres_drop_inflight_ref (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int dlm_lockres_master_requery (struct dlm_ctxt*,struct dlm_lock_resource*,scalar_t__*) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int dlm_process_recovery_data (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_migratable_lockres*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  mlog_exit (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_mig_lockres_worker(struct dlm_work_item *item, void *data)
{
	struct dlm_ctxt *dlm;
	struct dlm_migratable_lockres *mres;
	int ret = 0;
	struct dlm_lock_resource *res;
	u8 real_master;
	u8 extra_ref;

	dlm = item->dlm;
	mres = (struct dlm_migratable_lockres *)data;

	res = item->u.ml.lockres;
	real_master = item->u.ml.real_master;
	extra_ref = item->u.ml.extra_ref;

	if (real_master == DLM_LOCK_RES_OWNER_UNKNOWN) {
		/* this case is super-rare. only occurs if
		 * node death happens during migration. */
again:
		ret = dlm_lockres_master_requery(dlm, res, &real_master);
		if (ret < 0) {
			mlog(0, "dlm_lockres_master_requery ret=%d\n",
				  ret);
			goto again;
		}
		if (real_master == DLM_LOCK_RES_OWNER_UNKNOWN) {
			mlog(0, "lockres %.*s not claimed.  "
				   "this node will take it.\n",
				   res->lockname.len, res->lockname.name);
		} else {
			spin_lock(&res->spinlock);
			dlm_lockres_drop_inflight_ref(dlm, res);
			spin_unlock(&res->spinlock);
			mlog(0, "master needs to respond to sender "
				  "that node %u still owns %.*s\n",
				  real_master, res->lockname.len,
				  res->lockname.name);
			/* cannot touch this lockres */
			goto leave;
		}
	}

	ret = dlm_process_recovery_data(dlm, res, mres);
	if (ret < 0)
		mlog(0, "dlm_process_recovery_data returned  %d\n", ret);
	else
		mlog(0, "dlm_process_recovery_data succeeded\n");

	if ((mres->flags & (DLM_MRES_MIGRATION|DLM_MRES_ALL_DONE)) ==
	                   (DLM_MRES_MIGRATION|DLM_MRES_ALL_DONE)) {
		ret = dlm_finish_migration(dlm, res, mres->master);
		if (ret < 0)
			mlog_errno(ret);
	}

leave:
	/* See comment in dlm_mig_lockres_handler() */
	if (res) {
		if (extra_ref)
			dlm_lockres_put(res);
		dlm_lockres_put(res);
	}
	kfree(data);
	mlog_exit(ret);
}