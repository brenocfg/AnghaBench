#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  set ;
struct TYPE_8__ {scalar_t__ Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  SaveType; } ;
struct TYPE_9__ {int /*<<< orphan*/  SyslogLock; int /*<<< orphan*/  Syslog; TYPE_1__ SyslogSetting; } ;
typedef  TYPE_1__ SYSLOG_SETTING ;
typedef  TYPE_2__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_1__*,TYPE_1__*,int) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSLOG_NONE ; 
 int /*<<< orphan*/  SetSysLog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void SiSetSysLogSetting(SERVER *s, SYSLOG_SETTING *setting)
{
	SYSLOG_SETTING set;
	// Validate arguments
	if (s == NULL || setting == NULL)
	{
		return;
	}

	Zero(&set, sizeof(set));
	Copy(&set, setting, sizeof(SYSLOG_SETTING));

	if (IsEmptyStr(set.Hostname) || set.Port == 0)
	{
		set.SaveType = SYSLOG_NONE;
	}

	Lock(s->SyslogLock);
	{
		Copy(&s->SyslogSetting, &set, sizeof(SYSLOG_SETTING));

		SetSysLog(s->Syslog, set.Hostname, set.Port);
	}
	Unlock(s->SyslogLock);
}