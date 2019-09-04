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
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct necp_session {int /*<<< orphan*/  proc_pid; int /*<<< orphan*/  proc_uuid; scalar_t__ proc_locked; } ;
struct necp_packet_header {int packet_type; int /*<<< orphan*/  message_id; } ;
typedef  int /*<<< orphan*/  proc_uuid ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  header ;
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NECP_ERROR_INVALID_PROCESS ; 
 int /*<<< orphan*/  NECP_ERROR_UNKNOWN_PACKET_TYPE ; 
#define  NECP_PACKET_TYPE_LOCK_SESSION_TO_PROC 138 
#define  NECP_PACKET_TYPE_POLICY_ADD 137 
#define  NECP_PACKET_TYPE_POLICY_APPLY_ALL 136 
#define  NECP_PACKET_TYPE_POLICY_DELETE 135 
#define  NECP_PACKET_TYPE_POLICY_DELETE_ALL 134 
#define  NECP_PACKET_TYPE_POLICY_DUMP_ALL 133 
#define  NECP_PACKET_TYPE_POLICY_GET 132 
#define  NECP_PACKET_TYPE_POLICY_LIST_ALL 131 
#define  NECP_PACKET_TYPE_REGISTER_SERVICE 130 
#define  NECP_PACKET_TYPE_SET_SESSION_PRIORITY 129 
#define  NECP_PACKET_TYPE_UNREGISTER_SERVICE 128 
 int /*<<< orphan*/  current_proc () ; 
 int mbuf_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct necp_packet_header*) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int mbuf_pkthdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  necp_handle_lock_session_to_proc (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_policy_add (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  necp_handle_policy_apply_all (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_policy_delete (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_policy_delete_all (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_policy_dump_all (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_policy_get (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_policy_list_all (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_register_service (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_set_session_priority (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_handle_unregister_service (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  necp_send_error_response (struct necp_session*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_getexecutableuuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  proc_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
necp_ctl_send(kern_ctl_ref kctlref, u_int32_t unit, void *unitinfo, mbuf_t packet, int flags)
{
#pragma unused(kctlref, unit, flags)
	struct necp_session *session = (struct necp_session *)unitinfo;
	struct necp_packet_header header;
	int error = 0;

	if (session == NULL) {
		NECPLOG0(LOG_ERR, "Got a NULL session");
		error = EINVAL;
		goto done;
	}

	if (mbuf_pkthdr_len(packet) < sizeof(header)) {
		NECPLOG(LOG_ERR, "Got a bad packet, length (%lu) < sizeof header (%lu)", mbuf_pkthdr_len(packet), sizeof(header));
		error = EINVAL;
		goto done;
	}

	error = mbuf_copydata(packet, 0, sizeof(header), &header);
	if (error) {
		NECPLOG(LOG_ERR, "mbuf_copydata failed for the header: %d", error);
		error = ENOBUFS;
		goto done;
	}

	if (session->proc_locked) {
		// Verify that the calling process is allowed to send messages
		uuid_t proc_uuid;
		proc_getexecutableuuid(current_proc(), proc_uuid, sizeof(proc_uuid));
		if (uuid_compare(proc_uuid, session->proc_uuid) != 0) {
			necp_send_error_response(session, header.packet_type, header.message_id, NECP_ERROR_INVALID_PROCESS);
			goto done;
		}
	} else {
		// If not locked, update the proc_uuid and proc_pid of the session
		proc_getexecutableuuid(current_proc(), session->proc_uuid, sizeof(session->proc_uuid));
		session->proc_pid = proc_pid(current_proc());
	}

	switch (header.packet_type) {
		case NECP_PACKET_TYPE_POLICY_ADD: {
			necp_handle_policy_add(session, header.message_id, packet, NULL, 0, sizeof(header), NULL);
			break;
		}
		case NECP_PACKET_TYPE_POLICY_GET: {
			necp_handle_policy_get(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_POLICY_DELETE: {
			necp_handle_policy_delete(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_POLICY_APPLY_ALL: {
			necp_handle_policy_apply_all(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_POLICY_LIST_ALL: {
			necp_handle_policy_list_all(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_POLICY_DELETE_ALL: {
			necp_handle_policy_delete_all(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_POLICY_DUMP_ALL: {
			necp_handle_policy_dump_all(session, header.message_id, packet, 0, 0, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_SET_SESSION_PRIORITY: {
			necp_handle_set_session_priority(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_LOCK_SESSION_TO_PROC: {
			necp_handle_lock_session_to_proc(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_REGISTER_SERVICE: {
			necp_handle_register_service(session, header.message_id, packet, sizeof(header));
			break;
		}
		case NECP_PACKET_TYPE_UNREGISTER_SERVICE: {
			necp_handle_unregister_service(session, header.message_id, packet, sizeof(header));
			break;
		}
		default: {
			NECPLOG(LOG_ERR, "Received unknown message type %d", header.packet_type);
			necp_send_error_response(session, header.packet_type, header.message_id, NECP_ERROR_UNKNOWN_PACKET_TYPE);
			break;
		}
	}

done:
	mbuf_freem(packet);
	return (error);
}