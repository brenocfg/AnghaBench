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
struct dlm_node_iter {int curnode; } ;
struct dlm_finalize_reco {int node_idx; int /*<<< orphan*/  flags; int /*<<< orphan*/  dead_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  dead_node; } ;
struct dlm_ctxt {int node_num; int /*<<< orphan*/  key; TYPE_1__ reco; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  fr ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_FINALIZE_RECO_MSG ; 
 int /*<<< orphan*/  DLM_FINALIZE_STAGE2 ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_node_iter_init (int /*<<< orphan*/ ,struct dlm_node_iter*) ; 
 int dlm_node_iter_next (struct dlm_node_iter*) ; 
 int /*<<< orphan*/  memset (struct dlm_finalize_reco*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_finalize_reco*,int,int,int*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dlm_send_finalize_reco_message(struct dlm_ctxt *dlm)
{
	int ret = 0;
	struct dlm_finalize_reco fr;
	struct dlm_node_iter iter;
	int nodenum;
	int status;
	int stage = 1;

	mlog(0, "finishing recovery for node %s:%u, "
	     "stage %d\n", dlm->name, dlm->reco.dead_node, stage);

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->domain_map, &iter);
	spin_unlock(&dlm->spinlock);

stage2:
	memset(&fr, 0, sizeof(fr));
	fr.node_idx = dlm->node_num;
	fr.dead_node = dlm->reco.dead_node;
	if (stage == 2)
		fr.flags |= DLM_FINALIZE_STAGE2;

	while ((nodenum = dlm_node_iter_next(&iter)) >= 0) {
		if (nodenum == dlm->node_num)
			continue;
		ret = o2net_send_message(DLM_FINALIZE_RECO_MSG, dlm->key,
					 &fr, sizeof(fr), nodenum, &status);
		if (ret >= 0)
			ret = status;
		if (ret < 0) {
			mlog_errno(ret);
			if (dlm_is_host_down(ret)) {
				/* this has no effect on this recovery 
				 * session, so set the status to zero to 
				 * finish out the last recovery */
				mlog(ML_ERROR, "node %u went down after this "
				     "node finished recovery.\n", nodenum);
				ret = 0;
				continue;
			}
			break;
		}
	}
	if (stage == 1) {
		/* reset the node_iter back to the top and send finalize2 */
		iter.curnode = -1;
		stage = 2;
		goto stage2;
	}

	return ret;
}