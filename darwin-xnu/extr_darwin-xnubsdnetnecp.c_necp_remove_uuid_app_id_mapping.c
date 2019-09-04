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
struct necp_uuid_id_mapping {scalar_t__ refcount; int /*<<< orphan*/  table_refcount; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FREE (struct necp_uuid_id_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LIST_REMOVE (struct necp_uuid_id_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NECP ; 
 int TRUE ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 struct necp_uuid_id_mapping* necp_uuid_lookup_app_id_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
necp_remove_uuid_app_id_mapping(uuid_t uuid, bool *removed_mapping, bool uuid_policy_table)
{
	struct necp_uuid_id_mapping *existing_mapping = NULL;

	LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

	if (removed_mapping) {
		*removed_mapping = FALSE;
	}

	existing_mapping = necp_uuid_lookup_app_id_locked(uuid);
	if (existing_mapping != NULL) {
		if (uuid_policy_table) {
			existing_mapping->table_refcount--;
		}
		if (--existing_mapping->refcount == 0) {
			LIST_REMOVE(existing_mapping, chain);
			FREE(existing_mapping, M_NECP);
			if (removed_mapping) {
				*removed_mapping = TRUE;
			}
		}
		return (TRUE);
	}

	return (FALSE);
}