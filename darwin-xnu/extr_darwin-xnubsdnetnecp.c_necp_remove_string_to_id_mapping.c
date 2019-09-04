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
struct necp_string_id_mapping_list {int dummy; } ;
struct necp_string_id_mapping {scalar_t__ refcount; struct necp_string_id_mapping* string; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  FREE (struct necp_string_id_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_ASSERT_EXCLUSIVE ; 
 int /*<<< orphan*/  LIST_REMOVE (struct necp_string_id_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NECP ; 
 int TRUE ; 
 int /*<<< orphan*/  chain ; 
 int /*<<< orphan*/  necp_kernel_policy_lock ; 
 struct necp_string_id_mapping* necp_lookup_string_to_id_locked (struct necp_string_id_mapping_list*,char*) ; 

__attribute__((used)) static bool
necp_remove_string_to_id_mapping(struct necp_string_id_mapping_list *list, char *string)
{
	struct necp_string_id_mapping *existing_mapping = NULL;

	LCK_RW_ASSERT(&necp_kernel_policy_lock, LCK_RW_ASSERT_EXCLUSIVE);

	existing_mapping = necp_lookup_string_to_id_locked(list, string);
	if (existing_mapping != NULL) {
		if (--existing_mapping->refcount == 0) {
			LIST_REMOVE(existing_mapping, chain);
			FREE(existing_mapping->string, M_NECP);
			FREE(existing_mapping, M_NECP);
		}
		return (TRUE);
	}

	return (FALSE);
}