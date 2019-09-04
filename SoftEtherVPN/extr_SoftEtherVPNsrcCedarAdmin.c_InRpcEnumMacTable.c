#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_7__ {int NumMacTable; TYPE_1__* MacTables; int /*<<< orphan*/  HubName; } ;
struct TYPE_6__ {int /*<<< orphan*/  RemoteHostname; int /*<<< orphan*/  RemoteItem; void* UpdatedTime; void* CreatedTime; void* VlanId; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  SessionName; void* Key; } ;
typedef  TYPE_1__ RPC_ENUM_MAC_TABLE_ITEM ;
typedef  TYPE_2__ RPC_ENUM_MAC_TABLE ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBoolEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetDataEx2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt64Ex (int /*<<< orphan*/ *,char*,size_t) ; 
 void* PackGetIntEx (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,size_t) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void InRpcEnumMacTable(RPC_ENUM_MAC_TABLE *t, PACK *p)
{
	UINT i;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_ENUM_MAC_TABLE));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	t->NumMacTable = PackGetIndexCount(p, "SessionName");
	t->MacTables = ZeroMalloc(sizeof(RPC_ENUM_MAC_TABLE_ITEM) * t->NumMacTable);

	for (i = 0;i < t->NumMacTable;i++)
	{
		RPC_ENUM_MAC_TABLE_ITEM *e = &t->MacTables[i];

		e->Key = PackGetIntEx(p, "Key", i);
		PackGetStrEx(p, "SessionName", e->SessionName, sizeof(e->SessionName), i);
		PackGetDataEx2(p, "MacAddress", e->MacAddress, sizeof(e->MacAddress), i);
		e->VlanId = PackGetIntEx(p, "VlanId", i);
		e->CreatedTime = PackGetInt64Ex(p, "CreatedTime", i);
		e->UpdatedTime = PackGetInt64Ex(p, "UpdatedTime", i);
		e->RemoteItem = PackGetBoolEx(p, "RemoteItem", i);
		PackGetStrEx(p, "RemoteHostname", e->RemoteHostname, sizeof(e->RemoteHostname), i);
	}
}