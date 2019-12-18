#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_9__ {int /*<<< orphan*/  lock_online; TYPE_1__* SecureNAT; } ;
struct TYPE_8__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_7__ {int /*<<< orphan*/  Nat; } ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  RPC_ENUM_NAT ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  FreeRpcEnumNat (int /*<<< orphan*/ *) ; 
 TYPE_3__* GetHub (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_HUBNAME_LEN ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  NtEnumNatList (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcEnumNat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int PackGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

PACK *SiCalledEnumNat(SERVER *s, PACK *p)
{
	char hubname[MAX_HUBNAME_LEN + 1];
	RPC_ENUM_NAT t;
	PACK *ret;
	HUB *h;
	// Validate arguments
	if (s == NULL || p == NULL)
	{
		return NewPack();
	}
	if (PackGetStr(p, "HubName", hubname, sizeof(hubname)) == false)
	{
		return NewPack();
	}
	Zero(&t, sizeof(t));

	LockHubList(s->Cedar);
	{
		h = GetHub(s->Cedar, hubname);
	}
	UnlockHubList(s->Cedar);

	if (h != NULL)
	{
		Lock(h->lock_online);
		{
			if (h->SecureNAT != NULL)
			{
				NtEnumNatList(h->SecureNAT->Nat, &t);
			}
		}
		Unlock(h->lock_online);
	}

	ReleaseHub(h);

	ret = NewPack();
	OutRpcEnumNat(ret, &t);
	FreeRpcEnumNat(&t);

	return ret;
}