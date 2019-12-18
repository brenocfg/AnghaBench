#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_13__ {TYPE_2__* Server; } ;
struct TYPE_12__ {int NumItem; int /*<<< orphan*/ * IdList; } ;
struct TYPE_11__ {TYPE_1__* IPsecServer; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_10__ {int /*<<< orphan*/  LockSettings; int /*<<< orphan*/  EtherIPIdList; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ RPC_ENUM_ETHERIP_ID ;
typedef  int /*<<< orphan*/  ETHERIP_ID ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ERR_NOT_SUPPORTED ; 
 int ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeRpcEnumEtherIpId (TYPE_3__*) ; 
 int GetServerCapsBool (TYPE_2__*,char*) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ ,int) ; 
 int LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

UINT StEnumEtherIpId(ADMIN *a, RPC_ENUM_ETHERIP_ID *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	SERVER_ADMIN_ONLY;
	NO_SUPPORT_FOR_BRIDGE;
	if (GetServerCapsBool(s, "b_support_ipsec") == false || s->IPsecServer == NULL)
	{
		return ERR_NOT_SUPPORTED;
	}

	FreeRpcEnumEtherIpId(t);
	Zero(t, sizeof(RPC_ENUM_ETHERIP_ID));

	Lock(s->IPsecServer->LockSettings);
	{
		UINT i;
		UINT num;

		num = LIST_NUM(s->IPsecServer->EtherIPIdList);

		t->NumItem = num;
		t->IdList = ZeroMalloc(sizeof(ETHERIP_ID) * num);

		for (i = 0;i < num;i++)
		{
			ETHERIP_ID *d = &t->IdList[i];
			ETHERIP_ID *src = LIST_DATA(s->IPsecServer->EtherIPIdList, i);

			Copy(d, src, sizeof(ETHERIP_ID));
		}
	}
	Unlock(s->IPsecServer->LockSettings);

	return ERR_NO_ERROR;
}