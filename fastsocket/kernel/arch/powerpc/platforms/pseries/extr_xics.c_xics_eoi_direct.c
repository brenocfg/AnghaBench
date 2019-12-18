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
struct TYPE_2__ {scalar_t__ hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  direct_xirr_info_set (int) ; 
 int /*<<< orphan*/  iosync () ; 
 TYPE_1__* irq_map ; 

__attribute__((used)) static void xics_eoi_direct(unsigned int virq)
{
	unsigned int irq = (unsigned int)irq_map[virq].hwirq;

	iosync();
	direct_xirr_info_set((0xff << 24) | irq);
}