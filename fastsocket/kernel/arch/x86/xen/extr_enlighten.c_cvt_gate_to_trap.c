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
struct trap_info {int vector; unsigned long address; int flags; int /*<<< orphan*/  cs; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ ist; int dpl; } ;
typedef  TYPE_1__ gate_desc ;

/* Variables and functions */
 scalar_t__ GATE_INTERRUPT ; 
 scalar_t__ GATE_TRAP ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ debug ; 
 scalar_t__ double_fault ; 
 unsigned long gate_offset (TYPE_1__ const) ; 
 int /*<<< orphan*/  gate_segment (TYPE_1__ const) ; 
 scalar_t__ int3 ; 
 scalar_t__ machine_check ; 
 scalar_t__ nmi ; 
 scalar_t__ stack_segment ; 
 scalar_t__ xen_debug ; 
 scalar_t__ xen_int3 ; 
 scalar_t__ xen_stack_segment ; 

__attribute__((used)) static int cvt_gate_to_trap(int vector, const gate_desc *val,
			    struct trap_info *info)
{
	unsigned long addr;

	if (val->type != GATE_TRAP && val->type != GATE_INTERRUPT)
		return 0;

	info->vector = vector;

	addr = gate_offset(*val);
#ifdef CONFIG_X86_64
	/*
	 * Look for known traps using IST, and substitute them
	 * appropriately.  The debugger ones are the only ones we care
	 * about.  Xen will handle faults like double_fault and
	 * machine_check, so we should never see them.  Warn if
	 * there's an unexpected IST-using fault handler.
	 */
	if (addr == (unsigned long)debug)
		addr = (unsigned long)xen_debug;
	else if (addr == (unsigned long)int3)
		addr = (unsigned long)xen_int3;
	else if (addr == (unsigned long)stack_segment)
		addr = (unsigned long)xen_stack_segment;
	else if (addr == (unsigned long)double_fault ||
		 addr == (unsigned long)nmi) {
		/* Don't need to handle these */
		return 0;
#ifdef CONFIG_X86_MCE
	} else if (addr == (unsigned long)machine_check) {
		return 0;
#endif
	} else {
		/* Some other trap using IST? */
		if (WARN_ON(val->ist != 0))
			return 0;
	}
#endif	/* CONFIG_X86_64 */
	info->address = addr;

	info->cs = gate_segment(*val);
	info->flags = val->dpl;
	/* interrupt gates clear IF */
	if (val->type == GATE_INTERRUPT)
		info->flags |= 1 << 2;

	return 1;
}