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
struct TYPE_2__ {int /*<<< orphan*/  netagent_type; int /*<<< orphan*/  netagent_domain; } ;
struct netagent_wrapper {TYPE_1__ netagent; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NETAGENTLOG (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  NETAGENTLOG0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NETAGENT_DOMAINSIZE ; 
 int /*<<< orphan*/  NETAGENT_TYPESIZE ; 
 int TRUE ; 
 int /*<<< orphan*/  lck_rw_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_lock_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netagent_wrapper* netagent_find_agent_with_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netagent_lock ; 

bool
netagent_get_agent_domain_and_type(uuid_t uuid, char *domain, char *type)
{
	bool found = FALSE;
	if (domain == NULL || type == NULL) {
		NETAGENTLOG(LOG_ERR, "Invalid arguments for netagent_get_agent_domain_and_type %p %p", domain, type);
		return (FALSE);
	}

	lck_rw_lock_shared(&netagent_lock);
	struct netagent_wrapper *wrapper = netagent_find_agent_with_uuid(uuid);
	if (wrapper != NULL) {
		found = TRUE;
		memcpy(domain, wrapper->netagent.netagent_domain, NETAGENT_DOMAINSIZE);
		memcpy(type, wrapper->netagent.netagent_type, NETAGENT_TYPESIZE);
	} else {
		NETAGENTLOG0(LOG_ERR, "Type requested for invalid netagent");
	}
	lck_rw_done(&netagent_lock);

	return (found);
}