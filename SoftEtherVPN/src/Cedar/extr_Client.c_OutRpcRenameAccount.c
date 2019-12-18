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
struct TYPE_3__ {int /*<<< orphan*/  NewName; int /*<<< orphan*/  OldName; } ;
typedef  TYPE_1__ RPC_RENAME_ACCOUNT ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcRenameAccount(PACK *p, RPC_RENAME_ACCOUNT *a)
{
	// Validate arguments
	if (a == NULL || p == NULL)
	{
		return;
	}

	PackAddUniStr(p, "OldName", a->OldName);
	PackAddUniStr(p, "NewName", a->NewName);
}