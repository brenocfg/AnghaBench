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
typedef  scalar_t__ u8 ;
struct dlm_migratable_lockres {int dummy; } ;
struct dlm_master_list_entry {int /*<<< orphan*/  woken; int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {unsigned int len; int /*<<< orphan*/  name; } ;
struct dlm_lock_resource {scalar_t__ owner; int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  state; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  master_lock; int /*<<< orphan*/  dlm_worker; int /*<<< orphan*/  node_num; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LOCK_RES_MIGRATING ; 
 int /*<<< orphan*/  DLM_MRES_MIGRATION ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ O2NM_MAX_NODES ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int dlm_add_migration_mle (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_master_list_entry*,struct dlm_master_list_entry**,char const*,unsigned int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_get_mle_inuse (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 int dlm_is_lockres_migrateable (struct dlm_ctxt*,struct dlm_lock_resource*,int*) ; 
 scalar_t__ dlm_is_node_dead (struct dlm_ctxt*,scalar_t__) ; 
 int /*<<< orphan*/  dlm_kick_thread (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_calc_usage (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 scalar_t__ dlm_mark_lockres_migrating (struct dlm_ctxt*,struct dlm_lock_resource*,scalar_t__) ; 
 int /*<<< orphan*/  dlm_mle_cache ; 
 int /*<<< orphan*/  dlm_mle_detach_hb_events (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 scalar_t__ dlm_pick_migration_target (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_put_mle (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  dlm_put_mle_inuse (struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  dlm_remove_nonlocal_locks (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int dlm_send_one_lockres (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_migratable_lockres*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_set_lockres_owner (struct dlm_ctxt*,struct dlm_lock_resource*,scalar_t__) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_migrate_lockres(struct dlm_ctxt *dlm,
			       struct dlm_lock_resource *res,
			       u8 target)
{
	struct dlm_master_list_entry *mle = NULL;
	struct dlm_master_list_entry *oldmle = NULL;
 	struct dlm_migratable_lockres *mres = NULL;
	int ret = 0;
	const char *name;
	unsigned int namelen;
	int mle_added = 0;
	int numlocks;
	int wake = 0;

	if (!dlm_grab(dlm))
		return -EINVAL;

	name = res->lockname.name;
	namelen = res->lockname.len;

	mlog(0, "migrating %.*s to %u\n", namelen, name, target);

	/*
	 * ensure this lockres is a proper candidate for migration
	 */
	spin_lock(&res->spinlock);
	ret = dlm_is_lockres_migrateable(dlm, res, &numlocks);
	if (ret < 0) {
		spin_unlock(&res->spinlock);
		goto leave;
	}
	spin_unlock(&res->spinlock);

	/* no work to do */
	if (numlocks == 0) {
		mlog(0, "no locks were found on this lockres! done!\n");
		goto leave;
	}

	/*
	 * preallocate up front
	 * if this fails, abort
	 */

	ret = -ENOMEM;
	mres = (struct dlm_migratable_lockres *) __get_free_page(GFP_NOFS);
	if (!mres) {
		mlog_errno(ret);
		goto leave;
	}

	mle = (struct dlm_master_list_entry *) kmem_cache_alloc(dlm_mle_cache,
								GFP_NOFS);
	if (!mle) {
		mlog_errno(ret);
		goto leave;
	}
	ret = 0;

	/*
	 * find a node to migrate the lockres to
	 */

	mlog(0, "picking a migration node\n");
	spin_lock(&dlm->spinlock);
	/* pick a new node */
	if (!test_bit(target, dlm->domain_map) ||
	    target >= O2NM_MAX_NODES) {
		target = dlm_pick_migration_target(dlm, res);
	}
	mlog(0, "node %u chosen for migration\n", target);

	if (target >= O2NM_MAX_NODES ||
	    !test_bit(target, dlm->domain_map)) {
		/* target chosen is not alive */
		ret = -EINVAL;
	}

	if (ret) {
		spin_unlock(&dlm->spinlock);
		goto fail;
	}

	mlog(0, "continuing with target = %u\n", target);

	/*
	 * clear any existing master requests and
	 * add the migration mle to the list
	 */
	spin_lock(&dlm->master_lock);
	ret = dlm_add_migration_mle(dlm, res, mle, &oldmle, name,
				    namelen, target, dlm->node_num);
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

	if (ret == -EEXIST) {
		mlog(0, "another process is already migrating it\n");
		goto fail;
	}
	mle_added = 1;

	/*
	 * set the MIGRATING flag and flush asts
	 * if we fail after this we need to re-dirty the lockres
	 */
	if (dlm_mark_lockres_migrating(dlm, res, target) < 0) {
		mlog(ML_ERROR, "tried to migrate %.*s to %u, but "
		     "the target went down.\n", res->lockname.len,
		     res->lockname.name, target);
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_MIGRATING;
		wake = 1;
		spin_unlock(&res->spinlock);
		ret = -EINVAL;
	}

fail:
	if (oldmle) {
		/* master is known, detach if not already detached */
		dlm_mle_detach_hb_events(dlm, oldmle);
		dlm_put_mle(oldmle);
	}

	if (ret < 0) {
		if (mle_added) {
			dlm_mle_detach_hb_events(dlm, mle);
			dlm_put_mle(mle);
		} else if (mle) {
			kmem_cache_free(dlm_mle_cache, mle);
		}
		goto leave;
	}

	/*
	 * at this point, we have a migration target, an mle
	 * in the master list, and the MIGRATING flag set on
	 * the lockres
	 */

	/* now that remote nodes are spinning on the MIGRATING flag,
	 * ensure that all assert_master work is flushed. */
	flush_workqueue(dlm->dlm_worker);

	/* get an extra reference on the mle.
	 * otherwise the assert_master from the new
	 * master will destroy this.
	 * also, make sure that all callers of dlm_get_mle
	 * take both dlm->spinlock and dlm->master_lock */
	spin_lock(&dlm->spinlock);
	spin_lock(&dlm->master_lock);
	dlm_get_mle_inuse(mle);
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

	/* notify new node and send all lock state */
	/* call send_one_lockres with migration flag.
	 * this serves as notice to the target node that a
	 * migration is starting. */
	ret = dlm_send_one_lockres(dlm, res, mres, target,
				   DLM_MRES_MIGRATION);

	if (ret < 0) {
		mlog(0, "migration to node %u failed with %d\n",
		     target, ret);
		/* migration failed, detach and clean up mle */
		dlm_mle_detach_hb_events(dlm, mle);
		dlm_put_mle(mle);
		dlm_put_mle_inuse(mle);
		spin_lock(&res->spinlock);
		res->state &= ~DLM_LOCK_RES_MIGRATING;
		wake = 1;
		spin_unlock(&res->spinlock);
		goto leave;
	}

	/* at this point, the target sends a message to all nodes,
	 * (using dlm_do_migrate_request).  this node is skipped since
	 * we had to put an mle in the list to begin the process.  this
	 * node now waits for target to do an assert master.  this node
	 * will be the last one notified, ensuring that the migration
	 * is complete everywhere.  if the target dies while this is
	 * going on, some nodes could potentially see the target as the
	 * master, so it is important that my recovery finds the migration
	 * mle and sets the master to UNKNONWN. */


	/* wait for new node to assert master */
	while (1) {
		ret = wait_event_interruptible_timeout(mle->wq,
					(atomic_read(&mle->woken) == 1),
					msecs_to_jiffies(5000));

		if (ret >= 0) {
		       	if (atomic_read(&mle->woken) == 1 ||
			    res->owner == target)
				break;

			mlog(0, "%s:%.*s: timed out during migration\n",
			     dlm->name, res->lockname.len, res->lockname.name);
			/* avoid hang during shutdown when migrating lockres 
			 * to a node which also goes down */
			if (dlm_is_node_dead(dlm, target)) {
				mlog(0, "%s:%.*s: expected migration "
				     "target %u is no longer up, restarting\n",
				     dlm->name, res->lockname.len,
				     res->lockname.name, target);
				ret = -EINVAL;
				/* migration failed, detach and clean up mle */
				dlm_mle_detach_hb_events(dlm, mle);
				dlm_put_mle(mle);
				dlm_put_mle_inuse(mle);
				spin_lock(&res->spinlock);
				res->state &= ~DLM_LOCK_RES_MIGRATING;
				wake = 1;
				spin_unlock(&res->spinlock);
				goto leave;
			}
		} else
			mlog(0, "%s:%.*s: caught signal during migration\n",
			     dlm->name, res->lockname.len, res->lockname.name);
	}

	/* all done, set the owner, clear the flag */
	spin_lock(&res->spinlock);
	dlm_set_lockres_owner(dlm, res, target);
	res->state &= ~DLM_LOCK_RES_MIGRATING;
	dlm_remove_nonlocal_locks(dlm, res);
	spin_unlock(&res->spinlock);
	wake_up(&res->wq);

	/* master is known, detach if not already detached */
	dlm_mle_detach_hb_events(dlm, mle);
	dlm_put_mle_inuse(mle);
	ret = 0;

	dlm_lockres_calc_usage(dlm, res);

leave:
	/* re-dirty the lockres if we failed */
	if (ret < 0)
		dlm_kick_thread(dlm, res);

	/* wake up waiters if the MIGRATING flag got set
	 * but migration failed */
	if (wake)
		wake_up(&res->wq);

	/* TODO: cleanup */
	if (mres)
		free_page((unsigned long)mres);

	dlm_put(dlm);

	mlog(0, "returning %d\n", ret);
	return ret;
}