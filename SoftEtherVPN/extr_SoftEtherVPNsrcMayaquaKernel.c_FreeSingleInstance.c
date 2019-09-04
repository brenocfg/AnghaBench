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
struct TYPE_4__ {struct TYPE_4__* Name; int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ INSTANCE ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  OSFreeSingleInstance (int /*<<< orphan*/ ) ; 

void FreeSingleInstance(INSTANCE *inst)
{
	// Validate arguments
	if (inst == NULL)
	{
		return;
	}

	OSFreeSingleInstance(inst->pData);

	if (inst->Name != NULL)
	{
		Free(inst->Name);
	}
	Free(inst);
}