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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct o2net_msg {scalar_t__ buf; } ;
struct dlm_master_request {char* name; unsigned int namelen; int /*<<< orphan*/  node_idx; } ;
struct dlm_master_list_entry {scalar_t__ type; scalar_t__ master; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  maybe_map; int /*<<< orphan*/  new_master; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int state; scalar_t__ owner; TYPE_1__ lockname; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {scalar_t__ node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  master_lock; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_ASSERT_MASTER_MLE_CLEANUP ; 
 int DLM_IVBUFLEN ; 
 unsigned int DLM_LOCKID_NAME_MAX ; 
 int DLM_LOCK_RES_IN_PROGRESS ; 
 int DLM_LOCK_RES_MIGRATING ; 
 scalar_t__ DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int DLM_LOCK_RES_RECOVERING ; 
 int DLM_MASTER_RESP_ERROR ; 
 int DLM_MASTER_RESP_MAYBE ; 
 int DLM_MASTER_RESP_NO ; 
 int DLM_MASTER_RESP_YES ; 
 scalar_t__ DLM_MLE_BLOCK ; 
 scalar_t__ DLM_MLE_MIGRATION ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  __dlm_insert_mle (struct dlm_ctxt*,struct dlm_master_list_entry*) ; 
 struct dlm_lock_resource* __dlm_lookup_lockres (struct dlm_ctxt*,char*,unsigned int,unsigned int) ; 
 int dlm_dispatch_assert_master (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_domain_fully_joined (struct dlm_ctxt*) ; 
 int dlm_find_mle (struct dlm_ctxt*,struct dlm_master_list_entry**,char*,unsigned int) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_init_mle (struct dlm_master_list_entry*,scalar_t__,struct dlm_ctxt*,int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int dlm_lockid_hash (char*,unsigned int) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_set_refmap_bit (int /*<<< orphan*/ ,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_mle_cache ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_put_mle (struct dlm_master_list_entry*) ; 
 scalar_t__ kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dlm_master_list_entry*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_master_request_handler(struct o2net_msg *msg, u32 len, void *data,
			       void **ret_data)
{
	u8 response = DLM_MASTER_RESP_MAYBE;
	struct dlm_ctxt *dlm = data;
	struct dlm_lock_resource *res = NULL;
	struct dlm_master_request *request = (struct dlm_master_request *) msg->buf;
	struct dlm_master_list_entry *mle = NULL, *tmpmle = NULL;
	char *name;
	unsigned int namelen, hash;
	int found, ret;
	int set_maybe;
	int dispatch_assert = 0;

	if (!dlm_grab(dlm))
		return DLM_MASTER_RESP_NO;

	if (!dlm_domain_fully_joined(dlm)) {
		response = DLM_MASTER_RESP_NO;
		goto send_response;
	}

	name = request->name;
	namelen = request->namelen;
	hash = dlm_lockid_hash(name, namelen);

	if (namelen > DLM_LOCKID_NAME_MAX) {
		response = DLM_IVBUFLEN;
		goto send_response;
	}

way_up_top:
	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, name, namelen, hash);
	if (res) {
		spin_unlock(&dlm->spinlock);

		/* take care of the easy cases up front */
		spin_lock(&res->spinlock);
		if (res->state & (DLM_LOCK_RES_RECOVERING|
				  DLM_LOCK_RES_MIGRATING)) {
			spin_unlock(&res->spinlock);
			mlog(0, "returning DLM_MASTER_RESP_ERROR since res is "
			     "being recovered/migrated\n");
			response = DLM_MASTER_RESP_ERROR;
			if (mle)
				kmem_cache_free(dlm_mle_cache, mle);
			goto send_response;
		}

		if (res->owner == dlm->node_num) {
			mlog(0, "%s:%.*s: setting bit %u in refmap\n",
			     dlm->name, namelen, name, request->node_idx);
			dlm_lockres_set_refmap_bit(request->node_idx, res);
			spin_unlock(&res->spinlock);
			response = DLM_MASTER_RESP_YES;
			if (mle)
				kmem_cache_free(dlm_mle_cache, mle);

			/* this node is the owner.
			 * there is some extra work that needs to
			 * happen now.  the requesting node has
			 * caused all nodes up to this one to
			 * create mles.  this node now needs to
			 * go back and clean those up. */
			dispatch_assert = 1;
			goto send_response;
		} else if (res->owner != DLM_LOCK_RES_OWNER_UNKNOWN) {
			spin_unlock(&res->spinlock);
			// mlog(0, "node %u is the master\n", res->owner);
			response = DLM_MASTER_RESP_NO;
			if (mle)
				kmem_cache_free(dlm_mle_cache, mle);
			goto send_response;
		}

		/* ok, there is no owner.  either this node is
		 * being blocked, or it is actively trying to
		 * master this lock. */
		if (!(res->state & DLM_LOCK_RES_IN_PROGRESS)) {
			mlog(ML_ERROR, "lock with no owner should be "
			     "in-progress!\n");
			BUG();
		}

		// mlog(0, "lockres is in progress...\n");
		spin_lock(&dlm->master_lock);
		found = dlm_find_mle(dlm, &tmpmle, name, namelen);
		if (!found) {
			mlog(ML_ERROR, "no mle found for this lock!\n");
			BUG();
		}
		set_maybe = 1;
		spin_lock(&tmpmle->spinlock);
		if (tmpmle->type == DLM_MLE_BLOCK) {
			// mlog(0, "this node is waiting for "
			// "lockres to be mastered\n");
			response = DLM_MASTER_RESP_NO;
		} else if (tmpmle->type == DLM_MLE_MIGRATION) {
			mlog(0, "node %u is master, but trying to migrate to "
			     "node %u.\n", tmpmle->master, tmpmle->new_master);
			if (tmpmle->master == dlm->node_num) {
				mlog(ML_ERROR, "no owner on lockres, but this "
				     "node is trying to migrate it to %u?!\n",
				     tmpmle->new_master);
				BUG();
			} else {
				/* the real master can respond on its own */
				response = DLM_MASTER_RESP_NO;
			}
		} else if (tmpmle->master != DLM_LOCK_RES_OWNER_UNKNOWN) {
			set_maybe = 0;
			if (tmpmle->master == dlm->node_num) {
				response = DLM_MASTER_RESP_YES;
				/* this node will be the owner.
				 * go back and clean the mles on any
				 * other nodes */
				dispatch_assert = 1;
				dlm_lockres_set_refmap_bit(request->node_idx, res);
				mlog(0, "%s:%.*s: setting bit %u in refmap\n",
				     dlm->name, namelen, name,
				     request->node_idx);
			} else
				response = DLM_MASTER_RESP_NO;
		} else {
			// mlog(0, "this node is attempting to "
			// "master lockres\n");
			response = DLM_MASTER_RESP_MAYBE;
		}
		if (set_maybe)
			set_bit(request->node_idx, tmpmle->maybe_map);
		spin_unlock(&tmpmle->spinlock);

		spin_unlock(&dlm->master_lock);
		spin_unlock(&res->spinlock);

		/* keep the mle attached to heartbeat events */
		dlm_put_mle(tmpmle);
		if (mle)
			kmem_cache_free(dlm_mle_cache, mle);
		goto send_response;
	}

	/*
	 * lockres doesn't exist on this node
	 * if there is an MLE_BLOCK, return NO
	 * if there is an MLE_MASTER, return MAYBE
	 * otherwise, add an MLE_BLOCK, return NO
	 */
	spin_lock(&dlm->master_lock);
	found = dlm_find_mle(dlm, &tmpmle, name, namelen);
	if (!found) {
		/* this lockid has never been seen on this node yet */
		// mlog(0, "no mle found\n");
		if (!mle) {
			spin_unlock(&dlm->master_lock);
			spin_unlock(&dlm->spinlock);

			mle = (struct dlm_master_list_entry *)
				kmem_cache_alloc(dlm_mle_cache, GFP_NOFS);
			if (!mle) {
				response = DLM_MASTER_RESP_ERROR;
				mlog_errno(-ENOMEM);
				goto send_response;
			}
			goto way_up_top;
		}

		// mlog(0, "this is second time thru, already allocated, "
		// "add the block.\n");
		dlm_init_mle(mle, DLM_MLE_BLOCK, dlm, NULL, name, namelen);
		set_bit(request->node_idx, mle->maybe_map);
		__dlm_insert_mle(dlm, mle);
		response = DLM_MASTER_RESP_NO;
	} else {
		// mlog(0, "mle was found\n");
		set_maybe = 1;
		spin_lock(&tmpmle->spinlock);
		if (tmpmle->master == dlm->node_num) {
			mlog(ML_ERROR, "no lockres, but an mle with this node as master!\n");
			BUG();
		}
		if (tmpmle->type == DLM_MLE_BLOCK)
			response = DLM_MASTER_RESP_NO;
		else if (tmpmle->type == DLM_MLE_MIGRATION) {
			mlog(0, "migration mle was found (%u->%u)\n",
			     tmpmle->master, tmpmle->new_master);
			/* real master can respond on its own */
			response = DLM_MASTER_RESP_NO;
		} else
			response = DLM_MASTER_RESP_MAYBE;
		if (set_maybe)
			set_bit(request->node_idx, tmpmle->maybe_map);
		spin_unlock(&tmpmle->spinlock);
	}
	spin_unlock(&dlm->master_lock);
	spin_unlock(&dlm->spinlock);

	if (found) {
		/* keep the mle attached to heartbeat events */
		dlm_put_mle(tmpmle);
	}
send_response:
	/*
	 * __dlm_lookup_lockres() grabbed a reference to this lockres.
	 * The reference is released by dlm_assert_master_worker() under
	 * the call to dlm_dispatch_assert_master().  If
	 * dlm_assert_master_worker() isn't called, we drop it here.
	 */
	if (dispatch_assert) {
		if (response != DLM_MASTER_RESP_YES)
			mlog(ML_ERROR, "invalid response %d\n", response);
		if (!res) {
			mlog(ML_ERROR, "bad lockres while trying to assert!\n");
			BUG();
		}
		mlog(0, "%u is the owner of %.*s, cleaning everyone else\n",
			     dlm->node_num, res->lockname.len, res->lockname.name);
		ret = dlm_dispatch_assert_master(dlm, res, 0, request->node_idx, 
						 DLM_ASSERT_MASTER_MLE_CLEANUP);
		if (ret < 0) {
			mlog(ML_ERROR, "failed to dispatch assert master work\n");
			response = DLM_MASTER_RESP_ERROR;
			dlm_lockres_put(res);
		}
	} else {
		if (res)
			dlm_lockres_put(res);
	}

	dlm_put(dlm);
	return response;
}