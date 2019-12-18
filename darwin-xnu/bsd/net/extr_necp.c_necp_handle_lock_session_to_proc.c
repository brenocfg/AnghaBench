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
typedef  int /*<<< orphan*/  u_int32_t ;
struct necp_session {int /*<<< orphan*/  proc_locked; } ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NECP_PACKET_TYPE_LOCK_SESSION_TO_PROC ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  necp_send_success_response (struct necp_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
necp_handle_lock_session_to_proc(struct necp_session *session, u_int32_t message_id, mbuf_t packet, int offset)
{
#pragma unused(packet, offset)
	// proc_uuid already filled out
	session->proc_locked = TRUE;
	necp_send_success_response(session, NECP_PACKET_TYPE_LOCK_SESSION_TO_PROC, message_id);
}