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
typedef  int u32 ;
struct pt_regs {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int CCNT ; 
 unsigned int CNT0 ; 
 unsigned int CNTMAX ; 
 int CPU_COUNTER (int /*<<< orphan*/ ,unsigned int) ; 
 int FLAG_C ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int armv7_pmnc_getreset_flags () ; 
 int /*<<< orphan*/  armv7_pmnc_reset_counter (unsigned int) ; 
 int /*<<< orphan*/  armv7_start_pmnc () ; 
 int /*<<< orphan*/  armv7_stop_pmnc () ; 
 struct pt_regs* get_irq_regs () ; 
 int /*<<< orphan*/  oprofile_add_sample (struct pt_regs*,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static irqreturn_t armv7_pmnc_interrupt(int irq, void *arg)
{
	struct pt_regs *regs = get_irq_regs();
	unsigned int cnt;
	u32 flags;


	/*
	 * Stop IRQ generation
	 */
	armv7_stop_pmnc();

	/*
	 * Get and reset overflow status flags
	 */
	flags = armv7_pmnc_getreset_flags();

	/*
	 * Cycle counter
	 */
	if (flags & FLAG_C) {
		u32 cpu_cnt = CPU_COUNTER(smp_processor_id(), CCNT);
		armv7_pmnc_reset_counter(CCNT);
		oprofile_add_sample(regs, cpu_cnt);
	}

	/*
	 * PMNC counters 0:3
	 */
	for (cnt = CNT0; cnt < CNTMAX; cnt++) {
		if (flags & (1 << (cnt - CNT0))) {
			u32 cpu_cnt = CPU_COUNTER(smp_processor_id(), cnt);
			armv7_pmnc_reset_counter(cnt);
			oprofile_add_sample(regs, cpu_cnt);
		}
	}

	/*
	 * Allow IRQ generation
	 */
	armv7_start_pmnc();

	return IRQ_HANDLED;
}