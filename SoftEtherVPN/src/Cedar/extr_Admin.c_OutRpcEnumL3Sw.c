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
struct TYPE_5__ {size_t NumItem; TYPE_1__* Items; } ;
struct TYPE_4__ {int /*<<< orphan*/  Online; int /*<<< orphan*/  Active; int /*<<< orphan*/  NumTables; int /*<<< orphan*/  NumInterfaces; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_L3SW_ITEM ;
typedef  TYPE_2__ RPC_ENUM_L3SW ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumL3Sw(PACK *p, RPC_ENUM_L3SW *t)
{
	UINT i;
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);

	PackSetCurrentJsonGroupName(p, "L3SWList");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_L3SW_ITEM *s = &t->Items[i];

		PackAddStrEx(p, "Name", s->Name, i, t->NumItem);
		PackAddIntEx(p, "NumInterfaces", s->NumInterfaces, i, t->NumItem);
		PackAddIntEx(p, "NumTables", s->NumTables, i, t->NumItem);
		PackAddBoolEx(p, "Active", s->Active, i, t->NumItem);
		PackAddBoolEx(p, "Online", s->Online, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}