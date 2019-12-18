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
struct TYPE_4__ {void* FreePhys; void* UsedPhys; void* TotalPhys; void* FreeMemory; void* UsedMemory; void* TotalMemory; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ MEMINFO ;

/* Variables and functions */
 void* PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcMemInfo(MEMINFO *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(MEMINFO));
	t->TotalMemory = PackGetInt64(p, "TotalMemory");
	t->UsedMemory = PackGetInt64(p, "UsedMemory");
	t->FreeMemory = PackGetInt64(p, "FreeMemory");
	t->TotalPhys = PackGetInt64(p, "TotalPhys");
	t->UsedPhys = PackGetInt64(p, "UsedPhys");
	t->FreePhys = PackGetInt64(p, "FreePhys");
}