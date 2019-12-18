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
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  console_verbose () ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_registers (struct pt_regs*) ; 

void __die(const char *str, struct pt_regs *regs, const char *file,
	const char *func, unsigned long line)
{
	console_verbose();
	printk("%s", str);
	if (file && func)
		printk(" in %s:%s, line %ld", file, func, line);
	printk(":\n");
	show_registers(regs);
	do_exit(SIGSEGV);
}