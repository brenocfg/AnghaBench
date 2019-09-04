#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_4__ {scalar_t__ NumMacTable; int /*<<< orphan*/ * MacTables; } ;
typedef  int /*<<< orphan*/  RPC_ENUM_MAC_TABLE_ITEM ;
typedef  TYPE_1__ RPC_ENUM_MAC_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ReAlloc (int /*<<< orphan*/ *,int) ; 

void AdjoinRpcEnumMacTable(RPC_ENUM_MAC_TABLE *dest, RPC_ENUM_MAC_TABLE *src)
{
	UINT old_num;
	UINT i, n;
	if (dest == NULL || src == NULL)
	{
		return;
	}

	if (src->NumMacTable == 0)
	{
		return;
	}

	old_num = dest->NumMacTable;
	dest->NumMacTable += src->NumMacTable;
	dest->MacTables = ReAlloc(dest->MacTables, sizeof(RPC_ENUM_MAC_TABLE_ITEM) * dest->NumMacTable);

	n = 0;
	for (i = old_num;i < dest->NumMacTable;i++)
	{
		Copy(&dest->MacTables[i], &src->MacTables[n++], sizeof(RPC_ENUM_MAC_TABLE_ITEM));
	}
}