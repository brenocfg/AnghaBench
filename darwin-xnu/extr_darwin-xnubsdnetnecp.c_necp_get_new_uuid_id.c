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
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NECP_FIRST_VALID_APP_ID ; 
 scalar_t__ NECP_FIRST_VALID_SERVICE_ID ; 
 scalar_t__ NECP_NULL_SERVICE_ID ; 
 int TRUE ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 int /*<<< orphan*/ * necp_uuid_lookup_uuid_with_app_id_locked (scalar_t__) ; 
 int /*<<< orphan*/ * necp_uuid_lookup_uuid_with_service_id_locked (scalar_t__) ; 

__attribute__((used)) static u_int32_t
necp_get_new_uuid_id(bool service)
{
	static u_int32_t necp_last_service_uuid_id = 0;
	static u_int32_t necp_last_app_uuid_id = 0;

	u_int32_t newid = 0;

	LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

	if (service) {
		bool wrapped = FALSE;
		do {
			necp_last_service_uuid_id++;
			if (necp_last_service_uuid_id < NECP_FIRST_VALID_SERVICE_ID ||
				necp_last_service_uuid_id >= NECP_FIRST_VALID_APP_ID) {
				if (wrapped) {
					// Already wrapped, give up
					NECPLOG0(LOG_ERR, "Failed to find a free service UUID.\n");
					return (NECP_NULL_SERVICE_ID);
				}
				necp_last_service_uuid_id = NECP_FIRST_VALID_SERVICE_ID;
				wrapped = TRUE;
			}
			newid = necp_last_service_uuid_id;
		} while (necp_uuid_lookup_uuid_with_service_id_locked(newid) != NULL); // If already used, keep trying
	} else {
		bool wrapped = FALSE;
		do {
			necp_last_app_uuid_id++;
			if (necp_last_app_uuid_id < NECP_FIRST_VALID_APP_ID) {
				if (wrapped) {
					// Already wrapped, give up
					NECPLOG0(LOG_ERR, "Failed to find a free app UUID.\n");
					return (NECP_NULL_SERVICE_ID);
				}
				necp_last_app_uuid_id = NECP_FIRST_VALID_APP_ID;
				wrapped = TRUE;
			}
			newid = necp_last_app_uuid_id;
		} while (necp_uuid_lookup_uuid_with_app_id_locked(newid) != NULL); // If already used, keep trying
	}

	if (newid == NECP_NULL_SERVICE_ID) {
		NECPLOG0(LOG_ERR, "Allocate uuid ID failed.\n");
		return (NECP_NULL_SERVICE_ID);
	}

	return (newid);
}