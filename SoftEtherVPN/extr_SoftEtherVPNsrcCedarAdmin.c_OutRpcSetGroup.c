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
struct TYPE_3__ {int /*<<< orphan*/ * Policy; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SET_GROUP ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcPolicy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcSetGroup(PACK *p, RPC_SET_GROUP *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddStr(p, "Name", t->Name);
	PackAddUniStr(p, "Realname", t->Realname);
	PackAddUniStr(p, "Note", t->Note);
	OutRpcTraffic(p, &t->Traffic);

	if (t->Policy != NULL)
	{
		PackAddBool(p, "UsePolicy", true);
		OutRpcPolicy(p, t->Policy);
	}
}