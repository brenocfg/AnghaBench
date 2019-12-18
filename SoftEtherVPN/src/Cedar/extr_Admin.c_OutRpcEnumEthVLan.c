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
struct TYPE_4__ {int /*<<< orphan*/  Enabled; int /*<<< orphan*/  Support; int /*<<< orphan*/  DriverType; int /*<<< orphan*/  DriverName; int /*<<< orphan*/  DeviceInstanceId; int /*<<< orphan*/  Guid; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_ENUM_ETH_VLAN_ITEM ;
typedef  TYPE_2__ RPC_ENUM_ETH_VLAN ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumEthVLan(PACK *p, RPC_ENUM_ETH_VLAN *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackSetCurrentJsonGroupName(p, "Devices");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_ETH_VLAN_ITEM *e = &t->Items[i];

		PackAddStrEx(p, "DeviceName", e->DeviceName, i, t->NumItem);
		PackAddStrEx(p, "Guid", e->Guid, i, t->NumItem);
		PackAddStrEx(p, "DeviceInstanceId", e->DeviceInstanceId, i, t->NumItem);
		PackAddStrEx(p, "DriverName", e->DriverName, i, t->NumItem);
		PackAddStrEx(p, "DriverType", e->DriverType, i, t->NumItem);
		PackAddBoolEx(p, "Support", e->Support, i, t->NumItem);
		PackAddBoolEx(p, "Enabled", e->Enabled, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}