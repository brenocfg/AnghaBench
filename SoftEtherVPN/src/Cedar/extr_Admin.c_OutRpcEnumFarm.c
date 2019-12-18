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
struct TYPE_5__ {size_t NumFarm; TYPE_1__* Farms; } ;
struct TYPE_4__ {int /*<<< orphan*/  AssignedBridgeLicense; int /*<<< orphan*/  AssignedClientLicense; int /*<<< orphan*/  NumHubs; int /*<<< orphan*/  NumTcpConnections; int /*<<< orphan*/  NumSessions; int /*<<< orphan*/  Point; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Ip; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Controller; int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ RPC_ENUM_FARM_ITEM ;
typedef  TYPE_2__ RPC_ENUM_FARM ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumFarm(PACK *p, RPC_ENUM_FARM *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackSetCurrentJsonGroupName(p, "FarmMemberList");
	for (i = 0;i < t->NumFarm;i++)
	{
		RPC_ENUM_FARM_ITEM *e = &t->Farms[i];

		PackAddIntEx(p, "Id", e->Id, i, t->NumFarm);
		PackAddBoolEx(p, "Controller", e->Controller, i, t->NumFarm);
		PackAddTime64Ex(p, "ConnectedTime", e->ConnectedTime, i, t->NumFarm);
		PackAddIp32Ex(p, "Ip", e->Ip, i, t->NumFarm);
		PackAddStrEx(p, "Hostname", e->Hostname, i, t->NumFarm);
		PackAddIntEx(p, "Point", e->Point, i, t->NumFarm);
		PackAddIntEx(p, "NumSessions", e->NumSessions, i, t->NumFarm);
		PackAddIntEx(p, "NumTcpConnections", e->NumTcpConnections, i, t->NumFarm);
		PackAddIntEx(p, "NumHubs", e->NumHubs, i, t->NumFarm);
		PackAddIntEx(p, "AssignedClientLicense", e->AssignedClientLicense, i, t->NumFarm);
		PackAddIntEx(p, "AssignedBridgeLicense", e->AssignedBridgeLicense, i, t->NumFarm);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}