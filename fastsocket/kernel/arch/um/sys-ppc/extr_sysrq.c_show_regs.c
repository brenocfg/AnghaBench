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
struct pt_regs_subarch {int xcs; int xss; int esp; int xds; int xes; int /*<<< orphan*/ * gpr; int /*<<< orphan*/  ebp; int /*<<< orphan*/  edi; int /*<<< orphan*/  esi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; int /*<<< orphan*/  eflags; int /*<<< orphan*/  eip; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_trace (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void show_regs(struct pt_regs_subarch *regs)
{
	printk("\n");
	printk("show_regs(): insert regs here.\n");
#if 0
        printk("\n");
        printk("EIP: %04x:[<%08lx>] CPU: %d",0xffff & regs->xcs, regs->eip,
	       smp_processor_id());
        if (regs->xcs & 3)
                printk(" ESP: %04x:%08lx",0xffff & regs->xss, regs->esp);
        printk(" EFLAGS: %08lx\n", regs->eflags);
        printk("EAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx\n",
                regs->eax, regs->ebx, regs->ecx, regs->edx);
        printk("ESI: %08lx EDI: %08lx EBP: %08lx",
                regs->esi, regs->edi, regs->ebp);
        printk(" DS: %04x ES: %04x\n",
                0xffff & regs->xds, 0xffff & regs->xes);
#endif

        show_trace(current, &regs->gpr[1]);
}