#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {int NumItem; TYPE_1__* Items; int /*<<< orphan*/  Name; } ;
struct TYPE_6__ {void* SubnetMask; void* IpAddress; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_L3IF ;
typedef  TYPE_2__ RPC_ENUM_L3IF ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetIp32Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumL3If(RPC_ENUM_L3IF *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_L3IF));
	t->NumItem = PackGetInt(p, "NumItem");
	PackGetStr(p, "Name", t->Name, sizeof(t->Name));
	t->Items = ZeroMalloc(sizeof(RPC_L3IF) * t->NumItem);

	for (i = 0;i < t->NumItem;i++)
	{
		RPC_L3IF *f = &t->Items[i];

		PackGetStrEx(p, "HubName", f->HubName, sizeof(f->HubName), i);
		f->IpAddress = PackGetIp32Ex(p, "IpAddress", i);
		f->SubnetMask = PackGetIp32Ex(p, "SubnetMask", i);
	}
}