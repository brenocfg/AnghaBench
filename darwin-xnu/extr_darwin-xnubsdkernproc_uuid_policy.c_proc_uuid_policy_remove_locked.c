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
typedef  int /*<<< orphan*/  uint32_t ;
struct proc_uuid_policy_entry {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct proc_uuid_policy_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  proc_uuid_policy_count ; 
 struct proc_uuid_policy_entry* proc_uuid_policy_lookup_locked (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct proc_uuid_policy_entry *
proc_uuid_policy_remove_locked(uuid_t uuid, uint32_t flags, int *should_delete)
{
	struct proc_uuid_policy_entry *foundentry = NULL;
	if (should_delete) {
		*should_delete = 0;
	}
	
	foundentry = proc_uuid_policy_lookup_locked(uuid);
	if (foundentry) {
		if (foundentry->flags == flags) {
			LIST_REMOVE(foundentry, entries);
			proc_uuid_policy_count--;
			if (should_delete) {
				*should_delete = 1;
			}
		} else {
			foundentry->flags &= ~flags;
		}
	}
	
	return foundentry;
}