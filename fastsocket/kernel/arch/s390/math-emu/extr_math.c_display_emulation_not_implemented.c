#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mask; scalar_t__ addr; } ;
struct pt_regs {TYPE_1__ psw; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_6__ {scalar_t__ pgm_ilc; } ;
struct TYPE_5__ {unsigned long comm; unsigned long pid; } ;

/* Variables and functions */
 TYPE_3__ S390_lowcore ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  printk (char*,char*,unsigned long,unsigned long) ; 
 scalar_t__ sysctl_ieee_emulation_warnings ; 

__attribute__((used)) static void display_emulation_not_implemented(struct pt_regs *regs, char *instr)
{
        __u16 *location;
        
#ifdef CONFIG_SYSCTL
        if(sysctl_ieee_emulation_warnings)
#endif
        {
                location = (__u16 *)(regs->psw.addr-S390_lowcore.pgm_ilc);
                printk("%s ieee fpu instruction not emulated "
                       "process name: %s pid: %d \n",
                       instr, current->comm, current->pid);
                printk("%s's PSW:    %08lx %08lx\n", instr,
                       (unsigned long) regs->psw.mask,
                       (unsigned long) location);
        }
}