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
typedef  int /*<<< orphan*/  u32 ;
struct o2net_msg {scalar_t__ buf; } ;
struct dlm_migrate_request {char* name; unsigned int namelen; int /*<<< orphan*/  master; int /*<<< orphan*/  new_master; } ;
struct dlm_master_list_entry {int dummy; } ;
struct dlm_lock_resource {int state; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  master_lock; } ;

/* Variables and functions */
 int DLM_LOCK_RES_MIGRATING ; 
 int DLM_LOCK_RES_RECOVERING ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 struct dlm_lock_resource* __dlm_lookup_lockres (struct dlm_ctxt*,char const*,unsigned int,unsigned int) ; 
 int dlm_add_migration_mle (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_master_list_entry*,struct dlm_master_list_entry**,char const*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 unsigned int dlm_lockid_hash (char const*,unsigned int) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_mle_cache ; 
 int /*<<< orphan*/  dlm_mle_detach_hb_events (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_put_mle (struct dlm_master_list_entry*) ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_migrate_request_handler(struct o2net_msg *msg, u32 len, void *data,
				void **ret_data)
{
	struct dlm_ctxt *dlm = data;
	struct dlm_lock_resource *res = NULL;
	struct dlm_migrate_request *migrate = (struct dlm_migrate_request *) msg->buf;
	struct dlm_master_list_entry *mle = NULL, *oldmle = NULL;
	const char *name;
	unsigned int namelen, hash;
	int ret = 0;

	if (!dlm_grab(dlm))
		return -EINVAL;

	name = migrate->name;
	namelen = migrate->namelen;
	hash = dlm_lockid_hash(name, namelen);

	/* preallocate.. if this fails, abort */
	mle = (struct dlm_master_list_entry *) kmem_cache_alloc(dlm_mle_cache,
							 GFP_NOFS);

	if (!mle) {
		ret = -ENOMEM;
		goto leave;
	}

	/* check for pre-existing lock */
	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, name, namelen, hash);
	spin_lock(&dlm->master_lock);

	if (res) {
		spin_lock(&res->spinlock);
		if (res->state & DLM_LOCK_RES_RECOVERING) {
			/* if all is working ok, this can only mean that we got
		 	* a migrate request from a node that we now see as
		 	* dead.  what can we do here?  drop it to the floor? */
			spin_unlock(&res->spinlock);
			mlog(ML_ERROR, "Got a migrate request, but the "
			     "lockres is marked as recovering!");
			kmem_cache_free(dlm_mle_cache, mle);
			ret = -EINVAL; /* need a better solution */
			goto unlock;
		}
		res->state |= DLM_LOCK_RES_MIGRATING;
		spin_unlock(&res->spinlock);
	}

	/* ignore status.  only nonzero status would BUG. */
	ret = dlm_add_migration_mle(dlm, res, mle, &oldmle,
				    name, namelen,
				    migrate->new_master,
				    migrate->master);

unlock:
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

	if (oldmle) {
		/* master is known, detach if not already detached */
		dlm_mle_detach_hb_events(dlm, oldmle);
		dlm_put_mle(oldmle);
	}

	if (res)
		dlm_lockres_put(res);
leave:
	dlm_put(dlm);
	return ret;
}