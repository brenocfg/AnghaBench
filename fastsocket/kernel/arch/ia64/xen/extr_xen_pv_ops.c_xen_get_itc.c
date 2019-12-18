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
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 unsigned long ia64_native_getreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned long
xen_get_itc(void)
{
	unsigned long res;
	unsigned long itc_offset;
	unsigned long itc_last;
	unsigned long ret_itc_last;

	itc_offset = XEN_MAPPEDREGS->itc_offset;
	do {
		itc_last = XEN_MAPPEDREGS->itc_last;
		res = ia64_native_getreg(_IA64_REG_AR_ITC);
		res += itc_offset;
		if (itc_last >= res)
			res = itc_last + 1;
		ret_itc_last = cmpxchg(&XEN_MAPPEDREGS->itc_last,
				       itc_last, res);
	} while (unlikely(ret_itc_last != itc_last));
	return res;

#if 0
	/* ia64_itc_udelay() calls ia64_get_itc() with interrupt enabled.
	   Should it be paravirtualized instead? */
	WARN_ON(!irqs_disabled());
	itc_offset = XEN_MAPPEDREGS->itc_offset;
	itc_last = XEN_MAPPEDREGS->itc_last;
	res = ia64_native_getreg(_IA64_REG_AR_ITC);
	res += itc_offset;
	if (itc_last >= res)
		res = itc_last + 1;
	XEN_MAPPEDREGS->itc_last = res;
	return res;
#endif
}