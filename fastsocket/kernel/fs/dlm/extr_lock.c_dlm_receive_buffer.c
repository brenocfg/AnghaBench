#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int rc_type; } ;
struct TYPE_8__ {int m_type; } ;
struct dlm_header {int h_cmd; int h_nodeid; int /*<<< orphan*/  h_lockspace; } ;
union dlm_packet {TYPE_1__ rcom; TYPE_3__ message; struct dlm_header header; } ;
struct dlm_ls {int /*<<< orphan*/  ls_recv_active; } ;
struct TYPE_9__ {scalar_t__ ci_log_debug; } ;

/* Variables and functions */
#define  DLM_MSG 129 
#define  DLM_RCOM 128 
 int DLM_RCOM_STATUS ; 
 TYPE_6__ dlm_config ; 
 struct dlm_ls* dlm_find_lockspace_global (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_message_in (TYPE_3__*) ; 
 int /*<<< orphan*/  dlm_put_lockspace (struct dlm_ls*) ; 
 int /*<<< orphan*/  dlm_rcom_in (TYPE_1__*) ; 
 int /*<<< orphan*/  dlm_receive_message (struct dlm_ls*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  dlm_receive_rcom (struct dlm_ls*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dlm_send_ls_not_ready (int,TYPE_1__*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_print (char*,int,int,...) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

void dlm_receive_buffer(union dlm_packet *p, int nodeid)
{
	struct dlm_header *hd = &p->header;
	struct dlm_ls *ls;
	int type = 0;

	switch (hd->h_cmd) {
	case DLM_MSG:
		dlm_message_in(&p->message);
		type = p->message.m_type;
		break;
	case DLM_RCOM:
		dlm_rcom_in(&p->rcom);
		type = p->rcom.rc_type;
		break;
	default:
		log_print("invalid h_cmd %d from %u", hd->h_cmd, nodeid);
		return;
	}

	if (hd->h_nodeid != nodeid) {
		log_print("invalid h_nodeid %d from %d lockspace %x",
			  hd->h_nodeid, nodeid, hd->h_lockspace);
		return;
	}

	ls = dlm_find_lockspace_global(hd->h_lockspace);
	if (!ls) {
		if (dlm_config.ci_log_debug)
			log_print("invalid lockspace %x from %d cmd %d type %d",
				  hd->h_lockspace, nodeid, hd->h_cmd, type);

		if (hd->h_cmd == DLM_RCOM && type == DLM_RCOM_STATUS)
			dlm_send_ls_not_ready(nodeid, &p->rcom);
		return;
	}

	/* this rwsem allows dlm_ls_stop() to wait for all dlm_recv threads to
	   be inactive (in this ls) before transitioning to recovery mode */

	down_read(&ls->ls_recv_active);
	if (hd->h_cmd == DLM_MSG)
		dlm_receive_message(ls, &p->message, nodeid);
	else
		dlm_receive_rcom(ls, &p->rcom, nodeid);
	up_read(&ls->ls_recv_active);

	dlm_put_lockspace(ls);
}