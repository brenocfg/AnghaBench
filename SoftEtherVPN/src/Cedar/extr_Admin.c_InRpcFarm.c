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
typedef  size_t UINT ;
struct TYPE_4__ {int NumPort; int /*<<< orphan*/  ControllerOnly; void* Weight; int /*<<< orphan*/  MemberPasswordPlaintext; int /*<<< orphan*/  MemberPassword; void* ControllerPort; int /*<<< orphan*/  ControllerName; int /*<<< orphan*/  PublicIp; int /*<<< orphan*/ * Ports; void* ServerType; } ;
typedef  TYPE_1__ RPC_FARM ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void InRpcFarm(RPC_FARM *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_FARM));
	t->ServerType = PackGetInt(p, "ServerType");
	t->NumPort = PackGetIndexCount(p, "Ports");
	t->Ports = ZeroMalloc(sizeof(UINT) * t->NumPort);
	for (i = 0;i < t->NumPort;i++)
	{
		t->Ports[i] = PackGetIntEx(p, "Ports", i);
	}
	t->PublicIp = PackGetIp32(p, "PublicIp");
	PackGetStr(p, "ControllerName", t->ControllerName, sizeof(t->ControllerName));
	t->ControllerPort = PackGetInt(p, "ControllerPort");
	PackGetData2(p, "MemberPassword", t->MemberPassword, sizeof(t->MemberPassword));
	PackGetStr(p, "MemberPasswordPlaintext", t->MemberPasswordPlaintext, sizeof(t->MemberPasswordPlaintext));
	t->Weight = PackGetInt(p, "Weight");
	t->ControllerOnly = PackGetBool(p, "ControllerOnly");
}