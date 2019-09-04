#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_6__ {int NumPort; int NumFarmHub; void* Weight; void* NumTcpConnections; void* NumSessions; TYPE_1__* FarmHubs; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/ * Ports; void* Point; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Ip; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Controller; void* Id; } ;
struct TYPE_5__ {int /*<<< orphan*/  DynamicHub; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_2__ RPC_FARM_INFO ;
typedef  int /*<<< orphan*/  RPC_FARM_HUB ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  PackGetX (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 

void InRpcFarmInfo(RPC_FARM_INFO *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_FARM_INFO));
	t->Id = PackGetInt(p, "Id");
	t->Controller = PackGetBool(p, "Controller");
	t->ConnectedTime = PackGetInt64(p, "ConnectedTime");
	t->Ip = PackGetIp32(p, "Ip");
	PackGetStr(p, "Hostname", t->Hostname, sizeof(t->Hostname));
	t->Point = PackGetInt(p, "Point");
	t->NumPort = PackGetIndexCount(p, "Ports");
	t->Ports = ZeroMalloc(sizeof(UINT) * t->NumPort);
	for (i = 0;i < t->NumPort;i++)
	{
		t->Ports[i] = PackGetIntEx(p, "Ports", i);
	}
	t->ServerCert = PackGetX(p, "ServerCert");
	t->NumFarmHub = PackGetIndexCount(p, "HubName");
	t->FarmHubs = ZeroMalloc(sizeof(RPC_FARM_HUB) * t->NumFarmHub);
	for (i = 0;i < t->NumFarmHub;i++)
	{
		PackGetStrEx(p, "HubName", t->FarmHubs[i].HubName, sizeof(t->FarmHubs[i].HubName), i);
		t->FarmHubs[i].DynamicHub = PackGetBoolEx(p, "DynamicHub", i);
	}
	t->NumSessions = PackGetInt(p, "NumSessions");
	t->NumTcpConnections = PackGetInt(p, "NumTcpConnections");
	t->Weight = PackGetInt(p, "Weight");
}