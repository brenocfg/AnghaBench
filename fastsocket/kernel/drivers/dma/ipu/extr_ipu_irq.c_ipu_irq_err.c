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
typedef  unsigned long u32 ;
struct irq_desc {int dummy; } ;
struct ipu_irq_map {unsigned int irq; } ;
struct ipu_irq_bank {int /*<<< orphan*/  control; int /*<<< orphan*/  status; } ;
struct ipu {int dummy; } ;

/* Variables and functions */
 int IPU_IRQ_NR_BANKS ; 
 int IPU_IRQ_NR_FN_BANKS ; 
 int /*<<< orphan*/  bank_lock ; 
 int ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 struct ipu* get_irq_data (unsigned int) ; 
 unsigned long ipu_read_reg (struct ipu*,int /*<<< orphan*/ ) ; 
 struct ipu_irq_bank* irq_bank ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct ipu_irq_map* src2map (int) ; 

__attribute__((used)) static void ipu_irq_err(unsigned int irq, struct irq_desc *desc)
{
	struct ipu *ipu = get_irq_data(irq);
	u32 status;
	int i, line;

	for (i = IPU_IRQ_NR_FN_BANKS; i < IPU_IRQ_NR_BANKS; i++) {
		struct ipu_irq_bank *bank = irq_bank + i;

		spin_lock(&bank_lock);
		status = ipu_read_reg(ipu, bank->status);
		/*
		 * Don't think we have to clear all interrupts here, they will
		 * be acked by ->handle_irq() (handle_level_irq). However, we
		 * might want to clear unhandled interrupts after the loop...
		 */
		status &= ipu_read_reg(ipu, bank->control);
		spin_unlock(&bank_lock);
		while ((line = ffs(status))) {
			struct ipu_irq_map *map;

			line--;
			status &= ~(1UL << line);

			spin_lock(&bank_lock);
			map = src2map(32 * i + line);
			if (map)
				irq = map->irq;
			spin_unlock(&bank_lock);

			if (!map) {
				pr_err("IPU: Interrupt on unmapped source %u bank %d\n",
				       line, i);
				continue;
			}
			generic_handle_irq(irq);
		}
	}
}