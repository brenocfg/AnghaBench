#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int mask; } ;
struct pt_regs {scalar_t__* gprs; TYPE_2__ psw; } ;
struct TYPE_12__ {int /*<<< orphan*/  version; int /*<<< orphan*/  release; } ;
struct TYPE_8__ {scalar_t__ ksp; } ;
struct TYPE_11__ {TYPE_1__ thread; int /*<<< orphan*/  pid; int /*<<< orphan*/  comm; } ;
struct TYPE_10__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int PSW_MASK_PSTATE ; 
 TYPE_4__* current ; 
 TYPE_6__* init_utsname () ; 
 int /*<<< orphan*/  print_modules () ; 
 int /*<<< orphan*/  print_tainted () ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*,void*,...) ; 
 int /*<<< orphan*/  show_last_breaking_event (struct pt_regs*) ; 
 int /*<<< orphan*/  show_registers (struct pt_regs*) ; 
 int /*<<< orphan*/  show_trace (int /*<<< orphan*/ *,unsigned long*) ; 
 scalar_t__ strcspn (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* task_thread_info (TYPE_4__*) ; 

void show_regs(struct pt_regs *regs)
{
	print_modules();
	printk("CPU: %d %s %s %.*s\n",
	       task_thread_info(current)->cpu, print_tainted(),
	       init_utsname()->release,
	       (int)strcspn(init_utsname()->version, " "),
	       init_utsname()->version);
	printk("Process %s (pid: %d, task: %p, ksp: %p)\n",
	       current->comm, current->pid, current,
	       (void *) current->thread.ksp);
	show_registers(regs);
	/* Show stack backtrace if pt_regs is from kernel mode */
	if (!(regs->psw.mask & PSW_MASK_PSTATE))
		show_trace(NULL, (unsigned long *) regs->gprs[15]);
	show_last_breaking_event(regs);
}