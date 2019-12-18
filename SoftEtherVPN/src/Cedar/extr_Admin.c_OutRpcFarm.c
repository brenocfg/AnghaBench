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
typedef  size_t UINT ;
struct TYPE_3__ {size_t NumPort; int /*<<< orphan*/  ControllerOnly; int /*<<< orphan*/  Weight; int /*<<< orphan*/  MemberPasswordPlaintext; int /*<<< orphan*/  MemberPassword; int /*<<< orphan*/  ControllerPort; int /*<<< orphan*/  ControllerName; int /*<<< orphan*/  PublicIp; int /*<<< orphan*/ * Ports; int /*<<< orphan*/  ServerType; } ;
typedef  TYPE_1__ RPC_FARM ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcFarm(PACK *p, RPC_FARM *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "ServerType", t->ServerType);
	for (i = 0;i < t->NumPort;i++)
	{
		PackAddIntEx(p, "Ports", t->Ports[i], i, t->NumPort);
	}
	PackAddIp32(p, "PublicIp", t->PublicIp);
	PackAddStr(p, "ControllerName", t->ControllerName);
	PackAddInt(p, "ControllerPort", t->ControllerPort);
	PackAddData(p, "MemberPassword", t->MemberPassword, sizeof(t->MemberPassword));
	PackAddStr(p, "MemberPasswordPlaintext", t->MemberPasswordPlaintext);
	PackAddInt(p, "Weight", t->Weight);
	PackAddBool(p, "ControllerOnly", t->ControllerOnly);
}