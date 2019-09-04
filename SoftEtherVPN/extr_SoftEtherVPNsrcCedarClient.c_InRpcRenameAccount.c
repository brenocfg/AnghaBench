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
struct TYPE_4__ {int /*<<< orphan*/  NewName; int /*<<< orphan*/  OldName; } ;
typedef  TYPE_1__ RPC_RENAME_ACCOUNT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcRenameAccount(RPC_RENAME_ACCOUNT *a, PACK *p)
{
	// Validate arguments
	if (a == NULL || p == NULL)
	{
		return;
	}

	Zero(a, sizeof(RPC_RENAME_ACCOUNT));

	PackGetUniStr(p, "OldName", a->OldName, sizeof(a->OldName));
	PackGetUniStr(p, "NewName", a->NewName, sizeof(a->NewName));
}