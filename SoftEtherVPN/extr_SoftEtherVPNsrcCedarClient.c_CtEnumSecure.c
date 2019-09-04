#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int NumItem; TYPE_2__** Items; } ;
struct TYPE_7__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  Manufacturer; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  DeviceId; } ;
struct TYPE_6__ {int /*<<< orphan*/  Type; int /*<<< orphan*/  Manufacturer; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  Id; } ;
typedef  TYPE_1__ SECURE_DEVICE ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_SECURE_ITEM ;
typedef  TYPE_3__ RPC_CLIENT_ENUM_SECURE ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/ * GetSecureDeviceList () ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

bool CtEnumSecure(CLIENT *c, RPC_CLIENT_ENUM_SECURE *e)
{
	LIST *o;
	UINT i;
	// Validate arguments
	if (c == NULL || e == NULL)
	{
		return false;
	}

	o = GetSecureDeviceList();

	e->NumItem = LIST_NUM(o);
	e->Items = ZeroMalloc(sizeof(RPC_CLIENT_ENUM_SECURE_ITEM *) * e->NumItem);

	for (i = 0;i < LIST_NUM(o);i++)
	{
		RPC_CLIENT_ENUM_SECURE_ITEM *item = ZeroMalloc(sizeof(RPC_CLIENT_ENUM_SECURE_ITEM));
		SECURE_DEVICE *s = LIST_DATA(o, i);

		item->DeviceId = s->Id;
		StrCpy(item->DeviceName, sizeof(item->DeviceName), s->DeviceName);
		StrCpy(item->Manufacturer, sizeof(item->Manufacturer), s->Manufacturer);
		item->Type = s->Type;

		e->Items[i] = item;
	}

	return true;
}