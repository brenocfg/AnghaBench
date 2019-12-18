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
struct dlm_reco_data_done {int /*<<< orphan*/  dead_node; int /*<<< orphan*/  node_idx; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  key; int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  done_msg ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_RECO_DATA_DONE_MSG ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  memset (struct dlm_reco_data_done*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_reco_data_done*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int dlm_send_all_done_msg(struct dlm_ctxt *dlm, u8 dead_node, u8 send_to)
{
	int ret, tmpret;
	struct dlm_reco_data_done done_msg;

	memset(&done_msg, 0, sizeof(done_msg));
	done_msg.node_idx = dlm->node_num;
	done_msg.dead_node = dead_node;
	mlog(0, "sending DATA DONE message to %u, "
	     "my node=%u, dead node=%u\n", send_to, done_msg.node_idx,
	     done_msg.dead_node);

	ret = o2net_send_message(DLM_RECO_DATA_DONE_MSG, dlm->key, &done_msg,
				 sizeof(done_msg), send_to, &tmpret);
	if (ret < 0) {
		if (!dlm_is_host_down(ret)) {
			mlog_errno(ret);
			mlog(ML_ERROR, "%s: unknown error sending data-done "
			     "to %u\n", dlm->name, send_to);
			BUG();
		}
	} else
		ret = tmpret;
	return ret;
}