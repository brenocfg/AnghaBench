#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_3__ {size_t NumItem; int /*<<< orphan*/ * ItemType; int /*<<< orphan*/ * ItemName; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_1__ RPC_ENUM_OBJECT_IN_SECURE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddNum (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumObjectInSecure(PACK *p, RPC_ENUM_OBJECT_IN_SECURE *e)
{
	UINT i;
	// Validate arguments
	if (e == NULL || p == NULL)
	{
		return;
	}

	PackAddNum(p, "NumItem", e->NumItem);
	PackAddInt(p, "hWnd", e->hWnd);

	PackSetCurrentJsonGroupName(p, "ObjectList");
	for (i = 0;i < e->NumItem;i++)
	{
		PackAddStrEx(p, "ItemName", e->ItemName[i], i, e->NumItem);
		PackAddIntEx(p, "ItemType", e->ItemType[i], i, e->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}