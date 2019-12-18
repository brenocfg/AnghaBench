#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/ * Server; } ;
struct TYPE_7__ {scalar_t__ SaveType; } ;
typedef  TYPE_1__ SYSLOG_SETTING ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED_FUNCTION_ON_OPENSOURCE ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  GSF_DISABLE_SYSLOG ; 
 scalar_t__ GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int GetServerCapsBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 scalar_t__ SYSLOG_NONE ; 
 int /*<<< orphan*/  SiSetSysLogSetting (int /*<<< orphan*/ *,TYPE_1__*) ; 

UINT StSetSysLog(ADMIN *a, SYSLOG_SETTING *t)
{
	SERVER *s = a->Server;

	SERVER_ADMIN_ONLY;

	if (GetGlobalServerFlag(GSF_DISABLE_SYSLOG) != 0 && t->SaveType != SYSLOG_NONE)
	{
		return ERR_NOT_SUPPORTED_FUNCTION_ON_OPENSOURCE;
	}

	if (GetServerCapsBool(s, "b_support_syslog") == false)
	{
		return ERR_NOT_SUPPORTED;
	}

	SiSetSysLogSetting(s, t);

	IncrementServerConfigRevision(s);
	ALog(a, NULL, "LA_SET_SYSLOG");

	return ERR_NO_ERROR;
}