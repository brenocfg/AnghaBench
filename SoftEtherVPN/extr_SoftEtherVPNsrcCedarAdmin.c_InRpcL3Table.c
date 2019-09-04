#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Metric; void* GatewayAddress; void* SubnetMask; void* NetworkAddress; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_L3TABLE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcL3Table(RPC_L3TABLE *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_L3TABLE));
	PackGetStr(p, "Name", t->Name, sizeof(t->Name));
	t->NetworkAddress = PackGetIp32(p, "NetworkAddress");
	t->SubnetMask = PackGetIp32(p, "SubnetMask");
	t->GatewayAddress = PackGetIp32(p, "GatewayAddress");
	t->Metric = PackGetInt(p, "Metric");
}