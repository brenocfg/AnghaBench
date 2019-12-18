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
struct TYPE_3__ {int /*<<< orphan*/ * Server; } ;
typedef  int /*<<< orphan*/  SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ FARM_CONTROLLER ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,char*) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  SiCalledCreateHub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledCreateTicket (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiCalledDeleteHub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiCalledDeleteIpTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiCalledDeleteMacTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiCalledDeleteSession (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledEnumDhcp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiCalledEnumHub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledEnumIpTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledEnumLogFileList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledEnumMacTable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledEnumNat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledEnumSession (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledGetNatStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledGetSessionStatus (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SiCalledReadLogFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiCalledUpdateHub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ StrCmpi (char*,char*) ; 

PACK *SiCalledTask(FARM_CONTROLLER *f, PACK *p, char *taskname)
{
	PACK *ret;
	SERVER *s;
	// Validate arguments
	if (f == NULL || p == NULL || taskname == NULL)
	{
		return NULL;
	}

	ret = NULL;
	s = f->Server;

	if (StrCmpi(taskname, "noop") == 0)
	{
		// NO OPERATION
		ret = NewPack();
	}
	else
	{
		Debug("Task Called: [%s].\n", taskname);
		if (StrCmpi(taskname, "createhub") == 0)
		{
			SiCalledCreateHub(s, p);
			ret = NewPack();
		}
		else if (StrCmpi(taskname, "deletehub") == 0)
		{
			SiCalledDeleteHub(s, p);
			ret = NewPack();
		}
		else if (StrCmpi(taskname, "enumhub") == 0)
		{
			ret = NewPack();
			SiCalledEnumHub(s, ret, p);
		}
		else if (StrCmpi(taskname, "updatehub") == 0)
		{
			SiCalledUpdateHub(s, p);
			ret = NewPack();
		}
		else if (StrCmpi(taskname, "createticket") == 0)
		{
			ret = SiCalledCreateTicket(s, p);
		}
		else if (StrCmpi(taskname, "enumnat") == 0)
		{
			ret = SiCalledEnumNat(s, p);
		}
		else if (StrCmpi(taskname, "enumdhcp") == 0)
		{
			ret = SiCalledEnumDhcp(s, p);
		}
		else if (StrCmpi(taskname, "getnatstatus") == 0)
		{
			ret = SiCalledGetNatStatus(s, p);
		}
		else if (StrCmpi(taskname, "enumsession") == 0)
		{
			ret = SiCalledEnumSession(s, p);
		}
		else if (StrCmpi(taskname, "deletesession") == 0)
		{
			SiCalledDeleteSession(s, p);
			ret = NewPack();
		}
		else if (StrCmpi(taskname, "deletemactable") == 0)
		{
			SiCalledDeleteMacTable(s, p);
			ret = NewPack();
		}
		else if (StrCmpi(taskname, "deleteiptable") == 0)
		{
			SiCalledDeleteIpTable(s, p);
			ret = NewPack();
		}
		else if (StrCmpi(taskname, "enummactable") == 0)
		{
			ret = SiCalledEnumMacTable(s, p);
		}
		else if (StrCmpi(taskname, "enumiptable") == 0)
		{
			ret = SiCalledEnumIpTable(s, p);
		}
		else if (StrCmpi(taskname, "getsessionstatus") == 0)
		{
			ret = SiCalledGetSessionStatus(s, p);
		}
		else if (StrCmpi(taskname, "enumlogfilelist") == 0)
		{
			ret = SiCalledEnumLogFileList(s, p);
		}
		else if (StrCmpi(taskname, "readlogfile") == 0)
		{
			ret = SiCalledReadLogFile(s, p);
		}
	}

	return ret;
}