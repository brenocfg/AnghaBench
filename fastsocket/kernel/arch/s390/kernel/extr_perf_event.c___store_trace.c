#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stack_frame {unsigned long* gprs; unsigned long back_chain; } ;
struct pt_regs {unsigned long* gprs; } ;
struct perf_callchain_entry {int dummy; } ;

/* Variables and functions */
 unsigned long PSW_ADDR_INSN ; 
 int /*<<< orphan*/  perf_callchain_store (struct perf_callchain_entry*,unsigned long) ; 

__attribute__((used)) static unsigned long __store_trace(struct perf_callchain_entry *entry,
				   unsigned long sp,
				   unsigned long low, unsigned long high)
{
	struct stack_frame *sf;
	struct pt_regs *regs;

	while (1) {
		sp = sp & PSW_ADDR_INSN;
		if (sp < low || sp > high - sizeof(*sf))
			return sp;
		sf = (struct stack_frame *) sp;
		perf_callchain_store(entry, sf->gprs[8] & PSW_ADDR_INSN);
		/* Follow the backchain. */
		while (1) {
			low = sp;
			sp = sf->back_chain & PSW_ADDR_INSN;
			if (!sp)
				break;
			if (sp <= low || sp > high - sizeof(*sf))
				return sp;
			sf = (struct stack_frame *) sp;
			perf_callchain_store(entry,
					     sf->gprs[8] & PSW_ADDR_INSN);
		}
		/* Zero backchain detected, check for interrupt frame. */
		sp = (unsigned long) (sf + 1);
		if (sp <= low || sp > high - sizeof(*regs))
			return sp;
		regs = (struct pt_regs *) sp;
		perf_callchain_store(entry, sf->gprs[8] & PSW_ADDR_INSN);
		low = sp;
		sp = regs->gprs[15];
	}
}