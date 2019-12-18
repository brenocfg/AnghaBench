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
typedef  int /*<<< orphan*/  use_count ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
struct netagent_session {TYPE_1__* wrapper; } ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_2__ {int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netagent_lock ; 

errno_t
netagent_handle_use_count_setopt(struct netagent_session *session, u_int8_t *payload, size_t payload_length)
{
	errno_t response_error = 0;
	uint64_t use_count = 0;

	if (session == NULL) {
		NETAGENTLOG0(LOG_ERR, "Failed to find session");
		response_error = ENOENT;
		goto done;
	}

	if (payload == NULL) {
		NETAGENTLOG0(LOG_ERR, "No payload received");
		response_error = EINVAL;
		goto done;
	}

	if (payload_length != sizeof(use_count)) {
		NETAGENTLOG(LOG_ERR, "Payload length is invalid (%lu)", payload_length);
		response_error = EINVAL;
		goto done;
	}

	memcpy(&use_count, payload, sizeof(use_count));

	lck_rw_lock_shared(&netagent_lock);

	if (session->wrapper == NULL) {
		NETAGENTLOG0(LOG_ERR, "Session has no agent registered");
		response_error = ENOENT;
		lck_rw_done(&netagent_lock);
		goto done;
	}

	session->wrapper->use_count = use_count;

	lck_rw_done(&netagent_lock);

done:
	return response_error;
}