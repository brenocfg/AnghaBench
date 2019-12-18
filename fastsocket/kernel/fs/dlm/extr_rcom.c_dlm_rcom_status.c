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
struct dlm_rcom {int /*<<< orphan*/  rc_result; int /*<<< orphan*/  rc_id; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_ls {int ls_recover_nodeid; struct dlm_rcom* ls_recover_buf; } ;
struct TYPE_2__ {int /*<<< orphan*/  ci_buffer_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RCOM_STATUS ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  allow_sync_reply (struct dlm_ls*,int /*<<< orphan*/ *) ; 
 int check_config (struct dlm_ls*,struct dlm_rcom*,int) ; 
 int create_rcom (struct dlm_ls*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_rcom**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  disallow_sync_reply (struct dlm_ls*) ; 
 TYPE_1__ dlm_config ; 
 int dlm_our_nodeid () ; 
 int /*<<< orphan*/  dlm_recover_status (struct dlm_ls*) ; 
 int dlm_wait_function (struct dlm_ls*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int) ; 
 int /*<<< orphan*/  memset (struct dlm_rcom*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcom_response ; 
 int /*<<< orphan*/  send_rcom (struct dlm_ls*,struct dlm_mhandle*,struct dlm_rcom*) ; 

int dlm_rcom_status(struct dlm_ls *ls, int nodeid)
{
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	int error = 0;

	ls->ls_recover_nodeid = nodeid;

	if (nodeid == dlm_our_nodeid()) {
		rc = ls->ls_recover_buf;
		rc->rc_result = dlm_recover_status(ls);
		goto out;
	}

	error = create_rcom(ls, nodeid, DLM_RCOM_STATUS, 0, &rc, &mh);
	if (error)
		goto out;

	allow_sync_reply(ls, &rc->rc_id);
	memset(ls->ls_recover_buf, 0, dlm_config.ci_buffer_size);

	send_rcom(ls, mh, rc);

	error = dlm_wait_function(ls, &rcom_response);
	disallow_sync_reply(ls);
	if (error)
		goto out;

	rc = ls->ls_recover_buf;

	if (rc->rc_result == -ESRCH) {
		/* we pretend the remote lockspace exists with 0 status */
		log_debug(ls, "remote node %d not ready", nodeid);
		rc->rc_result = 0;
	} else
		error = check_config(ls, rc, nodeid);
	/* the caller looks at rc_result for the remote recovery status */
 out:
	return error;
}