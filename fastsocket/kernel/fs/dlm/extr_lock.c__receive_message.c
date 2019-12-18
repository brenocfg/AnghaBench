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
struct TYPE_2__ {int /*<<< orphan*/  h_nodeid; } ;
struct dlm_message {int m_type; int /*<<< orphan*/  m_result; int /*<<< orphan*/  m_remid; int /*<<< orphan*/  m_lkid; TYPE_1__ m_header; } ;
struct dlm_ls {int dummy; } ;

/* Variables and functions */
#define  DLM_MSG_BAST 141 
#define  DLM_MSG_CANCEL 140 
#define  DLM_MSG_CANCEL_REPLY 139 
#define  DLM_MSG_CONVERT 138 
#define  DLM_MSG_CONVERT_REPLY 137 
#define  DLM_MSG_GRANT 136 
#define  DLM_MSG_LOOKUP 135 
#define  DLM_MSG_LOOKUP_REPLY 134 
#define  DLM_MSG_PURGE 133 
#define  DLM_MSG_REMOVE 132 
#define  DLM_MSG_REQUEST 131 
#define  DLM_MSG_REQUEST_REPLY 130 
#define  DLM_MSG_UNLOCK 129 
#define  DLM_MSG_UNLOCK_REPLY 128 
 int /*<<< orphan*/  dlm_astd_wake () ; 
 int /*<<< orphan*/  dlm_is_member (struct dlm_ls*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (struct dlm_ls*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error (struct dlm_ls*,char*,int) ; 
 int /*<<< orphan*/  receive_bast (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_cancel (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_cancel_reply (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_convert (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_convert_reply (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_grant (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_lookup (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_lookup_reply (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_purge (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_remove (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_request (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_request_reply (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_unlock (struct dlm_ls*,struct dlm_message*) ; 
 int /*<<< orphan*/  receive_unlock_reply (struct dlm_ls*,struct dlm_message*) ; 

__attribute__((used)) static void _receive_message(struct dlm_ls *ls, struct dlm_message *ms)
{
	if (!dlm_is_member(ls, ms->m_header.h_nodeid)) {
		log_debug(ls, "ignore non-member message %d from %d %x %x %d",
			  ms->m_type, ms->m_header.h_nodeid, ms->m_lkid,
			  ms->m_remid, ms->m_result);
		return;
	}

	switch (ms->m_type) {

	/* messages sent to a master node */

	case DLM_MSG_REQUEST:
		receive_request(ls, ms);
		break;

	case DLM_MSG_CONVERT:
		receive_convert(ls, ms);
		break;

	case DLM_MSG_UNLOCK:
		receive_unlock(ls, ms);
		break;

	case DLM_MSG_CANCEL:
		receive_cancel(ls, ms);
		break;

	/* messages sent from a master node (replies to above) */

	case DLM_MSG_REQUEST_REPLY:
		receive_request_reply(ls, ms);
		break;

	case DLM_MSG_CONVERT_REPLY:
		receive_convert_reply(ls, ms);
		break;

	case DLM_MSG_UNLOCK_REPLY:
		receive_unlock_reply(ls, ms);
		break;

	case DLM_MSG_CANCEL_REPLY:
		receive_cancel_reply(ls, ms);
		break;

	/* messages sent from a master node (only two types of async msg) */

	case DLM_MSG_GRANT:
		receive_grant(ls, ms);
		break;

	case DLM_MSG_BAST:
		receive_bast(ls, ms);
		break;

	/* messages sent to a dir node */

	case DLM_MSG_LOOKUP:
		receive_lookup(ls, ms);
		break;

	case DLM_MSG_REMOVE:
		receive_remove(ls, ms);
		break;

	/* messages sent from a dir node (remove has no reply) */

	case DLM_MSG_LOOKUP_REPLY:
		receive_lookup_reply(ls, ms);
		break;

	/* other messages */

	case DLM_MSG_PURGE:
		receive_purge(ls, ms);
		break;

	default:
		log_error(ls, "unknown message type %d", ms->m_type);
	}

	dlm_astd_wake();
}