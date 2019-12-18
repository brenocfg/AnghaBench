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
struct TYPE_7__ {int NumItem; TYPE_1__* Items; } ;
struct TYPE_6__ {void* Online; void* Active; void* NumTables; void* NumInterfaces; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_ENUM_L3SW_ITEM ;
typedef  TYPE_2__ RPC_ENUM_L3SW ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumL3Sw(RPC_ENUM_L3SW *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_L3SW));
	t->NumItem = PackGetInt(p, "NumItem");
	t->Items = ZeroMalloc(sizeof(RPC_ENUM_L3SW_ITEM) * t->NumItem);

	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_L3SW_ITEM *s = &t->Items[i];

		PackGetStrEx(p, "Name", s->Name, sizeof(s->Name), i);
		s->NumInterfaces = PackGetIntEx(p, "NumInterfaces", i);
		s->NumTables = PackGetIntEx(p, "NumTables", i);
		s->Active = PackGetBoolEx(p, "Active", i);
		s->Online = PackGetBoolEx(p, "Online", i);
	}
}