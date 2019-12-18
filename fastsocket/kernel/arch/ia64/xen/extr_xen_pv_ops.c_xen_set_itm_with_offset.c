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
struct TYPE_2__ {scalar_t__ itc_offset; } ;

/* Variables and functions */
 TYPE_1__* XEN_MAPPEDREGS ; 
 int /*<<< orphan*/  xen_set_itm (scalar_t__) ; 

__attribute__((used)) static void
xen_set_itm_with_offset(unsigned long val)
{
	/* ia64_cpu_local_tick() calls this with interrupt enabled. */
	/* WARN_ON(!irqs_disabled()); */
	xen_set_itm(val - XEN_MAPPEDREGS->itc_offset);
}