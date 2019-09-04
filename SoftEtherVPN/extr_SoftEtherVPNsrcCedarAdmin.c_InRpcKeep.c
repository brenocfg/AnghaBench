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
struct TYPE_4__ {void* KeepConnectInterval; void* KeepConnectProtocol; void* KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; int /*<<< orphan*/  UseKeepConnect; } ;
typedef  TYPE_1__ RPC_KEEP ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcKeep(RPC_KEEP *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_KEEP));
	t->UseKeepConnect = PackGetBool(p, "UseKeepConnect");
	PackGetStr(p, "KeepConnectHost", t->KeepConnectHost, sizeof(t->KeepConnectHost));
	t->KeepConnectPort = PackGetInt(p, "KeepConnectPort");
	t->KeepConnectProtocol = PackGetInt(p, "KeepConnectProtocol");
	t->KeepConnectInterval = PackGetInt(p, "KeepConnectInterval");
}