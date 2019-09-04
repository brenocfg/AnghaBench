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
struct TYPE_2__ {int /*<<< orphan*/  (* getMaxIntDelay ) () ;} ;

/* Variables and functions */
 TYPE_1__* pmDispatch ; 
 int /*<<< orphan*/  stub1 () ; 

uint64_t
ml_get_maxintdelay(void)
{
    uint64_t	max_delay	= 0;

    if (pmDispatch != NULL
	&& pmDispatch->getMaxIntDelay != NULL)
	max_delay = pmDispatch->getMaxIntDelay();

    return(max_delay);
}