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
struct TYPE_3__ {int /*<<< orphan*/  Title; int /*<<< orphan*/  ServicePack; int /*<<< orphan*/  Build; int /*<<< orphan*/  VerMinor; int /*<<< orphan*/  VerMajor; int /*<<< orphan*/  IsBeta; int /*<<< orphan*/  IsServer; int /*<<< orphan*/  IsNT; int /*<<< orphan*/  IsWindows; } ;
typedef  TYPE_1__ RPC_WINVER ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcWinVer(PACK *p, RPC_WINVER *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddBool(p, "V_IsWindows", t->IsWindows);
	PackAddBool(p, "V_IsNT", t->IsNT);
	PackAddBool(p, "V_IsServer", t->IsServer);
	PackAddBool(p, "V_IsBeta", t->IsBeta);
	PackAddInt(p, "V_VerMajor", t->VerMajor);
	PackAddInt(p, "V_VerMinor", t->VerMinor);
	PackAddInt(p, "V_Build", t->Build);
	PackAddInt(p, "V_ServicePack", t->ServicePack);
	PackAddStr(p, "V_Title", t->Title);
}