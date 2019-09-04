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
struct TYPE_2__ {int netagent_flags; } ;
struct netagent_wrapper {TYPE_1__ netagent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  NETAGENTLOG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int NETAGENT_FLAG_ACTIVE ; 
 int NETAGENT_FLAG_KERNEL_ACTIVATED ; 
 int /*<<< orphan*/  NETAGENT_MESSAGE_TYPE_TRIGGER ; 
 int /*<<< orphan*/  NETAGENT_TRIGGER_FLAG_KERNEL ; 
 int /*<<< orphan*/  current_proc () ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 struct netagent_wrapper* netagent_find_agent_with_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netagent_lock ; 
 int netagent_send_trigger (struct netagent_wrapper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
netagent_kernel_trigger(uuid_t uuid)
{
	int error = 0;

	lck_rw_lock_shared(&netagent_lock);
	struct netagent_wrapper *wrapper = netagent_find_agent_with_uuid(uuid);
	if (wrapper == NULL) {
		NETAGENTLOG0(LOG_ERR, "Requested netagent for kernel trigger could not be found");
		error = ENOENT;
		goto done;
	}

	if ((wrapper->netagent.netagent_flags & NETAGENT_FLAG_KERNEL_ACTIVATED) == 0) {
		NETAGENTLOG0(LOG_ERR, "Requested netagent for kernel trigger is not kernel activated");
		// Agent does not accept kernel triggers
		error = EINVAL;
		goto done;
	}

	if ((wrapper->netagent.netagent_flags & NETAGENT_FLAG_ACTIVE)) {
		// Agent already active
		NETAGENTLOG0(LOG_INFO, "Requested netagent for kernel trigger is already active");
		error = 0;
		goto done;
	}

	error = netagent_send_trigger(wrapper, current_proc(), NETAGENT_TRIGGER_FLAG_KERNEL, NETAGENT_MESSAGE_TYPE_TRIGGER);
	NETAGENTLOG((error ? LOG_ERR : LOG_INFO), "Triggered netagent from kernel (error %d)", error);
done:
	lck_rw_done(&netagent_lock);
	return (error);
}