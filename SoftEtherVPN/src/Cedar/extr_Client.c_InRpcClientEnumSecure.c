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
typedef  size_t UINT ;
struct TYPE_6__ {int NumItem; TYPE_1__** Items; } ;
struct TYPE_5__ {int /*<<< orphan*/  Manufacturer; int /*<<< orphan*/  DeviceName; void* Type; void* DeviceId; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_SECURE_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_SECURE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int PackGetNum (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 void* ZeroMalloc (int) ; 

void InRpcClientEnumSecure(RPC_CLIENT_ENUM_SECURE *e, PACK *p)
{
	UINT i;
	// Validate arguments
	if (e == NULL || p == NULL)
	{
		return;
	}

	Zero(e, sizeof(RPC_CLIENT_ENUM_SECURE));

	e->NumItem = PackGetNum(p, "NumItem");
	e->Items = ZeroMalloc(sizeof(RPC_CLIENT_ENUM_SECURE_ITEM *) * e->NumItem);
	for (i = 0;i < e->NumItem;i++)
	{
		RPC_CLIENT_ENUM_SECURE_ITEM *item = e->Items[i] = ZeroMalloc(sizeof(RPC_CLIENT_ENUM_SECURE_ITEM));

		item->DeviceId = PackGetIntEx(p, "DeviceId", i);
		item->Type = PackGetIntEx(p, "Type", i);
		PackGetStrEx(p, "DeviceName", item->DeviceName, sizeof(item->DeviceName), i);
		PackGetStrEx(p, "Manufacturer", item->Manufacturer, sizeof(item->Manufacturer), i);
	}
}