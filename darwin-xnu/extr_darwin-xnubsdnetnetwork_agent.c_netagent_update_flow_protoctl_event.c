#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct netagent_session {TYPE_2__* wrapper; } ;
typedef  scalar_t__ netagent_session_t ;
typedef  int errno_t ;
struct TYPE_3__ {int /*<<< orphan*/  netagent_uuid; } ;
struct TYPE_4__ {TYPE_1__ netagent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int necp_update_flow_protoctl_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

errno_t
netagent_update_flow_protoctl_event(netagent_session_t _session,
    uuid_t client_id, uint32_t protoctl_event_code,
    uint32_t protoctl_event_val, uint32_t protoctl_event_tcp_seq_number)
{
	struct netagent_session *session = (struct netagent_session *)_session;
	int error = 0;

	if (session == NULL) {
		NETAGENTLOG0(LOG_ERR, "Cannot assign nexus from NULL session");
		return (EINVAL);
	}

	if (session->wrapper == NULL) {
		NETAGENTLOG0(LOG_ERR, "Session has no agent");
		return (ENOENT);
	}

	error = necp_update_flow_protoctl_event(session->wrapper->netagent.netagent_uuid,
	    client_id, protoctl_event_code, protoctl_event_val, protoctl_event_tcp_seq_number);

	return (error);
}