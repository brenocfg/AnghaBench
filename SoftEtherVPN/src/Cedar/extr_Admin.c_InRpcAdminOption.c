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
struct TYPE_7__ {int /*<<< orphan*/  Descrption; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
struct TYPE_6__ {int NumItem; TYPE_2__* Items; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_ADMIN_OPTION ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ ADMIN_OPTION ;

/* Variables and functions */
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  PackGetUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 

void InRpcAdminOption(RPC_ADMIN_OPTION *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ADMIN_OPTION));
	t->NumItem = PackGetIndexCount(p, "Name");
	t->Items = ZeroMalloc(sizeof(ADMIN_OPTION) * t->NumItem);

	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));

	for (i = 0;i < t->NumItem;i++)
	{
		ADMIN_OPTION *o = &t->Items[i];

		PackGetStrEx(p, "Name", o->Name, sizeof(o->Name), i);
		o->Value = PackGetIntEx(p, "Value", i);
		PackGetUniStrEx(p, "Descrption", o->Descrption, sizeof(o->Descrption), i);
	}
}