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
struct TYPE_3__ {int /*<<< orphan*/  MemInfo; int /*<<< orphan*/  OsInfo; int /*<<< orphan*/  NatHostName; int /*<<< orphan*/  NatBuildInt; int /*<<< orphan*/  NatVerInt; int /*<<< orphan*/  NatBuildInfoString; int /*<<< orphan*/  NatVersionString; int /*<<< orphan*/  NatProductName; } ;
typedef  TYPE_1__ RPC_NAT_INFO ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcMemInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OutRpcOsInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcNatInfo(PACK *p, RPC_NAT_INFO *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "NatProductName", t->NatProductName);
	PackAddStr(p, "NatVersionString", t->NatVersionString);
	PackAddStr(p, "NatBuildInfoString", t->NatBuildInfoString);
	PackAddInt(p, "NatVerInt", t->NatVerInt);
	PackAddInt(p, "NatBuildInt", t->NatBuildInt);
	PackAddStr(p, "NatHostName", t->NatHostName);
	OutRpcOsInfo(p, &t->OsInfo);
	OutRpcMemInfo(p, &t->MemInfo);
}