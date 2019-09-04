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
struct netagent_wrapper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEV_NETAGENT_UPDATED_INTERFACES ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 struct netagent_wrapper* netagent_find_agent_with_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netagent_lock ; 
 int /*<<< orphan*/  netagent_post_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
netagent_post_updated_interfaces(uuid_t uuid)
{
	struct netagent_wrapper *wrapper = NULL;
	lck_rw_lock_shared(&netagent_lock);
	wrapper = netagent_find_agent_with_uuid(uuid);
	lck_rw_done(&netagent_lock);

	if (wrapper != NULL) {
		netagent_post_event(uuid, KEV_NETAGENT_UPDATED_INTERFACES, TRUE);
	} else {
		NETAGENTLOG0(LOG_DEBUG, "Interface event with no associated agent");
	}

	return;
}