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
struct TYPE_4__ {int /*<<< orphan*/  Title; void* ServicePack; void* Build; void* VerMinor; void* VerMajor; void* IsBeta; void* IsServer; void* IsNT; void* IsWindows; } ;
typedef  TYPE_1__ RPC_WINVER ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcWinVer(RPC_WINVER *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_WINVER));

	t->IsWindows = PackGetBool(p, "V_IsWindows");
	t->IsNT = PackGetBool(p, "V_IsNT");
	t->IsServer = PackGetBool(p, "V_IsServer");
	t->IsBeta = PackGetBool(p, "V_IsBeta");
	t->VerMajor = PackGetInt(p, "V_VerMajor");
	t->VerMinor = PackGetInt(p, "V_VerMinor");
	t->Build = PackGetInt(p, "V_Build");
	t->ServicePack = PackGetInt(p, "V_ServicePack");
	PackGetStr(p, "V_Title", t->Title, sizeof(t->Title));
}