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
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  netagent_flags; } ;
struct netagent_wrapper {TYPE_1__ netagent; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 struct netagent_wrapper* netagent_find_agent_with_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netagent_lock ; 

u_int32_t
netagent_get_flags(uuid_t uuid)
{
	u_int32_t flags = 0;
	lck_rw_lock_shared(&netagent_lock);
	struct netagent_wrapper *wrapper = netagent_find_agent_with_uuid(uuid);
	if (wrapper != NULL) {
		flags = wrapper->netagent.netagent_flags;
	} else {
		NETAGENTLOG0(LOG_DEBUG, "Flags requested for invalid netagent");
	}
	lck_rw_done(&netagent_lock);

	return (flags);
}