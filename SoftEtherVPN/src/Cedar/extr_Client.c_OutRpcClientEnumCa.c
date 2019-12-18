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
struct TYPE_4__ {int /*<<< orphan*/  Expires; int /*<<< orphan*/  IssuerName; int /*<<< orphan*/  SubjectName; int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ RPC_CLIENT_ENUM_CA_ITEM ;
typedef  TYPE_2__ RPC_CLIENT_ENUM_CA ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddNum (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddUniStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcClientEnumCa(PACK *p, RPC_CLIENT_ENUM_CA *e)
{
	UINT i;
	// Validate arguments
	if (e == NULL || p == NULL)
	{
		return;
	}

	PackAddNum(p, "NumItem", e->NumItem);

	PackSetCurrentJsonGroupName(p, "CAList");
	for (i = 0;i < e->NumItem;i++)
	{
		RPC_CLIENT_ENUM_CA_ITEM *item = e->Items[i];
		PackAddIntEx(p, "Key", item->Key, i, e->NumItem);
		PackAddUniStrEx(p, "SubjectName", item->SubjectName, i, e->NumItem);
		PackAddUniStrEx(p, "IssuerName", item->IssuerName, i, e->NumItem);
		PackAddTime64Ex(p, "Expires", item->Expires, i, e->NumItem);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}