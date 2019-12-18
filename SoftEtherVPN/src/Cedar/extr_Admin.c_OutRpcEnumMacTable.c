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
struct TYPE_5__ {size_t NumMacTable; TYPE_1__* MacTables; int /*<<< orphan*/  HubName; } ;
struct TYPE_4__ {int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RemoteItem; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  VlanId; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  SessionName; int /*<<< orphan*/  Key; } ;
typedef  TYPE_1__ RPC_ENUM_MAC_TABLE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_MAC_TABLE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBoolEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  PackSetCurrentJsonGroupName (int /*<<< orphan*/ *,char*) ; 

void OutRpcEnumMacTable(PACK *p, RPC_ENUM_MAC_TABLE *t)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);

	PackSetCurrentJsonGroupName(p, "MacTable");
	for (i = 0;i < t->NumMacTable;i++)
	{
		RPC_ENUM_MAC_TABLE_ITEM *e = &t->MacTables[i];

		PackAddIntEx(p, "Key", e->Key, i, t->NumMacTable);
		PackAddStrEx(p, "SessionName", e->SessionName, i, t->NumMacTable);
		PackAddDataEx(p, "MacAddress", e->MacAddress, sizeof(e->MacAddress), i, t->NumMacTable);
		PackAddIntEx(p, "VlanId", e->VlanId, i, t->NumMacTable);
		PackAddTime64Ex(p, "CreatedTime", e->CreatedTime, i, t->NumMacTable);
		PackAddTime64Ex(p, "UpdatedTime", e->UpdatedTime, i, t->NumMacTable);
		PackAddBoolEx(p, "RemoteItem", e->RemoteItem, i, t->NumMacTable);
		PackAddStrEx(p, "RemoteHostname", e->RemoteHostname, i, t->NumMacTable);
	}
	PackSetCurrentJsonGroupName(p, NULL);
}