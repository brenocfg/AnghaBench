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
struct LockModeToStringType {scalar_t__ lockMode; char* name; } ;
typedef  scalar_t__ LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_LOCK_NOT_AVAILABLE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int) ; 
 int lock_mode_to_string_map_count ; 
 struct LockModeToStringType* lockmode_to_string_map ; 

const char *
LockModeToLockModeText(LOCKMODE lockMode)
{
	const char *lockModeText = NULL;

	int lockIndex = 0;
	for (lockIndex = 0; lockIndex < lock_mode_to_string_map_count; lockIndex++)
	{
		const struct LockModeToStringType *lockMap = lockmode_to_string_map + lockIndex;
		if (lockMode == lockMap->lockMode)
		{
			lockModeText = lockMap->name;
			break;
		}
	}

	/* we could not find the lock mode we are looking for */
	if (lockModeText == NULL)
	{
		ereport(ERROR,
				(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
				 errmsg("unknown lock mode enum: %d", (int) lockMode)));
	}

	return lockModeText;
}