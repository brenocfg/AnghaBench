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
typedef  int /*<<< orphan*/  u8 ;
struct dlm_node_iter {int dummy; } ;
struct dlm_lock_resource {int dummy; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  name; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  recovery_map; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int EAGAIN ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int dlm_do_master_requery (struct dlm_ctxt*,struct dlm_lock_resource*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_node_iter_init (int /*<<< orphan*/ ,struct dlm_node_iter*) ; 
 int dlm_node_iter_next (struct dlm_node_iter*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_pre_master_reco_lockres(struct dlm_ctxt *dlm,
				       struct dlm_lock_resource *res)
{
	struct dlm_node_iter iter;
	int nodenum;
	int ret = 0;
	u8 master = DLM_LOCK_RES_OWNER_UNKNOWN;

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->domain_map, &iter);
	spin_unlock(&dlm->spinlock);

	while ((nodenum = dlm_node_iter_next(&iter)) >= 0) {
		/* do not send to self */
		if (nodenum == dlm->node_num)
			continue;
		ret = dlm_do_master_requery(dlm, res, nodenum, &master);
		if (ret < 0) {
			mlog_errno(ret);
			if (!dlm_is_host_down(ret))
				BUG();
			/* host is down, so answer for that node would be
			 * DLM_LOCK_RES_OWNER_UNKNOWN.  continue. */
			ret = 0;
		}

		if (master != DLM_LOCK_RES_OWNER_UNKNOWN) {
			/* check to see if this master is in the recovery map */
			spin_lock(&dlm->spinlock);
			if (test_bit(master, dlm->recovery_map)) {
				mlog(ML_NOTICE, "%s: node %u has not seen "
				     "node %u go down yet, and thinks the "
				     "dead node is mastering the recovery "
				     "lock.  must wait.\n", dlm->name,
				     nodenum, master);
				ret = -EAGAIN;
			}
			spin_unlock(&dlm->spinlock);
			mlog(0, "%s: reco lock master is %u\n", dlm->name, 
			     master);
			break;
		}
	}
	return ret;
}