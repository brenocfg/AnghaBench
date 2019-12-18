#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {void* Priority; int /*<<< orphan*/  SubnetMask; void* Masked; int /*<<< orphan*/  IpAddress; void* Deny; void* Id; } ;
struct TYPE_8__ {int /*<<< orphan*/ * o; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_AC_LIST ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ AC ;

/* Variables and functions */
 int /*<<< orphan*/  AddAc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/ * NewAcList () ; 
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackGetIpEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void InRpcAcList(RPC_AC_LIST *t, PACK *p)
{
	UINT i;
	LIST *o;
	UINT num;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_AC_LIST));
	o = NewAcList();

	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	num = PackGetIndexCount(p, "IpAddress");

	for (i = 0;i < num;i++)
	{
		AC *ac = ZeroMalloc(sizeof(AC));

		ac->Id = PackGetIntEx(p, "Id", i);
		ac->Deny = PackGetBoolEx(p, "Deny", i);
		PackGetIpEx(p, "IpAddress", &ac->IpAddress, i);
		ac->Masked = PackGetBoolEx(p, "Masked", i);

		if (ac->Masked)
		{
			PackGetIpEx(p, "SubnetMask", &ac->SubnetMask, i);
		}

		ac->Priority = PackGetIntEx(p, "Priority", i);

		AddAc(o, ac);

		Free(ac);
	}

	t->o = o;
}