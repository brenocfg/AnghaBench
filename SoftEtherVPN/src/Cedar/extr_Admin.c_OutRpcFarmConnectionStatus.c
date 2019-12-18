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
struct TYPE_3__ {int /*<<< orphan*/  NumFailed; int /*<<< orphan*/  NumTry; int /*<<< orphan*/  NumConnected; int /*<<< orphan*/  FirstConnectedTime; int /*<<< orphan*/  CurrentConnectedTime; int /*<<< orphan*/  StartedTime; int /*<<< orphan*/  LastError; int /*<<< orphan*/  Online; int /*<<< orphan*/  Port; int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ RPC_FARM_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcFarmConnectionStatus(PACK *p, RPC_FARM_CONNECTION_STATUS *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddIp32(p, "Ip", t->Ip);
	PackAddInt(p, "Port", t->Port);
	PackAddBool(p, "Online", t->Online);
	PackAddInt(p, "LastError", t->LastError);
	PackAddTime64(p, "StartedTime", t->StartedTime);
	PackAddTime64(p, "CurrentConnectedTime", t->CurrentConnectedTime);
	PackAddTime64(p, "FirstConnectedTime", t->FirstConnectedTime);
	PackAddInt(p, "NumConnected", t->NumConnected);
	PackAddInt(p, "NumTry", t->NumTry);
	PackAddInt(p, "NumFailed", t->NumFailed);
}