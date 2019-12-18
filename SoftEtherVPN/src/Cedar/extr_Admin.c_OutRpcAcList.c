#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Priority; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  Masked; int /*<<< orphan*/  IpAddress; int /*<<< orphan*/  Deny; int /*<<< orphan*/  Id; } ;
struct TYPE_5__ {int /*<<< orphan*/  HubName; int /*<<< orphan*/ * o; } ;
typedef  TYPE_1__ RPC_AC_LIST ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ AC ;

/* Variables and functions */
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddIpEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcAcList(PACK *p, RPC_AC_LIST *t)
{
	UINT i, num;
	LIST *o;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	o = t->o;
	num = LIST_NUM(o);

	PackAddInt(p, "NumItem", num);

	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "ACList");
	for (i = 0;i < num;i++)
	{
		AC *ac = LIST_DATA(o, i);

		PackAddIntEx(p, "Id", ac->Id, i, num);
		PackAddBoolEx(p, "Deny", ac->Deny, i, num);
		PackAddIpEx(p, "IpAddress", &ac->IpAddress, i, num);
		PackAddBoolEx(p, "Masked", ac->Masked, i, num);

		PackAddIpEx(p, "SubnetMask", &ac->SubnetMask, i, num);

		PackAddIntEx(p, "Priority", ac->Priority, i, num);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}