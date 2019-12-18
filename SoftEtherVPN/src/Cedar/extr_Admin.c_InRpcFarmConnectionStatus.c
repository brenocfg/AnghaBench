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
struct TYPE_4__ {void* NumFailed; void* NumTry; void* NumConnected; void* FirstConnectedTime; void* CurrentConnectedTime; void* StartedTime; void* LastError; int /*<<< orphan*/  Online; void* Port; int /*<<< orphan*/  Ip; } ;
typedef  TYPE_1__ RPC_FARM_CONNECTION_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcFarmConnectionStatus(RPC_FARM_CONNECTION_STATUS *t, PACK *p)
{
	Zero(t, sizeof(RPC_FARM_CONNECTION_STATUS));
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	t->Ip = PackGetIp32(p, "Ip");
	t->Port = PackGetInt(p, "Port");
	t->Online = PackGetBool(p, "Online");
	t->LastError = PackGetInt(p, "LastError");
	t->StartedTime = PackGetInt64(p, "StartedTime");
	t->CurrentConnectedTime = PackGetInt64(p, "CurrentConnectedTime");
	t->FirstConnectedTime = PackGetInt64(p, "FirstConnectedTime");
	t->NumConnected = PackGetInt(p, "NumConnected");
	t->NumTry = PackGetInt(p, "NumTry");
	t->NumFailed = PackGetInt(p, "NumFailed");
}