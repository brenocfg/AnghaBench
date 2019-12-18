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
struct ni_gpct_device {unsigned int* regs; int /*<<< orphan*/  regs_lock; } ;
struct ni_gpct {struct ni_gpct_device* counter_dev; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int NITIO_Num_Registers ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,unsigned int,int) ; 

__attribute__((used)) static inline void ni_tio_set_bits_transient(struct ni_gpct *counter,
					     enum ni_gpct_register
					     register_index, unsigned bit_mask,
					     unsigned bit_values,
					     unsigned transient_bit_values)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned long flags;

	BUG_ON(register_index >= NITIO_Num_Registers);
	spin_lock_irqsave(&counter_dev->regs_lock, flags);
	counter_dev->regs[register_index] &= ~bit_mask;
	counter_dev->regs[register_index] |= (bit_values & bit_mask);
	write_register(counter,
		       counter_dev->regs[register_index] | transient_bit_values,
		       register_index);
	mmiowb();
	spin_unlock_irqrestore(&counter_dev->regs_lock, flags);
}