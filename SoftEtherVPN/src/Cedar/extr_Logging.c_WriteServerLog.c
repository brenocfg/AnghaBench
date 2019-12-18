#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {TYPE_1__* Server; } ;
struct TYPE_6__ {int /*<<< orphan*/  Logger; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  InsertUnicodeRecord (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsDebug () ; 
 scalar_t__ SYSLOG_NONE ; 
 scalar_t__ SiGetSysLogSaveStatus (TYPE_1__*) ; 
 int /*<<< orphan*/  SiWriteSysLog (TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniPrint (char*,int /*<<< orphan*/ *) ; 

void WriteServerLog(CEDAR *c, wchar_t *str)
{
	SERVER *s;
	// Validate arguments
	if (c == NULL || str == NULL)
	{
		return;
	}

	s = c->Server;
	if (s == NULL)
	{
		return;
	}

	if (IsDebug())
	{
		UniPrint(L"LOG: %s\n", str);
	}

	if (SiGetSysLogSaveStatus(s) != SYSLOG_NONE)
	{
		SiWriteSysLog(s, "SERVER_LOG", NULL, str);
	}
	else
	{
		InsertUnicodeRecord(s->Logger, str);
	}
}