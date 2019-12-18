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
typedef  unsigned int u32 ;
struct radeonfb_info {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 unsigned int INREG (unsigned int) ; 
 int /*<<< orphan*/  OUTREG (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void _OUTREGP(struct radeonfb_info *rinfo, u32 addr,
		       u32 val, u32 mask)
{
	unsigned long flags;
	unsigned int tmp;

	spin_lock_irqsave(&rinfo->reg_lock, flags);
	tmp = INREG(addr);
	tmp &= (mask);
	tmp |= (val);
	OUTREG(addr, tmp);
	spin_unlock_irqrestore(&rinfo->reg_lock, flags);
}