#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long spu; scalar_t__ bpc; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 scalar_t__ PAGE_OFFSET ; 
 scalar_t__ __get_user (unsigned char,unsigned char*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  show_stack (TYPE_1__*,unsigned long*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  task_pid_nr (TYPE_1__*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static void show_registers(struct pt_regs *regs)
{
	int i = 0;
	int in_kernel = 1;
	unsigned long sp;

	printk("CPU:    %d\n", smp_processor_id());
	show_regs(regs);

	sp = (unsigned long) (1+regs);
	if (user_mode(regs)) {
		in_kernel = 0;
		sp = regs->spu;
		printk("SPU: %08lx\n", sp);
	} else {
		printk("SPI: %08lx\n", sp);
	}
	printk("Process %s (pid: %d, process nr: %d, stackpage=%08lx)",
		current->comm, task_pid_nr(current), 0xffff & i, 4096+(unsigned long)current);

	/*
	 * When in-kernel, we also print out the stack and code at the
	 * time of the fault..
	 */
	if (in_kernel) {
		printk("\nStack: ");
		show_stack(current, (unsigned long*) sp);

		printk("\nCode: ");
		if (regs->bpc < PAGE_OFFSET)
			goto bad;

		for(i=0;i<20;i++) {
			unsigned char c;
			if (__get_user(c, &((unsigned char*)regs->bpc)[i])) {
bad:
				printk(" Bad PC value.");
				break;
			}
			printk("%02x ", c);
		}
	}
	printk("\n");
}