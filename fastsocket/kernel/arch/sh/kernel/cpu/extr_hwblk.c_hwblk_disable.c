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
struct hwblk_info {struct hwblk* hwblks; } ;
struct hwblk {int bit; int /*<<< orphan*/  mstp; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWBLK_CNT_USAGE ; 
 int __hwblk_mod_cnt (struct hwblk_info*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwblk_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hwblk_disable(struct hwblk_info *info, int hwblk)
{
	struct hwblk *hp = info->hwblks + hwblk;
	unsigned long tmp;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&hwblk_lock, flags);

	ret = __hwblk_mod_cnt(info, hwblk, HWBLK_CNT_USAGE, -1, 0);
	if (ret == 0) {
		tmp = __raw_readl(hp->mstp);
		tmp |= 1 << hp->bit;
		__raw_writel(tmp, hp->mstp);
	}

	spin_unlock_irqrestore(&hwblk_lock, flags);
}