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
struct TYPE_5__ {size_t NumItem; TYPE_1__* Items; int /*<<< orphan*/  Name; } ;
struct TYPE_4__ {int /*<<< orphan*/  Metric; int /*<<< orphan*/  GatewayAddress; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  NetworkAddress; } ;
typedef  TYPE_1__ RPC_L3TABLE ;
typedef  TYPE_2__ RPC_ENUM_L3TABLE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumL3Table(PACK *p, RPC_ENUM_L3TABLE *t)
{
	UINT i;
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);
	PackAddStr(p, "Name", t->Name);

	PackSetCurrentJsonGroupName(p, "L3Table");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_L3TABLE *e = &t->Items[i];

		PackAddIp32Ex(p, "NetworkAddress", e->NetworkAddress, i, t->NumItem);
		PackAddIp32Ex(p, "SubnetMask", e->SubnetMask, i, t->NumItem);
		PackAddIp32Ex(p, "GatewayAddress", e->GatewayAddress, i, t->NumItem);
		PackAddIntEx(p, "Metric", e->Metric, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}