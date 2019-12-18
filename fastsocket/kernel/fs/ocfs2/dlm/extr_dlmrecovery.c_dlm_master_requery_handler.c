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
struct dlm_master_requery {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct dlm_lock_resource {int owner; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_ASSERT_MASTER_REQUERY ; 
 int DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dlm_lock_resource* __dlm_lookup_lockres (struct dlm_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int dlm_dispatch_assert_master (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_grab (struct dlm_ctxt*) ; 
 unsigned int dlm_lockid_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_put (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  mlog_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_master_requery_handler(struct o2net_msg *msg, u32 len, void *data,
			       void **ret_data)
{
	struct dlm_ctxt *dlm = data;
	struct dlm_master_requery *req = (struct dlm_master_requery *)msg->buf;
	struct dlm_lock_resource *res = NULL;
	unsigned int hash;
	int master = DLM_LOCK_RES_OWNER_UNKNOWN;
	u32 flags = DLM_ASSERT_MASTER_REQUERY;

	if (!dlm_grab(dlm)) {
		/* since the domain has gone away on this
		 * node, the proper response is UNKNOWN */
		return master;
	}

	hash = dlm_lockid_hash(req->name, req->namelen);

	spin_lock(&dlm->spinlock);
	res = __dlm_lookup_lockres(dlm, req->name, req->namelen, hash);
	if (res) {
		spin_lock(&res->spinlock);
		master = res->owner;
		if (master == dlm->node_num) {
			int ret = dlm_dispatch_assert_master(dlm, res,
							     0, 0, flags);
			if (ret < 0) {
				mlog_errno(-ENOMEM);
				/* retry!? */
				BUG();
			}
		} else /* put.. incase we are not the master */
			dlm_lockres_put(res);
		spin_unlock(&res->spinlock);
	}
	spin_unlock(&dlm->spinlock);

	dlm_put(dlm);
	return master;
}