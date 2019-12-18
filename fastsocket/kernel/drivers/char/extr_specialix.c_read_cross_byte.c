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
struct specialix_board {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD186x_CAR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sx_in_off (struct specialix_board*,int) ; 
 int /*<<< orphan*/  sx_out_off (struct specialix_board*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int read_cross_byte(struct specialix_board *bp, int reg, int bit)
{
	int i;
	int t;
	unsigned long flags;

	spin_lock_irqsave(&bp->lock, flags);
	for (i = 0, t = 0; i < 8; i++) {
		sx_out_off(bp, CD186x_CAR, i);
		if (sx_in_off(bp, reg) & bit)
			t |= 1 << i;
	}
	spin_unlock_irqrestore(&bp->lock, flags);

	return t;
}