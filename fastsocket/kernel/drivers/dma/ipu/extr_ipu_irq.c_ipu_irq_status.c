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
struct ipu_irq_map {int source; struct ipu_irq_bank* bank; } ;
struct ipu_irq_bank {int /*<<< orphan*/  status; int /*<<< orphan*/  ipu; } ;

/* Variables and functions */
 int /*<<< orphan*/  bank_lock ; 
 struct ipu_irq_map* get_irq_chip_data (unsigned int) ; 
 unsigned long ipu_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool ipu_irq_status(unsigned int irq)
{
	struct ipu_irq_map *map = get_irq_chip_data(irq);
	struct ipu_irq_bank *bank;
	unsigned long lock_flags;
	bool ret;

	spin_lock_irqsave(&bank_lock, lock_flags);
	bank = map->bank;
	ret = bank && ipu_read_reg(bank->ipu, bank->status) &
		(1UL << (map->source & 31));
	spin_unlock_irqrestore(&bank_lock, lock_flags);

	return ret;
}