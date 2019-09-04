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
struct netagent_session {TYPE_2__* wrapper; } ;
typedef  scalar_t__ netagent_session_t ;
typedef  int errno_t ;
struct TYPE_3__ {int /*<<< orphan*/  netagent_uuid; } ;
struct TYPE_4__ {TYPE_1__ netagent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int necp_assign_client_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 

errno_t
netagent_assign_nexus(netagent_session_t _session, uuid_t necp_client_uuid,
					  void *assign_message, size_t assigned_results_length)
{
	struct netagent_session *session = (struct netagent_session *)_session;
	if (session == NULL) {
		NETAGENTLOG0(LOG_ERR, "Cannot assign nexus from NULL session");
		return EINVAL;
	}

	if (session->wrapper == NULL) {
		NETAGENTLOG0(LOG_ERR, "Session has no agent");
		return ENOENT;
	}

	// Note that if the error is 0, NECP has taken over our malloc'ed buffer
	int error = necp_assign_client_result(session->wrapper->netagent.netagent_uuid, necp_client_uuid, assign_message, assigned_results_length);
	if (error) {
		// necp_assign_client_result returns POSIX errors; don't error for ENOENT
		NETAGENTLOG((error == ENOENT ? LOG_DEBUG : LOG_ERR), "Client assignment failed: %d", error);
		return error;
	}

	NETAGENTLOG0(LOG_DEBUG, "Agent assigned nexus properties to client");
	return 0;
}