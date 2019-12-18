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
struct TYPE_4__ {scalar_t__ NumIpTable; int /*<<< orphan*/ * IpTables; } ;
typedef  int /*<<< orphan*/  RPC_ENUM_IP_TABLE_ITEM ;
typedef  TYPE_1__ RPC_ENUM_IP_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ReAlloc (int /*<<< orphan*/ *,int) ; 

void AdjoinRpcEnumIpTable(RPC_ENUM_IP_TABLE *dest, RPC_ENUM_IP_TABLE *src)
{
	UINT old_num;
	UINT i, n;
	if (dest == NULL || src == NULL)
	{
		return;
	}

	if (src->NumIpTable == 0)
	{
		return;
	}

	old_num = dest->NumIpTable;
	dest->NumIpTable += src->NumIpTable;
	dest->IpTables = ReAlloc(dest->IpTables, sizeof(RPC_ENUM_IP_TABLE_ITEM) * dest->NumIpTable);

	n = 0;
	for (i = old_num;i < dest->NumIpTable;i++)
	{
		Copy(&dest->IpTables[i], &src->IpTables[n++], sizeof(RPC_ENUM_IP_TABLE_ITEM));
	}
}