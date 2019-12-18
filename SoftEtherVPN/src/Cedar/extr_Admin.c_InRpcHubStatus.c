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
struct TYPE_4__ {void* NumLogin; void* LastLoginTime; void* CreatedTime; void* LastCommTime; int /*<<< orphan*/  Traffic; void* SecureNATEnabled; void* NumIpTables; void* NumMacTables; void* NumGroups; void* NumUsers; void* NumAccessLists; void* NumSessionsBridge; void* NumSessionsClient; void* NumSessions; void* HubType; void* Online; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_HUB_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcHubStatus(RPC_HUB_STATUS *t, PACK *p)
{
	Zero(t, sizeof(RPC_HUB_STATUS));
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->Online = PackGetBool(p, "Online");
	t->HubType = PackGetInt(p, "HubType");
	t->NumSessions = PackGetInt(p, "NumSessions");
	t->NumSessionsClient = PackGetInt(p, "NumSessionsClient");
	t->NumSessionsBridge = PackGetInt(p, "NumSessionsBridge");
	t->NumAccessLists = PackGetInt(p, "NumAccessLists");
	t->NumUsers = PackGetInt(p, "NumUsers");
	t->NumGroups = PackGetInt(p, "NumGroups");
	t->NumMacTables = PackGetInt(p, "NumMacTables");
	t->NumIpTables = PackGetInt(p, "NumIpTables");
	t->SecureNATEnabled = PackGetBool(p, "SecureNATEnabled");
	InRpcTraffic(&t->Traffic, p);
	t->LastCommTime = PackGetInt64(p, "LastCommTime");
	t->CreatedTime = PackGetInt64(p, "CreatedTime");
	t->LastLoginTime = PackGetInt64(p, "LastLoginTime");
	t->NumLogin = PackGetInt(p, "NumLogin");
}