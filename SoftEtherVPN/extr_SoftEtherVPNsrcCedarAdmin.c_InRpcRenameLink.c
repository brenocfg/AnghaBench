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
struct TYPE_4__ {int /*<<< orphan*/  NewAccountName; int /*<<< orphan*/  OldAccountName; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_RENAME_LINK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcRenameLink(RPC_RENAME_LINK *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_RENAME_LINK));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	PackGetUniStr(p, "OldAccountName", t->OldAccountName, sizeof(t->OldAccountName));
	PackGetUniStr(p, "NewAccountName", t->NewAccountName, sizeof(t->NewAccountName));
}