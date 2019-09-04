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
struct TYPE_4__ {void* Type; void* ClientBuild; void* ClientVer; void* ServerBuild; void* ServerVer; int /*<<< orphan*/  ClientStr; int /*<<< orphan*/  ServerStr; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  ConnectedTime; void* Port; int /*<<< orphan*/  Ip; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_CONNECTION_INFO ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcConnectionInfo(RPC_CONNECTION_INFO *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_CONNECTION_INFO));
	PackGetStr(p, "Name", t->Name, sizeof(t->Name));
	t->Ip = PackGetIp32(p, "Ip");
	t->Port = PackGetInt(p, "Port");
	t->ConnectedTime = PackGetInt64(p, "ConnectedTime");
	PackGetStr(p, "Hostname", t->Hostname, sizeof(t->Hostname));
	PackGetStr(p, "ServerStr", t->ServerStr, sizeof(t->ServerStr));
	PackGetStr(p, "ClientStr", t->ClientStr, sizeof(t->ClientStr));
	t->ServerVer = PackGetInt(p, "ServerVer");
	t->ServerBuild = PackGetInt(p, "ServerBuild");
	t->ClientVer = PackGetInt(p, "ClientVer");
	t->ClientBuild = PackGetInt(p, "ClientBuild");
	t->Type = PackGetInt(p, "Type");
}