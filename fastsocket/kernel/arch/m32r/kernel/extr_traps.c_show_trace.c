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

/* Variables and functions */
 scalar_t__ __kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  kstack_end (unsigned long*) ; 
 int /*<<< orphan*/  print_symbol (char*,unsigned long) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void show_trace(struct task_struct *task, unsigned long *stack)
{
	unsigned long addr;

	if (!stack)
		stack = (unsigned long*)&stack;

	printk("Call Trace: ");
	while (!kstack_end(stack)) {
		addr = *stack++;
		if (__kernel_text_address(addr)) {
			printk("[<%08lx>] ", addr);
			print_symbol("%s\n", addr);
		}
	}
	printk("\n");
}