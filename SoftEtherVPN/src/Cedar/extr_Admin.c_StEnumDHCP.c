#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  hubname ;
typedef  scalar_t__ UINT ;
struct TYPE_26__ {TYPE_2__* Server; } ;
struct TYPE_25__ {int Me; } ;
struct TYPE_24__ {scalar_t__ Type; int /*<<< orphan*/  lock_online; TYPE_1__* SecureNAT; } ;
struct TYPE_23__ {int NumItem; int /*<<< orphan*/  HubName; } ;
struct TYPE_22__ {int /*<<< orphan*/  FarmMemberList; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_21__ {int /*<<< orphan*/  Nat; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_ENUM_DHCP ;
typedef  TYPE_4__ HUB ;
typedef  TYPE_5__ FARM_MEMBER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_6__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_RIGHT ; 
 int /*<<< orphan*/  Copy (TYPE_3__*,TYPE_3__*,int) ; 
 scalar_t__ ERR_HUB_NOT_FOUND ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_SNAT_NOT_RUNNING ; 
 int /*<<< orphan*/  FreeRpcEnumDhcp (TYPE_3__*) ; 
 TYPE_4__* GetHub (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int GetServerCapsBool (TYPE_2__*,char*) ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 TYPE_5__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/  NtEnumDhcpList (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_4__*) ; 
 int /*<<< orphan*/  SiCallEnumDhcp (TYPE_2__*,TYPE_5__*,char*,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 

UINT StEnumDHCP(ADMIN *a, RPC_ENUM_DHCP *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	HUB *h;
	UINT ret = ERR_NO_ERROR;
	char hubname[MAX_HUBNAME_LEN + 1];
	UINT i;
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

	Lock(h->lock_online);
	{
		if (h->SecureNAT == NULL)
		{
			ret = ERR_SNAT_NOT_RUNNING;
		}
		else
		{
			NtEnumDhcpList(h->SecureNAT->Nat, t);
		}
	}
	Unlock(h->lock_online);

	if (h->Type == HUB_TYPE_FARM_DYNAMIC)
	{
		if (ret == ERR_SNAT_NOT_RUNNING)
		{
			// Get status of remote DHCP service
			LockList(s->FarmMemberList);
			{
				for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
				{
					FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);
					if (f->Me == false)
					{
						RPC_ENUM_DHCP tmp;

						Zero(&tmp, sizeof(tmp));

						SiCallEnumDhcp(s, f, hubname, &tmp);

						if (tmp.NumItem >= 1)
						{
							FreeRpcEnumDhcp(t);
							Copy(t, &tmp, sizeof(RPC_ENUM_DHCP));
							ret = ERR_NO_ERROR;
							break;
						}
						else
						{
							FreeRpcEnumDhcp(&tmp);
						}
					}
				}
			}
			UnlockList(s->FarmMemberList);
		}
	}

	ReleaseHub(h);

	ret = ERR_NO_ERROR;

	return ret;
}