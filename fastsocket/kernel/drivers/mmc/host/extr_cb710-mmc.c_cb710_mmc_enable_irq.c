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
struct cb710_slot {int dummy; } ;
struct cb710_mmc_reader {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cb710_mmc_enable_irq (struct cb710_slot*,unsigned short,unsigned short) ; 
 int /*<<< orphan*/  cb710_slot_to_mmc (struct cb710_slot*) ; 
 struct cb710_mmc_reader* mmc_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cb710_mmc_enable_irq(struct cb710_slot *slot,
	unsigned short enable, unsigned short mask)
{
	struct cb710_mmc_reader *reader = mmc_priv(cb710_slot_to_mmc(slot));
	unsigned long flags;

	spin_lock_irqsave(&reader->irq_lock, flags);
	/* this is the only thing irq_lock protects */
	__cb710_mmc_enable_irq(slot, enable, mask);
	spin_unlock_irqrestore(&reader->irq_lock, flags);
}