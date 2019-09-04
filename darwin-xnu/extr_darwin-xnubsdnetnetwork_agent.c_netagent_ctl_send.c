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
struct netagent_session {int dummy; } ;
struct netagent_message_header {int message_type; int /*<<< orphan*/  message_id; int /*<<< orphan*/  message_payload_length; } ;
typedef  int /*<<< orphan*/  mbuf_t ;
typedef  int /*<<< orphan*/  kern_ctl_ref ;
typedef  int /*<<< orphan*/  header ;
typedef  int errno_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETAGENT_MESSAGE_ERROR_UNKNOWN_TYPE ; 
#define  NETAGENT_MESSAGE_TYPE_ASSERT 134 
#define  NETAGENT_MESSAGE_TYPE_ASSIGN_NEXUS 133 
#define  NETAGENT_MESSAGE_TYPE_GET 132 
#define  NETAGENT_MESSAGE_TYPE_REGISTER 131 
#define  NETAGENT_MESSAGE_TYPE_UNASSERT 130 
#define  NETAGENT_MESSAGE_TYPE_UNREGISTER 129 
#define  NETAGENT_MESSAGE_TYPE_UPDATE 128 
 int mbuf_copydata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct netagent_message_header*) ; 
 int /*<<< orphan*/  mbuf_freem (int /*<<< orphan*/ ) ; 
 int mbuf_pkthdr_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netagent_handle_assign_nexus_message (struct netagent_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netagent_handle_get (struct netagent_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netagent_handle_register_message (struct netagent_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netagent_handle_unregister_message (struct netagent_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netagent_handle_update_message (struct netagent_session*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netagent_send_error_response (struct netagent_session*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static errno_t
netagent_ctl_send(kern_ctl_ref kctlref, u_int32_t unit, void *unitinfo, mbuf_t packet, int flags)
{
#pragma unused(kctlref, unit, flags)
	struct netagent_session *session = (struct netagent_session *)unitinfo;
	struct netagent_message_header header;
	int error = 0;

	if (session == NULL) {
		NETAGENTLOG0(LOG_ERR, "Got a NULL session");
		error = EINVAL;
		goto done;
	}

	if (mbuf_pkthdr_len(packet) < sizeof(header)) {
		NETAGENTLOG(LOG_ERR, "Got a bad packet, length (%lu) < sizeof header (%lu)",
					mbuf_pkthdr_len(packet), sizeof(header));
		error = EINVAL;
		goto done;
	}

	error = mbuf_copydata(packet, 0, sizeof(header), &header);
	if (error) {
		NETAGENTLOG(LOG_ERR, "mbuf_copydata failed for the header: %d", error);
		error = ENOBUFS;
		goto done;
	}

	switch (header.message_type) {
		case NETAGENT_MESSAGE_TYPE_REGISTER: {
			netagent_handle_register_message(session, header.message_id, header.message_payload_length,
									         packet, sizeof(header));
			break;
		}
		case NETAGENT_MESSAGE_TYPE_UNREGISTER: {
			netagent_handle_unregister_message(session, header.message_id, header.message_payload_length,
											   packet, sizeof(header));
			break;
		}
		case NETAGENT_MESSAGE_TYPE_UPDATE: {
			netagent_handle_update_message(session, header.message_id, header.message_payload_length,
								   packet, sizeof(header));
			break;
		}
		case NETAGENT_MESSAGE_TYPE_GET: {
			netagent_handle_get(session, header.message_id, header.message_payload_length,
								packet, sizeof(header));
			break;
		}
		case NETAGENT_MESSAGE_TYPE_ASSERT: {
			NETAGENTLOG0(LOG_ERR, "NETAGENT_MESSAGE_TYPE_ASSERT no longer supported");
			break;
		}
		case NETAGENT_MESSAGE_TYPE_UNASSERT: {
			NETAGENTLOG0(LOG_ERR, "NETAGENT_MESSAGE_TYPE_UNASSERT no longer supported");
			break;
		}
		case NETAGENT_MESSAGE_TYPE_ASSIGN_NEXUS: {
			netagent_handle_assign_nexus_message(session, header.message_id, header.message_payload_length,
												 packet, sizeof(header));
			break;
		}
		default: {
			NETAGENTLOG(LOG_ERR, "Received unknown message type %d", header.message_type);
			netagent_send_error_response(session, header.message_type, header.message_id,
										 NETAGENT_MESSAGE_ERROR_UNKNOWN_TYPE);
			break;
		}
	}

done:
	mbuf_freem(packet);
	return (error);
}