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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int DUMMY_REAL_TIME_EXECUTOR_ENUM_VALUE ; 
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int MULTI_EXECUTOR_ADAPTIVE ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static bool
WarnIfDeprecatedExecutorUsed(int *newval, void **extra, GucSource source)
{
	if (*newval == DUMMY_REAL_TIME_EXECUTOR_ENUM_VALUE)
	{
		ereport(WARNING, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						  errmsg("Ignoring the setting, real-time executor is "
								 "deprecated")));

		/* adaptive executor is superset of real-time, so switch to that */
		*newval = MULTI_EXECUTOR_ADAPTIVE;
	}

	return true;
}