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
struct TYPE_2__ {struct dlm_lock_resource* name; struct dlm_lock_resource* len; } ;
struct dlm_lock_resource {int state; scalar_t__ owner; int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  purge; TYPE_1__ lockname; } ;
struct dlm_ctxt {scalar_t__ node_num; int /*<<< orphan*/  purge_count; int /*<<< orphan*/  spinlock; struct dlm_lock_resource* name; int /*<<< orphan*/  purge_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DLM_LOCK_RES_DROPPING_REF ; 
 int DLM_LOCK_RES_MIGRATING ; 
 int /*<<< orphan*/  DLM_LOCK_RES_SETREF_INPROG ; 
 int /*<<< orphan*/  __dlm_lockres_unused (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_unhash_lockres (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_wait_on_lockres_flags (struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int dlm_drop_lockres_ref (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,struct dlm_lock_resource*,struct dlm_lock_resource*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_purge_lockres(struct dlm_ctxt *dlm,
			     struct dlm_lock_resource *res)
{
	int master;
	int ret = 0;

	spin_lock(&res->spinlock);
	if (!__dlm_lockres_unused(res)) {
		mlog(0, "%s:%.*s: tried to purge but not unused\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		__dlm_print_one_lock_resource(res);
		spin_unlock(&res->spinlock);
		BUG();
	}

	if (res->state & DLM_LOCK_RES_MIGRATING) {
		mlog(0, "%s:%.*s: Delay dropref as this lockres is "
		     "being remastered\n", dlm->name, res->lockname.len,
		     res->lockname.name);
		/* Re-add the lockres to the end of the purge list */
		if (!list_empty(&res->purge)) {
			list_del_init(&res->purge);
			list_add_tail(&res->purge, &dlm->purge_list);
		}
		spin_unlock(&res->spinlock);
		return 0;
	}

	master = (res->owner == dlm->node_num);

	if (!master)
		res->state |= DLM_LOCK_RES_DROPPING_REF;
	spin_unlock(&res->spinlock);

	mlog(0, "purging lockres %.*s, master = %d\n", res->lockname.len,
	     res->lockname.name, master);

	if (!master) {
		/* drop spinlock...  retake below */
		spin_unlock(&dlm->spinlock);

		spin_lock(&res->spinlock);
		/* This ensures that clear refmap is sent after the set */
		__dlm_wait_on_lockres_flags(res, DLM_LOCK_RES_SETREF_INPROG);
		spin_unlock(&res->spinlock);

		/* clear our bit from the master's refmap, ignore errors */
		ret = dlm_drop_lockres_ref(dlm, res);
		if (ret < 0) {
			mlog_errno(ret);
			if (!dlm_is_host_down(ret))
				BUG();
		}
		mlog(0, "%s:%.*s: dlm_deref_lockres returned %d\n",
		     dlm->name, res->lockname.len, res->lockname.name, ret);
		spin_lock(&dlm->spinlock);
	}

	spin_lock(&res->spinlock);
	if (!list_empty(&res->purge)) {
		mlog(0, "removing lockres %.*s:%p from purgelist, "
		     "master = %d\n", res->lockname.len, res->lockname.name,
		     res, master);
		list_del_init(&res->purge);
		spin_unlock(&res->spinlock);
		dlm_lockres_put(res);
		dlm->purge_count--;
	} else
		spin_unlock(&res->spinlock);

	__dlm_unhash_lockres(res);

	/* lockres is not in the hash now.  drop the flag and wake up
	 * any processes waiting in dlm_get_lock_resource. */
	if (!master) {
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_DROPPING_REF;
		spin_unlock(&res->spinlock);
		wake_up(&res->wq);
	}
	return 0;
}