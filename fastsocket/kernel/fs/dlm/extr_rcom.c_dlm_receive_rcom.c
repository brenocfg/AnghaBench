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
struct rcom_lock {int dummy; } ;
struct TYPE_2__ {int h_length; } ;
struct dlm_rcom {int rc_type; TYPE_1__ rc_header; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
#define  DLM_RCOM_LOCK 135 
#define  DLM_RCOM_LOCK_REPLY 134 
#define  DLM_RCOM_LOOKUP 133 
#define  DLM_RCOM_LOOKUP_REPLY 132 
#define  DLM_RCOM_NAMES 131 
#define  DLM_RCOM_NAMES_REPLY 130 
#define  DLM_RCOM_STATUS 129 
#define  DLM_RCOM_STATUS_REPLY 128 
 int /*<<< orphan*/  dlm_recover_process_copy (struct dlm_ls*,struct dlm_rcom*) ; 
 scalar_t__ dlm_recovery_stopped (struct dlm_ls*) ; 
 scalar_t__ is_old_reply (struct dlm_ls*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int,int) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int,...) ; 
 int /*<<< orphan*/  receive_rcom_lock (struct dlm_ls*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  receive_rcom_lookup (struct dlm_ls*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  receive_rcom_lookup_reply (struct dlm_ls*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  receive_rcom_names (struct dlm_ls*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  receive_rcom_status (struct dlm_ls*,struct dlm_rcom*) ; 
 int /*<<< orphan*/  receive_sync_reply (struct dlm_ls*,struct dlm_rcom*) ; 

void dlm_receive_rcom(struct dlm_ls *ls, struct dlm_rcom *rc, int nodeid)
{
	int lock_size = sizeof(struct dlm_rcom) + sizeof(struct rcom_lock);

	if (dlm_recovery_stopped(ls) && (rc->rc_type != DLM_RCOM_STATUS)) {
		log_debug(ls, "ignoring recovery message %x from %d",
			  rc->rc_type, nodeid);
		goto out;
	}

	if (is_old_reply(ls, rc))
		goto out;

	switch (rc->rc_type) {
	case DLM_RCOM_STATUS:
		receive_rcom_status(ls, rc);
		break;

	case DLM_RCOM_NAMES:
		receive_rcom_names(ls, rc);
		break;

	case DLM_RCOM_LOOKUP:
		receive_rcom_lookup(ls, rc);
		break;

	case DLM_RCOM_LOCK:
		if (rc->rc_header.h_length < lock_size)
			goto Eshort;
		receive_rcom_lock(ls, rc);
		break;

	case DLM_RCOM_STATUS_REPLY:
		receive_sync_reply(ls, rc);
		break;

	case DLM_RCOM_NAMES_REPLY:
		receive_sync_reply(ls, rc);
		break;

	case DLM_RCOM_LOOKUP_REPLY:
		receive_rcom_lookup_reply(ls, rc);
		break;

	case DLM_RCOM_LOCK_REPLY:
		if (rc->rc_header.h_length < lock_size)
			goto Eshort;
		dlm_recover_process_copy(ls, rc);
		break;

	default:
		log_error(ls, "receive_rcom bad type %d", rc->rc_type);
	}
out:
	return;
Eshort:
	log_error(ls, "recovery message %x from %d is too short",
			  rc->rc_type, nodeid);
}