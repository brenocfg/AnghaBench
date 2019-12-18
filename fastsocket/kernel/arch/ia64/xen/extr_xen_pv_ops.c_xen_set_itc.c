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
struct TYPE_2__ {unsigned long itc_offset; unsigned long itc_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* XEN_MAPPEDREGS ; 
 int /*<<< orphan*/  _IA64_REG_AR_ITC ; 
 unsigned long ia64_native_getreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 

__attribute__((used)) static void
xen_set_itc(unsigned long val)
{
	unsigned long mitc;

	WARN_ON(!irqs_disabled());
	mitc = ia64_native_getreg(_IA64_REG_AR_ITC);
	XEN_MAPPEDREGS->itc_offset = val - mitc;
	XEN_MAPPEDREGS->itc_last = val;
}