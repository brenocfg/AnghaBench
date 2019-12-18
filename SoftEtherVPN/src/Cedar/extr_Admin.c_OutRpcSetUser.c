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
struct TYPE_3__ {int /*<<< orphan*/ * Policy; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  NumLogin; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  AuthData; int /*<<< orphan*/  ExpireTime; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SET_USER ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcAuthData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcSetUser(PACK *p, RPC_SET_USER *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddStr(p, "Name", t->Name);
	PackAddStr(p, "GroupName", t->GroupName);
	PackAddUniStr(p, "Realname", t->Realname);
	PackAddUniStr(p, "Note", t->Note);
	PackAddTime64(p, "CreatedTime", t->CreatedTime);
	PackAddTime64(p, "UpdatedTime", t->UpdatedTime);
	PackAddTime64(p, "ExpireTime", t->ExpireTime);
	OutRpcAuthData(p, t->AuthData, t->AuthType);
	PackAddInt(p, "NumLogin", t->NumLogin);
	OutRpcTraffic(p, &t->Traffic);

	if (t->Policy != NULL)
	{
		PackAddBool(p, "UsePolicy", true);
		OutRpcPolicy(p, t->Policy);
	}
}