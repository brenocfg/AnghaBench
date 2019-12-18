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
typedef  size_t UINT ;
struct TYPE_7__ {int NumItem; TYPE_1__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {void* TcpStatus; void* RecvSize; void* SendSize; void* LastCommTime; void* CreatedTime; void* DestPort; int /*<<< orphan*/  DestHost; void* DestIp; void* SrcPort; int /*<<< orphan*/  SrcHost; void* SrcIp; void* Protocol; void* Id; } ;
typedef  TYPE_1__ RPC_ENUM_NAT_ITEM ;
typedef  TYPE_2__ RPC_ENUM_NAT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumNat(RPC_ENUM_NAT *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_NAT));
	t->NumItem = PackGetInt(p, "NumItem");
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->Items = ZeroMalloc(sizeof(RPC_ENUM_NAT_ITEM) * t->NumItem);
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_NAT_ITEM *e = &t->Items[i];

		e->Id = PackGetIntEx(p, "Id", i);
		e->Protocol = PackGetIntEx(p, "Protocol", i);
		e->SrcIp = PackGetIntEx(p, "SrcIp", i);
		PackGetStrEx(p, "SrcHost", e->SrcHost, sizeof(e->SrcHost), i);
		e->SrcPort = PackGetIntEx(p, "SrcPort", i);
		e->DestIp = PackGetIntEx(p, "DestIp", i);
		PackGetStrEx(p, "DestHost", e->DestHost, sizeof(e->DestHost), i);
		e->DestPort = PackGetIntEx(p, "DestPort", i);
		e->CreatedTime = PackGetInt64Ex(p, "CreatedTime", i);
		e->LastCommTime = PackGetInt64Ex(p, "LastCommTime", i);
		e->SendSize = PackGetInt64Ex(p, "SendSize", i);
		e->RecvSize = PackGetInt64Ex(p, "RecvSize", i);
		e->TcpStatus = PackGetIntEx(p, "TcpStatus", i);
	}
}