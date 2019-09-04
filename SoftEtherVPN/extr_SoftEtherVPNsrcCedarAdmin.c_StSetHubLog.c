#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_18__ {int ServerAdmin; TYPE_1__* Server; } ;
struct TYPE_17__ {int /*<<< orphan*/  CurrentVersion; } ;
struct TYPE_16__ {int /*<<< orphan*/  LogSetting; int /*<<< orphan*/  HubName; } ;
struct TYPE_15__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_HUB_LOG ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 int /*<<< orphan*/  SetHubLogSettingEx (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SiHubUpdateProc (TYPE_3__*) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 

UINT StSetHubLog(ADMIN *a, RPC_HUB_LOG *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;

	CHECK_RIGHT;


	LockHubList(c);
	{
		h = GetHub(c, t->HubName);
	}
	UnlockHubList(c);

	if (h == NULL)
	{
		return ERR_HUB_NOT_FOUND;
	}

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_change_log_config") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	ALog(a, h, "LA_SET_HUB_LOG");

	SetHubLogSettingEx(h, &t->LogSetting,
		(a->ServerAdmin == false && GetHubAdminOption(h, "no_change_log_switch_type") != 0));

	h->CurrentVersion++;
	SiHubUpdateProc(h);

	ReleaseHub(h);

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}