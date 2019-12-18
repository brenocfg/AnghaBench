#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/ * Server; } ;
struct TYPE_5__ {int SaveSecurityLog; } ;
struct TYPE_6__ {int /*<<< orphan*/  SecurityLogger; int /*<<< orphan*/  Name; TYPE_1__ LogSetting; TYPE_3__* Cedar; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_2__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  InsertUnicodeRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 scalar_t__ SYSLOG_NONE ; 
 scalar_t__ SYSLOG_SERVER_AND_HUB_ALL_LOG ; 
 scalar_t__ SYSLOG_SERVER_AND_HUB_SECURITY_LOG ; 
 scalar_t__ SiGetSysLogSaveStatus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiWriteSysLog (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteServerLog (TYPE_3__*,int /*<<< orphan*/ *) ; 

void WriteHubLog(HUB *h, wchar_t *str)
{
	wchar_t buf[MAX_SIZE * 2];
	UINT syslog_status;
	SERVER *s;
	// Validate arguments
	if (h == NULL || str == NULL)
	{
		return;
	}

	s = h->Cedar->Server;
	syslog_status = SiGetSysLogSaveStatus(s);

	UniFormat(buf, sizeof(buf), L"[HUB \"%S\"] %s", h->Name, str);

	if (syslog_status == SYSLOG_NONE)
	{
		WriteServerLog(h->Cedar, buf);
	}

	if (h->LogSetting.SaveSecurityLog == false)
	{
		return;
	}

	if (syslog_status == SYSLOG_SERVER_AND_HUB_SECURITY_LOG
		|| syslog_status == SYSLOG_SERVER_AND_HUB_ALL_LOG)
	{
		SiWriteSysLog(s, "SECURITY_LOG", h->Name, str);
	}
	else
	{
		InsertUnicodeRecord(h->SecurityLogger, str);
	}
}