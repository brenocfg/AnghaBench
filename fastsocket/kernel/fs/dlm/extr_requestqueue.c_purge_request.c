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
typedef  int uint32_t ;
struct dlm_message {int m_type; int /*<<< orphan*/  m_hash; } ;
struct dlm_ls {int /*<<< orphan*/  ls_count; } ;

/* Variables and functions */
#define  DLM_MSG_CANCEL 136 
#define  DLM_MSG_CANCEL_REPLY 135 
#define  DLM_MSG_CONVERT 134 
#define  DLM_MSG_CONVERT_REPLY 133 
#define  DLM_MSG_GRANT 132 
 int DLM_MSG_LOOKUP ; 
 int DLM_MSG_LOOKUP_REPLY ; 
 int DLM_MSG_REMOVE ; 
#define  DLM_MSG_REQUEST 131 
#define  DLM_MSG_REQUEST_REPLY 130 
#define  DLM_MSG_UNLOCK 129 
#define  DLM_MSG_UNLOCK_REPLY 128 
 int dlm_hash2nodeid (struct dlm_ls*,int /*<<< orphan*/ ) ; 
 scalar_t__ dlm_is_removed (struct dlm_ls*,int) ; 
 int /*<<< orphan*/  dlm_no_directory (struct dlm_ls*) ; 
 int dlm_our_nodeid () ; 

__attribute__((used)) static int purge_request(struct dlm_ls *ls, struct dlm_message *ms, int nodeid)
{
	uint32_t type = ms->m_type;

	/* the ls is being cleaned up and freed by release_lockspace */
	if (!ls->ls_count)
		return 1;

	if (dlm_is_removed(ls, nodeid))
		return 1;

	/* directory operations are always purged because the directory is
	   always rebuilt during recovery and the lookups resent */

	if (type == DLM_MSG_REMOVE ||
	    type == DLM_MSG_LOOKUP ||
	    type == DLM_MSG_LOOKUP_REPLY)
		return 1;

	if (!dlm_no_directory(ls))
		return 0;

	/* with no directory, the master is likely to change as a part of
	   recovery; requests to/from the defunct master need to be purged */

	switch (type) {
	case DLM_MSG_REQUEST:
	case DLM_MSG_CONVERT:
	case DLM_MSG_UNLOCK:
	case DLM_MSG_CANCEL:
		/* we're no longer the master of this resource, the sender
		   will resend to the new master (see waiter_needs_recovery) */

		if (dlm_hash2nodeid(ls, ms->m_hash) != dlm_our_nodeid())
			return 1;
		break;

	case DLM_MSG_REQUEST_REPLY:
	case DLM_MSG_CONVERT_REPLY:
	case DLM_MSG_UNLOCK_REPLY:
	case DLM_MSG_CANCEL_REPLY:
	case DLM_MSG_GRANT:
		/* this reply is from the former master of the resource,
		   we'll resend to the new master if needed */

		if (dlm_hash2nodeid(ls, ms->m_hash) != nodeid)
			return 1;
		break;
	}

	return 0;
}