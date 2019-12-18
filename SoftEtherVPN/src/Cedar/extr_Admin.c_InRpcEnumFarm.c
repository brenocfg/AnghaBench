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
struct TYPE_7__ {int NumFarm; TYPE_1__* Farms; } ;
struct TYPE_6__ {void* AssignedBridgeLicense; void* AssignedClientLicense; void* NumHubs; void* NumTcpConnections; void* NumSessions; void* Point; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Ip; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Controller; void* Id; } ;
typedef  TYPE_1__ RPC_ENUM_FARM_ITEM ;
typedef  TYPE_2__ RPC_ENUM_FARM ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIp32Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumFarm(RPC_ENUM_FARM *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_FARM));
	t->NumFarm = PackGetIndexCount(p, "Id");
	t->Farms = ZeroMalloc(sizeof(RPC_ENUM_FARM_ITEM) * t->NumFarm);

	for (i = 0;i < t->NumFarm;i++)
	{
		RPC_ENUM_FARM_ITEM *e = &t->Farms[i];

		e->Id = PackGetIntEx(p, "Id", i);
		e->Controller = PackGetBoolEx(p, "Controller", i);
		e->ConnectedTime = PackGetInt64Ex(p, "ConnectedTime", i);
		e->Ip = PackGetIp32Ex(p, "Ip", i);
		PackGetStrEx(p, "Hostname", e->Hostname, sizeof(e->Hostname), i);
		e->Point = PackGetIntEx(p, "Point", i);
		e->NumSessions = PackGetIntEx(p, "NumSessions", i);
		e->NumTcpConnections = PackGetIntEx(p, "NumTcpConnections", i);
		e->NumHubs = PackGetIntEx(p, "NumHubs", i);
		e->AssignedClientLicense = PackGetIntEx(p, "AssignedClientLicense", i);
		e->AssignedBridgeLicense = PackGetIntEx(p, "AssignedBridgeLicense", i);
	}
}