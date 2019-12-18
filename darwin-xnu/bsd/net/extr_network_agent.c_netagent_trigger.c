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
typedef  int /*<<< orphan*/  uuid_t ;
struct proc {int dummy; } ;
struct TYPE_2__ {int netagent_flags; } ;
struct netagent_wrapper {TYPE_1__ netagent; } ;
struct netagent_trigger_args {int agent_uuidlen; scalar_t__ agent_uuid; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOTSUP ; 
 int ERANGE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  NETAGENTLOG (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int NETAGENT_FLAG_ACTIVE ; 
 int NETAGENT_FLAG_USER_ACTIVATED ; 
 int /*<<< orphan*/  NETAGENT_MESSAGE_TYPE_TRIGGER ; 
 int /*<<< orphan*/  NETAGENT_TRIGGER_FLAG_USER ; 
 int copyin (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 struct netagent_wrapper* netagent_find_agent_with_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netagent_lock ; 
 int netagent_send_trigger (struct netagent_wrapper*,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ ) ; 

int
netagent_trigger(struct proc *p, struct netagent_trigger_args *uap, int32_t *retval)
{
#pragma unused(p, retval)
	uuid_t agent_uuid;
	int error = 0;

	if (uap == NULL) {
		NETAGENTLOG0(LOG_ERR, "uap == NULL");
		return (EINVAL);
	}

	if (uap->agent_uuid) {
		if (uap->agent_uuidlen != sizeof(uuid_t)) {
			NETAGENTLOG(LOG_ERR, "Incorrect length (got %llu, expected %lu)",
						uap->agent_uuidlen, sizeof(uuid_t));
			return (ERANGE);
		}

		error = copyin(uap->agent_uuid, agent_uuid, sizeof(uuid_t));
		if (error) {
			NETAGENTLOG(LOG_ERR, "copyin error (%d)", error);
			return (error);
		}
	}

	if (uuid_is_null(agent_uuid)) {
		NETAGENTLOG0(LOG_ERR, "Requested netagent UUID is empty");
		return (EINVAL);
	}

	lck_rw_lock_shared(&netagent_lock);
	struct netagent_wrapper *wrapper = netagent_find_agent_with_uuid(agent_uuid);
	if (wrapper == NULL) {
		NETAGENTLOG0(LOG_ERR, "Requested netagent UUID is not registered");
		error = ENOENT;
		goto done;
	}

	if ((wrapper->netagent.netagent_flags & NETAGENT_FLAG_USER_ACTIVATED) == 0) {
		// Agent does not accept triggers
		NETAGENTLOG0(LOG_ERR, "Requested netagent UUID is not eligible for triggering");
		error = ENOTSUP;
		goto done;
	}

	if ((wrapper->netagent.netagent_flags & NETAGENT_FLAG_ACTIVE)) {
		// Agent already active
		NETAGENTLOG0(LOG_INFO, "Requested netagent UUID is already active");
		error = 0;
		goto done;
	}

	error = netagent_send_trigger(wrapper, p, NETAGENT_TRIGGER_FLAG_USER, NETAGENT_MESSAGE_TYPE_TRIGGER);
	NETAGENTLOG((error ? LOG_ERR : LOG_INFO), "Triggered netagent (error %d)", error);
done:
	lck_rw_done(&netagent_lock);
	return (error);
}