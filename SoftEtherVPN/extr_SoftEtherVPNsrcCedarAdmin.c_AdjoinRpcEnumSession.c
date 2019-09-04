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
struct TYPE_4__ {scalar_t__ NumSession; int /*<<< orphan*/ * Sessions; } ;
typedef  int /*<<< orphan*/  RPC_ENUM_SESSION_ITEM ;
typedef  TYPE_1__ RPC_ENUM_SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ReAlloc (int /*<<< orphan*/ *,int) ; 

void AdjoinRpcEnumSession(RPC_ENUM_SESSION *dest, RPC_ENUM_SESSION *src)
{
	UINT old_num;
	UINT i, n;
	if (dest == NULL || src == NULL)
	{
		return;
	}

	if (src->NumSession == 0)
	{
		return;
	}

	old_num = dest->NumSession;
	dest->NumSession += src->NumSession;
	dest->Sessions = ReAlloc(dest->Sessions, sizeof(RPC_ENUM_SESSION_ITEM) * dest->NumSession);

	n = 0;
	for (i = old_num;i < dest->NumSession;i++)
	{
		Copy(&dest->Sessions[i], &src->Sessions[n++], sizeof(RPC_ENUM_SESSION_ITEM));
	}
}