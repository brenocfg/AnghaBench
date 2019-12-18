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
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static bool
ErrorIfNotASuitableDeadlockFactor(double *newval, void **extra, GucSource source)
{
	if (*newval <= 1.0 && *newval != -1.0)
	{
		ereport(WARNING, (errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						  errmsg(
							  "citus.distributed_deadlock_detection_factor cannot be less than 1. "
							  "To disable distributed deadlock detection set the value to -1.")));

		return false;
	}

	return true;
}