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
struct TYPE_3__ {int /*<<< orphan*/  FreePhys; int /*<<< orphan*/  UsedPhys; int /*<<< orphan*/  TotalPhys; int /*<<< orphan*/  FreeMemory; int /*<<< orphan*/  UsedMemory; int /*<<< orphan*/  TotalMemory; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ MEMINFO ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcMemInfo(PACK *p, MEMINFO *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddInt64(p, "TotalMemory", t->TotalMemory);
	PackAddInt64(p, "UsedMemory", t->UsedMemory);
	PackAddInt64(p, "FreeMemory", t->FreeMemory);
	PackAddInt64(p, "TotalPhys", t->TotalPhys);
	PackAddInt64(p, "UsedPhys", t->UsedPhys);
	PackAddInt64(p, "FreePhys", t->FreePhys);
}