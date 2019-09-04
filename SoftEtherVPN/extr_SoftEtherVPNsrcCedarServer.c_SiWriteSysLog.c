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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  machinename ;
typedef  int /*<<< orphan*/  datetime ;
struct TYPE_3__ {int /*<<< orphan*/  Syslog; scalar_t__ StrictSyslogDatetimeFormat; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GSF_DISABLE_SYSLOG ; 
 int /*<<< orphan*/  GetCurrentTimezone () ; 
 int /*<<< orphan*/  GetDateTimeStrMilli (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDateTimeStrRFC3339 (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  LocalTime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HOST_NAME_LEN ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SendSysLog (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,char*,char*,char*,char*,...) ; 

void SiWriteSysLog(SERVER *s, char *typestr, char *hubname, wchar_t *message)
{
	wchar_t tmp[1024];
	char machinename[MAX_HOST_NAME_LEN + 1];
	char datetime[MAX_PATH];
	SYSTEMTIME st;
	// Validate arguments
	if (s == NULL || typestr == NULL || message == NULL)
	{
		return;
	}

	if (GetGlobalServerFlag(GSF_DISABLE_SYSLOG) != 0)
	{
		return;
	}

	// Host name
	GetMachineName(machinename, sizeof(machinename));

	// Date and time
	LocalTime(&st);
	if(s->StrictSyslogDatetimeFormat){
		GetDateTimeStrRFC3339(datetime, sizeof(datetime), &st, GetCurrentTimezone());
	}else{
		GetDateTimeStrMilli(datetime, sizeof(datetime), &st);
	}

	if (IsEmptyStr(hubname) == false)
	{
		UniFormat(tmp, sizeof(tmp), L"[%S/VPN/%S] (%S) <%S>: %s",
			machinename, hubname, datetime, typestr, message);
	}
	else
	{
		UniFormat(tmp, sizeof(tmp), L"[%S/VPN] (%S) <%S>: %s",
			machinename, datetime, typestr, message);
	}

	Debug("Syslog send: %S\n",tmp);

	SendSysLog(s->Syslog, tmp);
}