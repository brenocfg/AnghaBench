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

/* Variables and functions */
 int /*<<< orphan*/  ApplyLogRedaction (char const*) ; 
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  LogDistributedDeadlockDetection ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamptz_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
LogDistributedDeadlockDebugMessage(const char *errorMessage)
{
	if (!LogDistributedDeadlockDetection)
	{
		return;
	}

	ereport(LOG, (errmsg("[%s] %s", timestamptz_to_str(GetCurrentTimestamp()),
						 ApplyLogRedaction(errorMessage))));
}