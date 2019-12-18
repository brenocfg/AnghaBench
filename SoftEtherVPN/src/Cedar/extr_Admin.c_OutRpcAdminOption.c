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
struct TYPE_5__ {int /*<<< orphan*/  Descrption; int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
struct TYPE_4__ {size_t NumItem; TYPE_2__* Items; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_ADMIN_OPTION ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ ADMIN_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcAdminOption(PACK *p, RPC_ADMIN_OPTION *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);

	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "AdminOptionList");
	for (i = 0;i < t->NumItem;i++)
	{
		ADMIN_OPTION *o = &t->Items[i];

		PackAddStrEx(p, "Name", o->Name, i, t->NumItem);
		PackAddIntEx(p, "Value", o->Value, i, t->NumItem);
		PackAddUniStrEx(p, "Descrption", o->Descrption, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}