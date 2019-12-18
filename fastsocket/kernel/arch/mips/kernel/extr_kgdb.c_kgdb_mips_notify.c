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
struct pt_regs {int cp0_cause; unsigned long cp0_epc; } ;
struct notifier_block {int dummy; } ;
struct die_args {struct pt_regs* regs; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  __flush_cache_all () ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ breakinst ; 
 int /*<<< orphan*/  compute_signal (int) ; 
 int /*<<< orphan*/  kgdb_active ; 
 scalar_t__ kgdb_handle_exception (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  kgdb_nmicallback (int /*<<< orphan*/ ,struct pt_regs*) ; 
 int /*<<< orphan*/  kgdb_setting_breakpoint ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int kgdb_mips_notify(struct notifier_block *self, unsigned long cmd,
			    void *ptr)
{
	struct die_args *args = (struct die_args *)ptr;
	struct pt_regs *regs = args->regs;
	int trap = (regs->cp0_cause & 0x7c) >> 2;

	/* Userpace events, ignore. */
	if (user_mode(regs))
		return NOTIFY_DONE;

	if (atomic_read(&kgdb_active) != -1)
		kgdb_nmicallback(smp_processor_id(), regs);

	if (kgdb_handle_exception(trap, compute_signal(trap), 0, regs))
		return NOTIFY_DONE;

	if (atomic_read(&kgdb_setting_breakpoint))
		if ((trap == 9) && (regs->cp0_epc == (unsigned long)breakinst))
			regs->cp0_epc += 4;

	/* In SMP mode, __flush_cache_all does IPI */
	local_irq_enable();
	__flush_cache_all();

	return NOTIFY_STOP;
}