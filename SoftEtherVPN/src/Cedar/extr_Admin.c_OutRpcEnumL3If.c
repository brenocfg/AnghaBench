#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {size_t NumItem; TYPE_1__* Items; int /*<<< orphan*/  Name; } ;
struct TYPE_4__ {int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_L3IF ;
typedef  TYPE_2__ RPC_ENUM_L3IF ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddIp32Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumL3If(PACK *p, RPC_ENUM_L3IF *t)
{
	UINT i;
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);
	PackAddStr(p, "Name", t->Name);

	PackSetCurrentJsonGroupName(p, "L3IFList");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_L3IF *f = &t->Items[i];

		PackAddStrEx(p, "HubName", f->HubName, i, t->NumItem);
		PackAddIp32Ex(p, "IpAddress", f->IpAddress, i, t->NumItem);
		PackAddIp32Ex(p, "SubnetMask", f->SubnetMask, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}