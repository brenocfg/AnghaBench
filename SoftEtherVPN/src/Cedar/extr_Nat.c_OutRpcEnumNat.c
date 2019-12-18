#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t NumItem; TYPE_1__* Items; int /*<<< orphan*/  HubName; } ;
struct TYPE_4__ {int /*<<< orphan*/  TcpStatus; int /*<<< orphan*/  RecvSize; int /*<<< orphan*/  SendSize; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  DestPort; int /*<<< orphan*/  DestHost; int /*<<< orphan*/  DestIp; int /*<<< orphan*/  SrcPort; int /*<<< orphan*/  SrcHost; int /*<<< orphan*/  SrcIp; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ RPC_ENUM_NAT_ITEM ;
typedef  TYPE_2__ RPC_ENUM_NAT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddInt64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumNat(PACK *p, RPC_ENUM_NAT *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);
	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "NatTable");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_NAT_ITEM *e = &t->Items[i];

		PackAddIntEx(p, "Id", e->Id, i, t->NumItem);
		PackAddIntEx(p, "Protocol", e->Protocol, i, t->NumItem);
		PackAddIp32Ex(p, "SrcIp", e->SrcIp, i, t->NumItem);
		PackAddStrEx(p, "SrcHost", e->SrcHost, i, t->NumItem);
		PackAddIntEx(p, "SrcPort", e->SrcPort, i, t->NumItem);
		PackAddIp32Ex(p, "DestIp", e->DestIp, i, t->NumItem);
		PackAddStrEx(p, "DestHost", e->DestHost, i, t->NumItem);
		PackAddIntEx(p, "DestPort", e->DestPort, i, t->NumItem);
		PackAddTime64Ex(p, "CreatedTime", e->CreatedTime, i, t->NumItem);
		PackAddTime64Ex(p, "LastCommTime", e->LastCommTime, i, t->NumItem);
		PackAddInt64Ex(p, "SendSize", e->SendSize, i, t->NumItem);
		PackAddInt64Ex(p, "RecvSize", e->RecvSize, i, t->NumItem);
		PackAddIntEx(p, "TcpStatus", e->TcpStatus, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}