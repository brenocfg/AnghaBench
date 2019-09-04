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
typedef  scalar_t__ UINT64 ;
struct TYPE_3__ {int /*<<< orphan*/  Interrupts; } ;
typedef  TYPE_1__ L2TP_SERVER ;

/* Variables and functions */
 int /*<<< orphan*/  AddInterrupt (int /*<<< orphan*/ ,scalar_t__) ; 

void L2TPAddInterrupt(L2TP_SERVER *l2tp, UINT64 next_tick)
{
	// Validate arguments
	if (l2tp == NULL || next_tick == 0)
	{
		return;
	}

	AddInterrupt(l2tp->Interrupts, next_tick);
}