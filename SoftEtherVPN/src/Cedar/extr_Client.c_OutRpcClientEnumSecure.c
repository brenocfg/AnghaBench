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
struct TYPE_5__ {size_t NumItem; TYPE_1__** Items; } ;
struct TYPE_4__ {int /*<<< orphan*/  Manufacturer; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  Type; int /*<<< orphan*/  DeviceId; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_SECURE_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_SECURE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddNum (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcClientEnumSecure(PACK *p, RPC_CLIENT_ENUM_SECURE *e)
{
	UINT i;
	// Validate arguments
	if (e == NULL || p == NULL)
	{
		return;
	}

	PackAddNum(p, "NumItem", e->NumItem);

	PackSetCurrentJsonGroupName(p, "SecureDeviceList");
	for (i = 0;i < e->NumItem;i++)
	{
		RPC_CLIENT_ENUM_SECURE_ITEM *item = e->Items[i];

		PackAddIntEx(p, "DeviceId", item->DeviceId, i, e->NumItem);
		PackAddIntEx(p, "Type", item->Type, i, e->NumItem);
		PackAddStrEx(p, "DeviceName", item->DeviceName, i, e->NumItem);
		PackAddStrEx(p, "Manufacturer", item->Manufacturer, i, e->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}