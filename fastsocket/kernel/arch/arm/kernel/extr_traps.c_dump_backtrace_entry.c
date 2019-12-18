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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int KSYM_SYMBOL_LEN ; 
 int /*<<< orphan*/  dump_mem (char*,char*,unsigned long,unsigned long) ; 
 scalar_t__ in_exception_text (unsigned long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long,...) ; 
 int /*<<< orphan*/  sprint_symbol (char*,unsigned long) ; 

void dump_backtrace_entry(unsigned long where, unsigned long from, unsigned long frame)
{
#ifdef CONFIG_KALLSYMS
	char sym1[KSYM_SYMBOL_LEN], sym2[KSYM_SYMBOL_LEN];
	sprint_symbol(sym1, where);
	sprint_symbol(sym2, from);
	printk("[<%08lx>] (%s) from [<%08lx>] (%s)\n", where, sym1, from, sym2);
#else
	printk("Function entered at [<%08lx>] from [<%08lx>]\n", where, from);
#endif

	if (in_exception_text(where))
		dump_mem("", "Exception stack", frame + 4, frame + 4 + sizeof(struct pt_regs));
}