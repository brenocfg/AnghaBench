#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dlm_rcom {int /*<<< orphan*/  rc_id; int /*<<< orphan*/  rc_buf; } ;
struct dlm_mhandle {int dummy; } ;
struct dlm_ls {int ls_recover_nodeid; TYPE_2__* ls_recover_buf; } ;
struct TYPE_6__ {int ci_buffer_size; } ;
struct TYPE_4__ {int h_length; } ;
struct TYPE_5__ {int /*<<< orphan*/  rc_buf; TYPE_1__ rc_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_RCOM_NAMES ; 
 int /*<<< orphan*/  allow_sync_reply (struct dlm_ls*,int /*<<< orphan*/ *) ; 
 int create_rcom (struct dlm_ls*,int,int /*<<< orphan*/ ,int,struct dlm_rcom**,struct dlm_mhandle**) ; 
 int /*<<< orphan*/  disallow_sync_reply (struct dlm_ls*) ; 
 TYPE_3__ dlm_config ; 
 int /*<<< orphan*/  dlm_copy_master_names (struct dlm_ls*,char*,int,int /*<<< orphan*/ ,int,int) ; 
 int dlm_our_nodeid () ; 
 int dlm_wait_function (struct dlm_ls*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcom_response ; 
 int /*<<< orphan*/  send_rcom (struct dlm_ls*,struct dlm_mhandle*,struct dlm_rcom*) ; 

int dlm_rcom_names(struct dlm_ls *ls, int nodeid, char *last_name, int last_len)
{
	struct dlm_rcom *rc;
	struct dlm_mhandle *mh;
	int error = 0;
	int max_size = dlm_config.ci_buffer_size - sizeof(struct dlm_rcom);

	ls->ls_recover_nodeid = nodeid;

	if (nodeid == dlm_our_nodeid()) {
		ls->ls_recover_buf->rc_header.h_length =
			dlm_config.ci_buffer_size;
		dlm_copy_master_names(ls, last_name, last_len,
		                      ls->ls_recover_buf->rc_buf,
		                      max_size, nodeid);
		goto out;
	}

	error = create_rcom(ls, nodeid, DLM_RCOM_NAMES, last_len, &rc, &mh);
	if (error)
		goto out;
	memcpy(rc->rc_buf, last_name, last_len);

	allow_sync_reply(ls, &rc->rc_id);
	memset(ls->ls_recover_buf, 0, dlm_config.ci_buffer_size);

	send_rcom(ls, mh, rc);

	error = dlm_wait_function(ls, &rcom_response);
	disallow_sync_reply(ls);
 out:
	return error;
}