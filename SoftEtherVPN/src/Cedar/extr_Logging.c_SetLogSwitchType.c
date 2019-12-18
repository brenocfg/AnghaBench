#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  SwitchType; } ;
typedef  TYPE_1__ LOG ;

/* Variables and functions */
 int /*<<< orphan*/  LockLog (TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockLog (TYPE_1__*) ; 

void SetLogSwitchType(LOG *g, UINT switch_type)
{
	// Validate arguments
	if (g == NULL)
	{
		return;
	}

	LockLog(g);
	{
		g->SwitchType = switch_type;
	}
	UnlockLog(g);
}