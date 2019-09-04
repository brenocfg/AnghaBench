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
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  INFINITE ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  LOG_SWITCH_DAY ; 
 int /*<<< orphan*/  LOG_SWITCH_HOUR ; 
 int /*<<< orphan*/  LOG_SWITCH_MINUTE ; 
 int /*<<< orphan*/  LOG_SWITCH_MONTH ; 
 int /*<<< orphan*/  LOG_SWITCH_NO ; 
 int /*<<< orphan*/  LOG_SWITCH_SECOND ; 
 scalar_t__ StartWith (char*,char*) ; 

UINT StrToLogSwitchType(char *str)
{
	UINT ret = INFINITE;
	// Validate arguments
	if (str == NULL)
	{
		return INFINITE;
	}

	if (IsEmptyStr(str) || StartWith("none", str))
	{
		ret = LOG_SWITCH_NO;
	}
	else if (StartWith("second", str))
	{
		ret = LOG_SWITCH_SECOND;
	}
	else if (StartWith("minute", str))
	{
		ret = LOG_SWITCH_MINUTE;
	}
	else if (StartWith("hour", str))
	{
		ret = LOG_SWITCH_HOUR;
	}
	else if (StartWith("day", str))
	{
		ret = LOG_SWITCH_DAY;
	}
	else if (StartWith("month", str))
	{
		ret = LOG_SWITCH_MONTH;
	}

	return ret;
}