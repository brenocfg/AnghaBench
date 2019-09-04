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
struct proc_uuid_policy_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUMP_PROC_UUID_POLICY_GENERATION_COUNT () ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  FREE (struct proc_uuid_policy_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_PROC_UUID_POLICY ; 
 int /*<<< orphan*/  PROC_UUID_POLICY_SUBSYS_LOCK () ; 
 int /*<<< orphan*/  PROC_UUID_POLICY_SUBSYS_UNLOCK () ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ) ; 
 struct proc_uuid_policy_entry* proc_uuid_policy_remove_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuidstr ; 

__attribute__((used)) static int
proc_uuid_policy_remove(uuid_t uuid, uint32_t flags)
{
	struct proc_uuid_policy_entry *delentry = NULL;
	int error;
	int should_delete = 0;

#if PROC_UUID_POLICY_DEBUG
	uuid_string_t uuidstr;
	uuid_unparse(uuid, uuidstr);
#endif

	if (uuid_is_null(uuid))
		return EINVAL;

	PROC_UUID_POLICY_SUBSYS_LOCK();

	delentry = proc_uuid_policy_remove_locked(uuid, flags, &should_delete);

	if (delentry) {
		error = 0;
		BUMP_PROC_UUID_POLICY_GENERATION_COUNT();
	} else {
		error = ENOENT;
	}

	PROC_UUID_POLICY_SUBSYS_UNLOCK();

	/* If we had found a pre-existing entry, deallocate its memory now */
	if (delentry && should_delete) {
		FREE(delentry, M_PROC_UUID_POLICY);
	}

	if (error) {
		dprintf("Failed to remove proc uuid policy (%s), entry not present\n", uuidstr);
	} else {
		dprintf("Removed proc uuid policy (%s)\n", uuidstr);
	}

	return error;
}