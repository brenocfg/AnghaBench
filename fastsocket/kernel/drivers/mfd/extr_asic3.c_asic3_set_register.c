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
typedef  int /*<<< orphan*/  u32 ;
struct asic3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  asic3_read_register (struct asic3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asic3_write_register (struct asic3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void asic3_set_register(struct asic3 *asic, u32 reg, u32 bits, bool set)
{
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&asic->lock, flags);
	val = asic3_read_register(asic, reg);
	if (set)
		val |= bits;
	else
		val &= ~bits;
	asic3_write_register(asic, reg, val);
	spin_unlock_irqrestore(&asic->lock, flags);
}