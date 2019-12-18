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
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  kstack_end (unsigned long*) ; 
 int /*<<< orphan*/  print_symbol (char*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void show_trace_log_lvl(struct task_struct *tsk, unsigned long *sp,
			       struct pt_regs *regs, const char *log_lvl)
{
	unsigned long addr;

	printk("%sCall trace:\n", log_lvl);

	while (!kstack_end(sp)) {
		addr = *sp++;
		if (kernel_text_address(addr)) {
#ifdef CONFIG_KALLSYMS
			printk("%s [<%08lx>] ", log_lvl, addr);
#else
			printk(" [<%08lx>] ", addr);
#endif
			print_symbol("%s\n", addr);
		}
	}
	printk("\n");
}