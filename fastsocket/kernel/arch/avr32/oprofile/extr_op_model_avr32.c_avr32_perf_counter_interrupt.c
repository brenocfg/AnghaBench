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
struct avr32_perf_counter {int flag_mask; int count; scalar_t__ enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVR32_PERFCTR_IRQ_GROUP ; 
 int AVR32_PERFCTR_IRQ_LINE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PCCNT ; 
 int /*<<< orphan*/  PCCR ; 
 int /*<<< orphan*/  PCNT0 ; 
 int /*<<< orphan*/  PCNT1 ; 
 struct pt_regs* get_irq_regs () ; 
 int intc_get_pending (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  oprofile_add_sample (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int sysreg_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t avr32_perf_counter_interrupt(int irq, void *dev_id)
{
	struct avr32_perf_counter *ctr = dev_id;
	struct pt_regs *regs;
	u32 pccr;

	if (likely(!(intc_get_pending(AVR32_PERFCTR_IRQ_GROUP)
					& (1 << AVR32_PERFCTR_IRQ_LINE))))
		return IRQ_NONE;

	regs = get_irq_regs();
	pccr = sysreg_read(PCCR);

	/* Clear the interrupt flags we're about to handle */
	sysreg_write(PCCR, pccr);

	/* PCCNT */
	if (ctr->enabled && (pccr & ctr->flag_mask)) {
		sysreg_write(PCCNT, -ctr->count);
		oprofile_add_sample(regs, PCCNT);
	}
	ctr++;
	/* PCNT0 */
	if (ctr->enabled && (pccr & ctr->flag_mask)) {
		sysreg_write(PCNT0, -ctr->count);
		oprofile_add_sample(regs, PCNT0);
	}
	ctr++;
	/* PCNT1 */
	if (ctr->enabled && (pccr & ctr->flag_mask)) {
		sysreg_write(PCNT1, -ctr->count);
		oprofile_add_sample(regs, PCNT1);
	}

	return IRQ_HANDLED;
}