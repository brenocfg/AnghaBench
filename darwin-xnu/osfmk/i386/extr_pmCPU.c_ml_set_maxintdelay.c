#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* setMaxIntDelay ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_UNSET ; 
 int /*<<< orphan*/  earlyMaxIntDelay ; 
 TYPE_1__* pmDispatch ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
ml_set_maxintdelay(uint64_t mdelay)
{
    if (pmDispatch != NULL
	&& pmDispatch->setMaxIntDelay != NULL) {
	earlyMaxIntDelay = DELAY_UNSET;
	pmDispatch->setMaxIntDelay(mdelay);
    } else
	earlyMaxIntDelay = mdelay;
}