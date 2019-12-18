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
struct hwblk_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __hwblk_mod_cnt (struct hwblk_info*,int,int,int,int) ; 
 int /*<<< orphan*/  hwblk_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hwblk_mod_cnt(struct hwblk_info *info, int hwblk,
			  int counter, int value, int goal)
{
	unsigned long flags;

	spin_lock_irqsave(&hwblk_lock, flags);
	__hwblk_mod_cnt(info, hwblk, counter, value, goal);
	spin_unlock_irqrestore(&hwblk_lock, flags);
}