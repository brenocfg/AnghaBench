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
struct TYPE_5__ {size_t NumItem; int /*<<< orphan*/  IsLicenseSupported; TYPE_1__* Items; } ;
struct TYPE_4__ {int /*<<< orphan*/  Active; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_ENUM_DEVICE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_DEVICE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumDevice(PACK *p, RPC_ENUM_DEVICE *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "NumItem", t->NumItem);

	PackSetCurrentJsonGroupName(p, "DeviceList");
	for (i = 0;i < t->NumItem;i++)
	{
		RPC_ENUM_DEVICE_ITEM *d = &t->Items[i];

		PackAddStrEx(p, "DeviceName", d->DeviceName, i, t->NumItem);
		PackAddBoolEx(p, "Active", d->Active, i, t->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);

	PackAddBool(p, "IsLicenseSupported", t->IsLicenseSupported);
}