#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  push_routes_str_old ;
struct TYPE_28__ {int ApplyDhcpPushRoutes; scalar_t__ UseDhcp; scalar_t__ UseNat; int /*<<< orphan*/  HubName; int /*<<< orphan*/  DhcpPushRoutes; int /*<<< orphan*/  Mask; int /*<<< orphan*/  Ip; int /*<<< orphan*/  MacAddress; } ;
typedef  TYPE_5__ VH_OPTION ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_31__ {int ServerAdmin; TYPE_6__* Server; } ;
struct TYPE_30__ {scalar_t__ Type; int /*<<< orphan*/  CurrentVersion; int /*<<< orphan*/  lock_online; TYPE_4__* SecureNAT; TYPE_14__* SecureNATOption; TYPE_2__* Cedar; } ;
struct TYPE_29__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_27__ {TYPE_3__* Nat; } ;
struct TYPE_26__ {int /*<<< orphan*/  Virtual; } ;
struct TYPE_25__ {TYPE_1__* Server; } ;
struct TYPE_24__ {scalar_t__ ServerType; } ;
struct TYPE_23__ {int UseNat; int UseDhcp; char* DhcpPushRoutes; } ;
typedef  TYPE_6__ SERVER ;
typedef  TYPE_7__ HUB ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_8__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_8__*,TYPE_7__*,char*) ; 
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  Copy (TYPE_14__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ERR_HUB_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NOT_ENOUGH_RIGHT ; 
 int /*<<< orphan*/  ERR_NOT_FARM_CONTROLLER ; 
 int /*<<< orphan*/  ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 TYPE_7__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetHubAdminOption (TYPE_7__*,char*) ; 
 int GetServerCapsBool (TYPE_6__*,char*) ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 scalar_t__ HUB_TYPE_STANDALONE ; 
 int IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_6__*) ; 
 int IsHostIPAddress4 (int /*<<< orphan*/ *) ; 
 int IsSubnetMask4 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsZero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int MAX_DHCP_CLASSLESS_ROUTE_TABLE_STR_SIZE ; 
 int /*<<< orphan*/  NiClearUnsupportedVhOptionForDynamicHub (TYPE_14__*,int) ; 
 int NormalizeClasslessRouteTableStr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_7__*) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SetVirtualHostOption (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  SiHubUpdateProc (TYPE_7__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 

UINT StSetSecureNATOption(ADMIN *a, VH_OPTION *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	char push_routes_str_old[MAX_DHCP_CLASSLESS_ROUTE_TABLE_STR_SIZE];


	if (IsZero(t->MacAddress, sizeof(t->MacAddress)) ||
		IsHostIPAddress4(&t->Ip) == false ||
		IsSubnetMask4(&t->Mask) == false)
	{
		return ERR_INVALID_PARAMETER;
	}
	if ((IPToUINT(&t->Ip) & (~(IPToUINT(&t->Mask)))) == 0)
	{
		return ERR_INVALID_PARAMETER;
	}
	if (GetServerCapsBool(s, "b_support_securenat") == false)
	{
		t->ApplyDhcpPushRoutes = false;
	}
	if (t->ApplyDhcpPushRoutes)
	{
		if (NormalizeClasslessRouteTableStr(t->DhcpPushRoutes, sizeof(t->DhcpPushRoutes), t->DhcpPushRoutes) == false)
		{
			return ERR_INVALID_PARAMETER;
		}
	}

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

	if (a->ServerAdmin == false && GetHubAdminOption(h, "no_securenat") != 0)
	{
		ReleaseHub(h);
		return ERR_NOT_ENOUGH_RIGHT;
	}

	if (h->SecureNATOption->UseNat == false && t->UseNat)
	{
		if (a->ServerAdmin == false && GetHubAdminOption(h, "no_securenat_enablenat") != 0)
		{
			ReleaseHub(h);
			return ERR_NOT_ENOUGH_RIGHT;
		}
	}

	if (h->SecureNATOption->UseDhcp == false && t->UseDhcp)
	{
		if (a->ServerAdmin == false && GetHubAdminOption(h, "no_securenat_enabledhcp") != 0)
		{
			ReleaseHub(h);
			return ERR_NOT_ENOUGH_RIGHT;
		}
	}

	StrCpy(push_routes_str_old, sizeof(push_routes_str_old), h->SecureNATOption->DhcpPushRoutes);
	Copy(h->SecureNATOption, t, sizeof(VH_OPTION));
	if (t->ApplyDhcpPushRoutes == false)
	{
		StrCpy(h->SecureNATOption->DhcpPushRoutes, sizeof(h->SecureNATOption->DhcpPushRoutes), push_routes_str_old);
	}

	if (h->Type != HUB_TYPE_STANDALONE && h->Cedar != NULL && h->Cedar->Server != NULL &&
		h->Cedar->Server->ServerType == SERVER_TYPE_FARM_CONTROLLER)
	{
		NiClearUnsupportedVhOptionForDynamicHub(h->SecureNATOption, false);
	}

	Lock(h->lock_online);
	{
		if (h->SecureNAT != NULL)
		{
			SetVirtualHostOption(h->SecureNAT->Nat->Virtual, t);
		}
	}
	Unlock(h->lock_online);

	ALog(a, h, "LA_SET_SNAT_OPTION");

	h->CurrentVersion++;
	SiHubUpdateProc(h);

	IncrementServerConfigRevision(s);

	ReleaseHub(h);

	return ERR_NO_ERROR;
}