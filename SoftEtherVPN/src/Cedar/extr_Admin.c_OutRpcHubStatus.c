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
struct TYPE_3__ {int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  SecureNATEnabled; int /*<<< orphan*/  NumIpTables; int /*<<< orphan*/  NumMacTables; int /*<<< orphan*/  NumGroups; int /*<<< orphan*/  NumUsers; int /*<<< orphan*/  NumAccessLists; int /*<<< orphan*/  NumSessionsBridge; int /*<<< orphan*/  NumSessionsClient; int /*<<< orphan*/  NumSessions; int /*<<< orphan*/  HubType; int /*<<< orphan*/  Online; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_HUB_STATUS ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcHubStatus(PACK *p, RPC_HUB_STATUS *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddBool(p, "Online", t->Online);
	PackAddInt(p, "HubType", t->HubType);
	PackAddInt(p, "NumSessions", t->NumSessions);
	PackAddInt(p, "NumSessionsClient", t->NumSessionsClient);
	PackAddInt(p, "NumSessionsBridge", t->NumSessionsBridge);
	PackAddInt(p, "NumAccessLists", t->NumAccessLists);
	PackAddInt(p, "NumUsers", t->NumUsers);
	PackAddInt(p, "NumGroups", t->NumGroups);
	PackAddInt(p, "NumMacTables", t->NumMacTables);
	PackAddInt(p, "NumIpTables", t->NumIpTables);
	PackAddBool(p, "SecureNATEnabled", t->SecureNATEnabled);
	OutRpcTraffic(p, &t->Traffic);
	PackAddTime64(p, "LastCommTime", t->LastCommTime);
	PackAddTime64(p, "CreatedTime", t->CreatedTime);
	PackAddTime64(p, "LastLoginTime", t->LastLoginTime);
	PackAddInt(p, "NumLogin", t->NumLogin);
}