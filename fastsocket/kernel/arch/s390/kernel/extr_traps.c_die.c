#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  trap_no; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_OOPS ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  console_verbose () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  debug_stop_all () ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  lgr_info_log () ; 
 int /*<<< orphan*/  notify_die (int /*<<< orphan*/ ,char const*,struct pt_regs*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oops_enter () ; 
 int /*<<< orphan*/  oops_exit () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_oops ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void die(const char * str, struct pt_regs * regs, long err)
{
	static int die_counter;

	oops_enter();
	lgr_info_log();
	debug_stop_all();
	console_verbose();
	spin_lock_irq(&die_lock);
	bust_spinlocks(1);
	printk("%s: %04lx [#%d] ", str, err & 0xffff, ++die_counter);
#ifdef CONFIG_PREEMPT
	printk("PREEMPT ");
#endif
#ifdef CONFIG_SMP
	printk("SMP ");
#endif
#ifdef CONFIG_DEBUG_PAGEALLOC
	printk("DEBUG_PAGEALLOC");
#endif
	printk("\n");
	notify_die(DIE_OOPS, str, regs, err, current->thread.trap_no, SIGSEGV);
	show_regs(regs);
	bust_spinlocks(0);
	add_taint(TAINT_DIE);
	spin_unlock_irq(&die_lock);
	if (in_interrupt())
		panic("Fatal exception in interrupt");
	if (panic_on_oops)
		panic("Fatal exception: panic_on_oops");
	oops_exit();
	do_exit(SIGSEGV);
}