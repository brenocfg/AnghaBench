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
struct TYPE_5__ {size_t NumPort; size_t NumFarmHub; int /*<<< orphan*/  Weight; int /*<<< orphan*/  NumTcpConnections; int /*<<< orphan*/  NumSessions; TYPE_1__* FarmHubs; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/ * Ports; int /*<<< orphan*/  Point; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Ip; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Controller; int /*<<< orphan*/  Id; } ;
struct TYPE_4__ {int /*<<< orphan*/  DynamicHub; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_2__ RPC_FARM_INFO ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddX (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcFarmInfo(PACK *p, RPC_FARM_INFO *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "Id", t->Id);
	PackAddBool(p, "Controller", t->Controller);
	PackAddTime64(p, "ConnectedTime", t->ConnectedTime);
	PackAddIp32(p, "Ip", t->Ip);
	PackAddStr(p, "Hostname", t->Hostname);
	PackAddInt(p, "Point", t->Point);
	for (i = 0;i < t->NumPort;i++)
	{
		PackAddIntEx(p, "Ports", t->Ports[i], i, t->NumPort);
	}
	PackAddX(p, "ServerCert", t->ServerCert);

	PackSetCurrentJsonGroupName(p, "HubsList");
	for (i = 0;i < t->NumFarmHub;i++)
	{
		PackAddStrEx(p, "HubName", t->FarmHubs[i].HubName, i, t->NumFarmHub);
		PackAddBoolEx(p, "DynamicHub", t->FarmHubs[i].DynamicHub, i, t->NumFarmHub);
	}
	PackSetCurrentJsonGroupName(p, NULL);

	PackAddInt(p, "NumSessions", t->NumSessions);
	PackAddInt(p, "NumTcpConnections", t->NumTcpConnections);
	PackAddInt(p, "Weight", t->Weight);
}