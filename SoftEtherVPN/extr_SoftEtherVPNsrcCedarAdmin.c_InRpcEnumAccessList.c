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
typedef  size_t UINT ;
struct TYPE_4__ {int NumAccess; int /*<<< orphan*/ * Accesses; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_ENUM_ACCESS_LIST ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcAccessEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void InRpcEnumAccessList(RPC_ENUM_ACCESS_LIST *a, PACK *p)
{
	UINT i;
	// Validate arguments
	if (a == NULL || p == NULL)
	{
		return;
	}

	Zero(a, sizeof(RPC_ENUM_ACCESS_LIST));
	PackGetStr(p, "HubName", a->HubName, sizeof(a->HubName));
	a->NumAccess = PackGetIndexCount(p, "Protocol");
	a->Accesses = ZeroMalloc(sizeof(ACCESS) * a->NumAccess);

	for (i = 0;i < a->NumAccess;i++)
	{
		ACCESS *e = &a->Accesses[i];

		InRpcAccessEx(e, p, i);
	}
}