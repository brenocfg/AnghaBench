#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  SaveType; } ;
typedef  TYPE_1__ SYSLOG_SETTING ;
typedef  int /*<<< orphan*/  SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  SYSLOG_NONE ; 
 int /*<<< orphan*/  SiGetSysLogSetting (int /*<<< orphan*/ *,TYPE_1__*) ; 

UINT SiGetSysLogSaveStatus(SERVER *s)
{
	SYSLOG_SETTING set;
	// Validate arguments
	if (s == NULL)
	{
		return SYSLOG_NONE;
	}

	SiGetSysLogSetting(s, &set);

	return set.SaveType;
}