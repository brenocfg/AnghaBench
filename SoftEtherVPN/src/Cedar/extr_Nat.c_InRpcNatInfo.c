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
struct TYPE_4__ {int /*<<< orphan*/  MemInfo; int /*<<< orphan*/  OsInfo; int /*<<< orphan*/  NatHostName; void* NatBuildInt; void* NatVerInt; int /*<<< orphan*/  NatBuildInfoString; int /*<<< orphan*/  NatVersionString; int /*<<< orphan*/  NatProductName; } ;
typedef  TYPE_1__ RPC_NAT_INFO ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcMemInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcOsInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcNatInfo(RPC_NAT_INFO *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_NAT_INFO));
	PackGetStr(p, "NatProductName", t->NatProductName, sizeof(t->NatProductName));
	PackGetStr(p, "NatVersionString", t->NatVersionString, sizeof(t->NatVersionString));
	PackGetStr(p, "NatBuildInfoString", t->NatBuildInfoString, sizeof(t->NatBuildInfoString));
	t->NatVerInt = PackGetInt(p, "NatVerInt");
	t->NatBuildInt = PackGetInt(p, "NatBuildInt");
	PackGetStr(p, "NatHostName", t->NatHostName, sizeof(t->NatHostName));
	InRpcOsInfo(&t->OsInfo, p);
	InRpcMemInfo(&t->MemInfo, p);
}