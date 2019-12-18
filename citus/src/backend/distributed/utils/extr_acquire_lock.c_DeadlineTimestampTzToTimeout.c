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
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int /*<<< orphan*/  TimestampDifference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*,int*) ; 

__attribute__((used)) static long
DeadlineTimestampTzToTimeout(TimestampTz deadline)
{
	long secs = 0;
	int msecs = 0;
	TimestampDifference(GetCurrentTimestamp(), deadline, &secs, &msecs);
	return secs * 1000 + msecs / 1000;
}