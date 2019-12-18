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
struct TYPE_2__ {int /*<<< orphan*/  machine_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACHINE_FLAG_HPAGE ; 
 TYPE_1__ S390_lowcore ; 
 int /*<<< orphan*/  __ctl_set_bit (int /*<<< orphan*/ ,int) ; 
 unsigned int stfl () ; 

void setup_hpage(void)
{
#ifndef CONFIG_DEBUG_PAGEALLOC
	unsigned int facilities;

	facilities = stfl();
	if (!(facilities & (1UL << 23)) || !(facilities & (1UL << 29)))
		return;
	S390_lowcore.machine_flags |= MACHINE_FLAG_HPAGE;
	__ctl_set_bit(0, 23);
#endif
}