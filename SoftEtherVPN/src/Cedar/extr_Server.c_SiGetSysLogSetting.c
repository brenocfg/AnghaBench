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
struct TYPE_3__ {int /*<<< orphan*/  SyslogSetting; } ;
typedef  int /*<<< orphan*/  SYSLOG_SETTING ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

void SiGetSysLogSetting(SERVER *s, SYSLOG_SETTING *setting)
{
	// Validate arguments
	if (s == NULL || setting == NULL)
	{
		return;
	}

	//Lock(s->SyslogLock);
	{
		Copy(setting, &s->SyslogSetting, sizeof(SYSLOG_SETTING));
	}
	//Unlock(s->SyslogLock);
}