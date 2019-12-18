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
typedef  int uint64_t ;
struct TYPE_2__ {int (* getMaxSnoop ) () ;} ;

/* Variables and functions */
 TYPE_1__* pmDispatch ; 
 scalar_t__ pmInitDone ; 
 int stub1 () ; 

unsigned
ml_get_maxsnoop(void)
{
    uint64_t	max_snoop	= 0;

    if (pmInitDone
	&& pmDispatch != NULL
	&& pmDispatch->getMaxSnoop != NULL)
	max_snoop = pmDispatch->getMaxSnoop();

    return((unsigned)(max_snoop & 0xffffffff));
}