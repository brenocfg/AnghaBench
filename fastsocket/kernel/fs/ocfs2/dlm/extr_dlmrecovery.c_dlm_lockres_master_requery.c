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
typedef  scalar_t__ u8 ;
struct dlm_node_iter {int dummy; } ;
struct dlm_lock_resource {int dummy; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int dlm_do_master_requery (struct dlm_ctxt*,struct dlm_lock_resource*,int,scalar_t__*) ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_node_iter_init (int /*<<< orphan*/ ,struct dlm_node_iter*) ; 
 int dlm_node_iter_next (struct dlm_node_iter*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_lockres_master_requery(struct dlm_ctxt *dlm,
				      struct dlm_lock_resource *res,
				      u8 *real_master)
{
	struct dlm_node_iter iter;
	int nodenum;
	int ret = 0;

	*real_master = DLM_LOCK_RES_OWNER_UNKNOWN;

	/* we only reach here if one of the two nodes in a
	 * migration died while the migration was in progress.
	 * at this point we need to requery the master.  we
	 * know that the new_master got as far as creating
	 * an mle on at least one node, but we do not know
	 * if any nodes had actually cleared the mle and set
	 * the master to the new_master.  the old master
	 * is supposed to set the owner to UNKNOWN in the
	 * event of a new_master death, so the only possible
	 * responses that we can get from nodes here are
	 * that the master is new_master, or that the master
	 * is UNKNOWN.
	 * if all nodes come back with UNKNOWN then we know
	 * the lock needs remastering here.
	 * if any node comes back with a valid master, check
	 * to see if that master is the one that we are
	 * recovering.  if so, then the new_master died and
	 * we need to remaster this lock.  if not, then the
	 * new_master survived and that node will respond to
	 * other nodes about the owner.
	 * if there is an owner, this node needs to dump this
	 * lockres and alert the sender that this lockres
	 * was rejected. */
	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->domain_map, &iter);
	spin_unlock(&dlm->spinlock);

	while ((nodenum = dlm_node_iter_next(&iter)) >= 0) {
		/* do not send to self */
		if (nodenum == dlm->node_num)
			continue;
		ret = dlm_do_master_requery(dlm, res, nodenum, real_master);
		if (ret < 0) {
			mlog_errno(ret);
			if (!dlm_is_host_down(ret))
				BUG();
			/* host is down, so answer for that node would be
			 * DLM_LOCK_RES_OWNER_UNKNOWN.  continue. */
		}
		if (*real_master != DLM_LOCK_RES_OWNER_UNKNOWN) {
			mlog(0, "lock master is %u\n", *real_master);
			break;
		}
	}
	return ret;
}