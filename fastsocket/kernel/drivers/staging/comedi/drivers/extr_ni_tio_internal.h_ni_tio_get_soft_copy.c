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
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline unsigned ni_tio_get_soft_copy(const struct ni_gpct *counter,
					    enum ni_gpct_register
					    register_index)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	unsigned long flags;
	unsigned value;

	BUG_ON(register_index >= NITIO_Num_Registers);
	spin_lock_irqsave(&counter_dev->regs_lock, flags);
	value = counter_dev->regs[register_index];
	spin_unlock_irqrestore(&counter_dev->regs_lock, flags);
	return value;
}