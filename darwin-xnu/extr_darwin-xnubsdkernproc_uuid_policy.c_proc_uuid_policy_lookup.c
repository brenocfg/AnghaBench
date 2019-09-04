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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  PROC_UUID_POLICY_SUBSYS_LOCK () ; 
 int /*<<< orphan*/  PROC_UUID_POLICY_SUBSYS_UNLOCK () ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct proc_uuid_policy_entry* proc_uuid_policy_lookup_locked (int /*<<< orphan*/ ) ; 
 scalar_t__ proc_uuid_policy_table_gencount ; 
 scalar_t__ uuid_is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uuidstr ; 

int
proc_uuid_policy_lookup(uuid_t uuid, uint32_t *flags, int32_t *gencount)
{
	struct proc_uuid_policy_entry *foundentry = NULL;
	int error;

#if PROC_UUID_POLICY_DEBUG
	uuid_string_t uuidstr;
	uuid_unparse(uuid, uuidstr);
#endif

	if (uuid_is_null(uuid) || !flags || !gencount)
		return EINVAL;

	if (*gencount == proc_uuid_policy_table_gencount) {
		/*
		 * Generation count hasn't changed, so old flags should be valid.
		 * We avoid taking the lock here by assuming any concurrent modifications
		 * to the table will invalidate the generation count.
		 */
		return 0;
	}

	PROC_UUID_POLICY_SUBSYS_LOCK();

	foundentry = proc_uuid_policy_lookup_locked(uuid);

	if (foundentry) {
		*flags = foundentry->flags;
		*gencount = proc_uuid_policy_table_gencount;
		error = 0;
	} else {
		error = ENOENT;
	}

	PROC_UUID_POLICY_SUBSYS_UNLOCK();

	if (error == 0) {
		dprintf("Looked up proc uuid policy (%s,0x%08x)\n", uuidstr, *flags);
	}

	return error;
}