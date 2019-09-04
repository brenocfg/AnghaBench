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
struct TYPE_3__ {int /*<<< orphan*/  NewAccountName; int /*<<< orphan*/  OldAccountName; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_RENAME_LINK ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcRenameLink(PACK *p, RPC_RENAME_LINK *t)
{
	// Validate arguments
	if (p == NULL || t == NULL)
	{
		return;
	}

	PackAddStr(p, "HubName", t->HubName);
	PackAddUniStr(p, "OldAccountName", t->OldAccountName);
	PackAddUniStr(p, "NewAccountName", t->NewAccountName);
}