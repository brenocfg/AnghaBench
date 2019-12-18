#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int /*<<< orphan*/ * regs; } ;
struct TYPE_5__ {char const* comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_OOPS ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  TAINT_DIE ; 
 scalar_t__ THREAD_SIZE ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bust_spinlocks (int) ; 
 int /*<<< orphan*/  console_verbose () ; 
 int /*<<< orphan*/  crash_kexec (struct pt_regs*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  die_lock ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_mem (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ kexec_should_crash (TYPE_1__*) ; 
 int /*<<< orphan*/  notify_die (int /*<<< orphan*/ ,char const*,struct pt_regs*,long,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oops_enter () ; 
 int /*<<< orphan*/  oops_exit () ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ panic_on_oops ; 
 int /*<<< orphan*/  print_modules () ; 
 int /*<<< orphan*/  printk (char*,char const*,long,int) ; 
 int /*<<< orphan*/  show_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_printk_last_file () ; 
 long task_pid_nr (TYPE_1__*) ; 
 int task_stack_page (TYPE_1__*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void die(const char * str, struct pt_regs * regs, long err)
{
	static int die_counter;

	oops_enter();

	spin_lock_irq(&die_lock);
	console_verbose();
	bust_spinlocks(1);

	printk("%s: %04lx [#%d]\n", str, err & 0xffff, ++die_counter);
	sysfs_printk_last_file();
	print_modules();
	show_regs(regs);

	printk("Process: %s (pid: %d, stack limit = %p)\n", current->comm,
			task_pid_nr(current), task_stack_page(current) + 1);

	if (!user_mode(regs) || in_interrupt())
		dump_mem("Stack: ", regs->regs[15], THREAD_SIZE +
			 (unsigned long)task_stack_page(current));

	notify_die(DIE_OOPS, str, regs, err, 255, SIGSEGV);

	bust_spinlocks(0);
	add_taint(TAINT_DIE);
	spin_unlock_irq(&die_lock);
	oops_exit();

	if (kexec_should_crash(current))
		crash_kexec(regs);

	if (in_interrupt())
		panic("Fatal exception in interrupt");

	if (panic_on_oops)
		panic("Fatal exception");

	do_exit(SIGSEGV);
}