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
typedef  int u_int32_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  NECPLOG0 (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  necp_account_id_list ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 int /*<<< orphan*/ * necp_lookup_string_with_id_locked (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u_int32_t
necp_get_new_string_id(void)
{
	static u_int32_t necp_last_string_id = 0;

	u_int32_t newid = 0;

	LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

	bool wrapped = FALSE;
	do {
		necp_last_string_id++;
		if (necp_last_string_id < 1) {
			if (wrapped) {
				// Already wrapped, give up
				NECPLOG0(LOG_ERR, "Failed to find a free app UUID.\n");
				return (0);
			}
			necp_last_string_id = 1;
			wrapped = TRUE;
		}
		newid = necp_last_string_id;
	} while (necp_lookup_string_with_id_locked(&necp_account_id_list, newid) != NULL); // If already used, keep trying

	if (newid == 0) {
		NECPLOG0(LOG_ERR, "Allocate string id failed.\n");
		return (0);
	}

	return (newid);
}