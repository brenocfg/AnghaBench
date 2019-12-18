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
 int PT_REGS_CS (struct pt_regs*) ; 
 int PT_REGS_DS (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_EAX (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_EBP (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_EBX (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_ECX (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_EDI (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_EDX (struct pt_regs*) ; 
 int PT_REGS_EFLAGS (struct pt_regs*) ; 
 int PT_REGS_ES (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_ESI (struct pt_regs*) ; 
 int /*<<< orphan*/  PT_REGS_IP (struct pt_regs*) ; 
 int PT_REGS_SP (struct pt_regs*) ; 
 int PT_REGS_SS (struct pt_regs*) ; 
 int print_tainted () ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_trace (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void show_regs(struct pt_regs *regs)
{
        printk("\n");
        printk("EIP: %04lx:[<%08lx>] CPU: %d %s", 
	       0xffff & PT_REGS_CS(regs), PT_REGS_IP(regs),
	       smp_processor_id(), print_tainted());
        if (PT_REGS_CS(regs) & 3)
                printk(" ESP: %04lx:%08lx", 0xffff & PT_REGS_SS(regs),
		       PT_REGS_SP(regs));
        printk(" EFLAGS: %08lx\n    %s\n", PT_REGS_EFLAGS(regs),
	       print_tainted());
        printk("EAX: %08lx EBX: %08lx ECX: %08lx EDX: %08lx\n",
                PT_REGS_EAX(regs), PT_REGS_EBX(regs), 
	       PT_REGS_ECX(regs), 
	       PT_REGS_EDX(regs));
        printk("ESI: %08lx EDI: %08lx EBP: %08lx",
	       PT_REGS_ESI(regs), PT_REGS_EDI(regs), 
	       PT_REGS_EBP(regs));
        printk(" DS: %04lx ES: %04lx\n",
	       0xffff & PT_REGS_DS(regs), 
	       0xffff & PT_REGS_ES(regs));

        show_trace(NULL, (unsigned long *) &regs);
}