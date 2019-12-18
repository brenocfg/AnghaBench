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
struct TYPE_7__ {int NumSession; TYPE_1__* Sessions; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {void* LastCommTime; void* CreatedTime; void* LastCommDormant; void* IsDormant; void* IsDormantEnabled; int /*<<< orphan*/  UniqueId; void* VLanId; int /*<<< orphan*/  RemoteHostname; void* Client_MonitorMode; void* Client_BridgeMode; void* Layer3Mode; void* BridgeMode; void* SecureNATMode; void* LinkMode; void* RemoteSession; void* PacketNum; void* PacketSize; void* CurrentNumTcp; void* MaxNumTcp; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  ClientIP; void* Ip; int /*<<< orphan*/  Username; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_SESSION_ITEM ;
typedef  TYPE_2__ RPC_ENUM_SESSION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetDataEx2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIpEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumSession(RPC_ENUM_SESSION *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_SESSION));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->NumSession = PackGetIndexCount(p, "Name");
	t->Sessions = ZeroMalloc(sizeof(RPC_ENUM_SESSION_ITEM) * t->NumSession);

	for (i = 0;i < t->NumSession;i++)
	{
		RPC_ENUM_SESSION_ITEM *e = &t->Sessions[i];

		PackGetStrEx(p, "Name", e->Name, sizeof(e->Name), i);
		PackGetStrEx(p, "Username", e->Username, sizeof(e->Username), i);
		e->Ip = PackGetIntEx(p, "Ip", i);
		PackGetIpEx(p, "ClientIP", &e->ClientIP, i);
		PackGetStrEx(p, "Hostname", e->Hostname, sizeof(e->Hostname), i);
		e->MaxNumTcp = PackGetIntEx(p, "MaxNumTcp", i);
		e->CurrentNumTcp = PackGetIntEx(p, "CurrentNumTcp", i);
		e->PacketSize = PackGetInt64Ex(p, "PacketSize", i);
		e->PacketNum = PackGetInt64Ex(p, "PacketNum", i);
		e->RemoteSession = PackGetBoolEx(p, "RemoteSession", i);
		e->LinkMode = PackGetBoolEx(p, "LinkMode", i);
		e->SecureNATMode = PackGetBoolEx(p, "SecureNATMode", i);
		e->BridgeMode = PackGetBoolEx(p, "BridgeMode", i);
		e->Layer3Mode = PackGetBoolEx(p, "Layer3Mode", i);
		e->Client_BridgeMode = PackGetBoolEx(p, "Client_BridgeMode", i);
		e->Client_MonitorMode = PackGetBoolEx(p, "Client_MonitorMode", i);
		PackGetStrEx(p, "RemoteHostname", e->RemoteHostname, sizeof(e->RemoteHostname), i);
		e->VLanId = PackGetIntEx(p, "VLanId", i);
		PackGetDataEx2(p, "UniqueId", e->UniqueId, sizeof(e->UniqueId), i);
		e->IsDormantEnabled = PackGetBoolEx(p, "IsDormantEnabled", i);
		e->IsDormant = PackGetBoolEx(p, "IsDormant", i);
		e->LastCommDormant = PackGetInt64Ex(p, "LastCommDormant", i);
		e->CreatedTime = PackGetInt64Ex(p, "CreatedTime", i);
		e->LastCommTime = PackGetInt64Ex(p, "LastCommTime", i);
	}
}