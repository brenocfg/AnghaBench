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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int ServerAdmin; int /*<<< orphan*/ * Server; } ;
struct TYPE_6__ {scalar_t__ SaveType; scalar_t__ Port; int /*<<< orphan*/  Hostname; } ;
typedef  TYPE_1__ SYSLOG_SETTING ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 scalar_t__ SYSLOG_NONE ; 
 int /*<<< orphan*/  SiGetSysLogSetting (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 

UINT StGetSysLog(ADMIN *a, SYSLOG_SETTING *t)
{
	SERVER *s = a->Server;

	SiGetSysLogSetting(s, t);

	if (a->ServerAdmin == false)
	{
		// Hide server name for non-administrator
		if (t->SaveType == SYSLOG_NONE)
		{
			StrCpy(t->Hostname, sizeof(t->Hostname), "");
			t->Port = 0;
		}
		else
		{
			StrCpy(t->Hostname, sizeof(t->Hostname), "Secret");
			t->Port = 0;
		}
	}

	return ERR_NO_ERROR;
}