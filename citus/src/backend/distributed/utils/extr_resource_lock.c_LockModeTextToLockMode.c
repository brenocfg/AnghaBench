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
struct LockModeToStringType {int lockMode; int /*<<< orphan*/  name; } ;
typedef  int LOCKMODE ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_LOCK_NOT_AVAILABLE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int lock_mode_to_string_map_count ; 
 struct LockModeToStringType* lockmode_to_string_map ; 
 scalar_t__ pg_strncasecmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

LOCKMODE
LockModeTextToLockMode(const char *lockModeName)
{
	LOCKMODE lockMode = -1;

	int lockIndex = 0;
	for (lockIndex = 0; lockIndex < lock_mode_to_string_map_count; lockIndex++)
	{
		const struct LockModeToStringType *lockMap = lockmode_to_string_map + lockIndex;
		if (pg_strncasecmp(lockMap->name, lockModeName, NAMEDATALEN) == 0)
		{
			lockMode = lockMap->lockMode;
			break;
		}
	}

	/* we could not find the lock mode we are looking for */
	if (lockMode == -1)
	{
		ereport(ERROR,
				(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
				 errmsg("unknown lock mode: %s", lockModeName)));
	}

	return lockMode;
}