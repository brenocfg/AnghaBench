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
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  node_num; } ;
struct dlm_cancel_join {int /*<<< orphan*/  name_len; int /*<<< orphan*/  domain; int /*<<< orphan*/  node_idx; } ;
typedef  int /*<<< orphan*/  cancel_msg ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_CANCEL_JOIN_MSG ; 
 int /*<<< orphan*/  DLM_MOD_KEY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_cancel_join*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_cancel_join*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_send_one_join_cancel(struct dlm_ctxt *dlm,
				    unsigned int node)
{
	int status;
	struct dlm_cancel_join cancel_msg;

	memset(&cancel_msg, 0, sizeof(cancel_msg));
	cancel_msg.node_idx = dlm->node_num;
	cancel_msg.name_len = strlen(dlm->name);
	memcpy(cancel_msg.domain, dlm->name, cancel_msg.name_len);

	status = o2net_send_message(DLM_CANCEL_JOIN_MSG, DLM_MOD_KEY,
				    &cancel_msg, sizeof(cancel_msg), node,
				    NULL);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}

bail:
	return status;
}