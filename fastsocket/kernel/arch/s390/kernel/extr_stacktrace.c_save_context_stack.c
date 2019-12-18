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
struct stack_trace {unsigned long* entries; scalar_t__ nr_entries; scalar_t__ max_entries; int /*<<< orphan*/  skip; } ;
struct stack_frame {unsigned long* gprs; unsigned long back_chain; } ;
struct TYPE_2__ {unsigned long addr; } ;
struct pt_regs {unsigned long* gprs; TYPE_1__ psw; } ;

/* Variables and functions */
 unsigned long PSW_ADDR_INSN ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 

__attribute__((used)) static unsigned long save_context_stack(struct stack_trace *trace,
					unsigned long sp,
					unsigned long low,
					unsigned long high,
					int savesched)
{
	struct stack_frame *sf;
	struct pt_regs *regs;
	unsigned long addr;

	while(1) {
		sp &= PSW_ADDR_INSN;
		if (sp < low || sp > high)
			return sp;
		sf = (struct stack_frame *)sp;
		while(1) {
			addr = sf->gprs[8] & PSW_ADDR_INSN;
			if (!trace->skip)
				trace->entries[trace->nr_entries++] = addr;
			else
				trace->skip--;
			if (trace->nr_entries >= trace->max_entries)
				return sp;
			low = sp;
			sp = sf->back_chain & PSW_ADDR_INSN;
			if (!sp)
				break;
			if (sp <= low || sp > high - sizeof(*sf))
				return sp;
			sf = (struct stack_frame *)sp;
		}
		/* Zero backchain detected, check for interrupt frame. */
		sp = (unsigned long)(sf + 1);
		if (sp <= low || sp > high - sizeof(*regs))
			return sp;
		regs = (struct pt_regs *)sp;
		addr = regs->psw.addr & PSW_ADDR_INSN;
		if (savesched || !in_sched_functions(addr)) {
			if (!trace->skip)
				trace->entries[trace->nr_entries++] = addr;
			else
				trace->skip--;
		}
		if (trace->nr_entries >= trace->max_entries)
			return sp;
		low = sp;
		sp = regs->gprs[15];
	}
}