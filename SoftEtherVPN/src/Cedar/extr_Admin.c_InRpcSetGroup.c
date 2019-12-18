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
struct TYPE_4__ {int /*<<< orphan*/  Policy; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SET_GROUP ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcPolicy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ PackGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ZeroMalloc (int) ; 

void InRpcSetGroup(RPC_SET_GROUP *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_SET_GROUP));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	PackGetStr(p, "Name", t->Name, sizeof(t->Name));
	PackGetUniStr(p, "Realname", t->Realname, sizeof(t->Realname));
	PackGetUniStr(p, "Note", t->Note, sizeof(t->Note));
	InRpcTraffic(&t->Traffic, p);

	if (PackGetBool(p, "UsePolicy"))
	{
		t->Policy = ZeroMalloc(sizeof(POLICY));
		InRpcPolicy(t->Policy, p);
	}
}