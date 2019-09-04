#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_12__ {char* HubName; int ApplyDhcpPushRoutes; } ;
typedef  TYPE_1__ VH_OPTION ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {TYPE_2__* Server; } ;
struct TYPE_14__ {scalar_t__ Type; char* Name; int /*<<< orphan*/  SecureNATOption; } ;
struct TYPE_13__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  Copy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NOT_FARM_CONTROLLER ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ *,char*) ; 
 int GetServerCapsBool (TYPE_2__*,char*) ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

UINT StGetSecureNATOption(ADMIN *a, VH_OPTION *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	char hubname[MAX_HUBNAME_LEN + 1];

	StrCpy(hubname, sizeof(hubname), t->HubName);

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

	if (h->Type == HUB_TYPE_FARM_STATIC || GetServerCapsBool(s, "b_support_securenat") == false)
	{
		ReleaseHub(h);
		return ERR_NOT_SUPPORTED;
	}
	if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
	{
		ReleaseHub(h);
		return ERR_NOT_FARM_CONTROLLER;
	}

	Zero(t, sizeof(VH_OPTION));
	Copy(t, h->SecureNATOption, sizeof(VH_OPTION));
	StrCpy(t->HubName, sizeof(t->HubName), h->Name);
	t->ApplyDhcpPushRoutes = true;

	ReleaseHub(h);

	return ERR_NO_ERROR;
}