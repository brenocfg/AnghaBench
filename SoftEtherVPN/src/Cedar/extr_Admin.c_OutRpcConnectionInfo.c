#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  ClientBuild; int /*<<< orphan*/  ClientVer; int /*<<< orphan*/  ServerBuild; int /*<<< orphan*/  ServerVer; int /*<<< orphan*/  ClientStr; int /*<<< orphan*/  ServerStr; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Port; int /*<<< orphan*/  Ip; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_CONNECTION_INFO ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcConnectionInfo(PACK *p, RPC_CONNECTION_INFO *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "Name", t->Name);
	PackAddIp32(p, "Ip", t->Ip);
	PackAddInt(p, "Port", t->Port);
	PackAddTime64(p, "ConnectedTime", t->ConnectedTime);
	PackAddStr(p, "Hostname", t->Hostname);
	PackAddStr(p, "ServerStr", t->ServerStr);
	PackAddStr(p, "ClientStr", t->ClientStr);
	PackAddInt(p, "ServerVer", t->ServerVer);
	PackAddInt(p, "ServerBuild", t->ServerBuild);
	PackAddInt(p, "ClientVer", t->ClientVer);
	PackAddInt(p, "ClientBuild", t->ClientBuild);
	PackAddInt(p, "Type", t->Type);
}