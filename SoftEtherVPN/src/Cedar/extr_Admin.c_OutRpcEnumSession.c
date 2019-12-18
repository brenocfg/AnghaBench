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
struct TYPE_5__ {size_t NumSession; TYPE_1__* Sessions; int /*<<< orphan*/  HubName; } ;
struct TYPE_4__ {int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  LastCommDormant; int /*<<< orphan*/  IsDormant; int /*<<< orphan*/  IsDormantEnabled; int /*<<< orphan*/  UniqueId; int /*<<< orphan*/  VLanId; int /*<<< orphan*/  Client_MonitorMode; int /*<<< orphan*/  Client_BridgeMode; int /*<<< orphan*/  Layer3Mode; int /*<<< orphan*/  BridgeMode; int /*<<< orphan*/  SecureNATMode; int /*<<< orphan*/  LinkMode; int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RemoteSession; int /*<<< orphan*/  PacketNum; int /*<<< orphan*/  PacketSize; int /*<<< orphan*/  CurrentNumTcp; int /*<<< orphan*/  MaxNumTcp; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  ClientIP; int /*<<< orphan*/  Ip; int /*<<< orphan*/  Username; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_SESSION_ITEM ;
typedef  TYPE_2__ RPC_ENUM_SESSION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddInt64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIpEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumSession(PACK *p, RPC_ENUM_SESSION *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}
	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "SessionList");
	for (i = 0;i < t->NumSession;i++)
	{
		RPC_ENUM_SESSION_ITEM *e = &t->Sessions[i];

		PackAddStrEx(p, "Name", e->Name, i, t->NumSession);
		PackAddStrEx(p, "Username", e->Username, i, t->NumSession);
		PackAddIp32Ex(p, "Ip", e->Ip, i, t->NumSession);
		PackAddIpEx(p, "ClientIP", &e->ClientIP, i, t->NumSession);
		PackAddStrEx(p, "Hostname", e->Hostname, i, t->NumSession);
		PackAddIntEx(p, "MaxNumTcp", e->MaxNumTcp, i, t->NumSession);
		PackAddIntEx(p, "CurrentNumTcp", e->CurrentNumTcp, i, t->NumSession);
		PackAddInt64Ex(p, "PacketSize", e->PacketSize, i, t->NumSession);
		PackAddInt64Ex(p, "PacketNum", e->PacketNum, i, t->NumSession);
		PackAddBoolEx(p, "RemoteSession", e->RemoteSession, i, t->NumSession);
		PackAddStrEx(p, "RemoteHostname", e->RemoteHostname, i, t->NumSession);
		PackAddBoolEx(p, "LinkMode", e->LinkMode, i, t->NumSession);
		PackAddBoolEx(p, "SecureNATMode", e->SecureNATMode, i, t->NumSession);
		PackAddBoolEx(p, "BridgeMode", e->BridgeMode, i, t->NumSession);
		PackAddBoolEx(p, "Layer3Mode", e->Layer3Mode, i, t->NumSession);
		PackAddBoolEx(p, "Client_BridgeMode", e->Client_BridgeMode, i, t->NumSession);
		PackAddBoolEx(p, "Client_MonitorMode", e->Client_MonitorMode, i, t->NumSession);
		PackAddIntEx(p, "VLanId", e->VLanId, i, t->NumSession);
		PackAddDataEx(p, "UniqueId", e->UniqueId, sizeof(e->UniqueId), i, t->NumSession);
		PackAddBoolEx(p, "IsDormantEnabled", e->IsDormantEnabled, i, t->NumSession);
		PackAddBoolEx(p, "IsDormant", e->IsDormant, i, t->NumSession);
		PackAddTime64Ex(p, "LastCommDormant", e->LastCommDormant, i, t->NumSession);
		PackAddTime64Ex(p, "CreatedTime", e->CreatedTime, i, t->NumSession);
		PackAddTime64Ex(p, "LastCommTime", e->LastCommTime, i, t->NumSession);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}