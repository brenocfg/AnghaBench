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
typedef  int /*<<< orphan*/  uint64_t ;
struct netagent_wrapper {int /*<<< orphan*/  use_count; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_exclusive (int /*<<< orphan*/ *) ; 
 struct netagent_wrapper* netagent_find_agent_with_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netagent_lock ; 

int
netagent_use(uuid_t agent_uuid, uint64_t *out_use_count)
{
	int error = 0;

	lck_rw_lock_exclusive(&netagent_lock);
	struct netagent_wrapper *wrapper = netagent_find_agent_with_uuid(agent_uuid);
	if (wrapper == NULL) {
		NETAGENTLOG0(LOG_ERR, "netagent_assert: Requested netagent UUID is not registered");
		error = ENOENT;
		goto done;
	}

	uint64_t current_count = wrapper->use_count;
	wrapper->use_count++;

	if (out_use_count != NULL) {
		*out_use_count = current_count;
	}

done:
	lck_rw_done(&netagent_lock);
	return (error);
}