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
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sx_in (struct specialix_board*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void turn_ints_on(struct specialix_board *bp)
{
	unsigned long flags;

	func_enter();

	spin_lock_irqsave(&bp->lock, flags);
	(void) sx_in(bp, 0); /* Turn ON interrupts. */
	spin_unlock_irqrestore(&bp->lock, flags);

	func_exit();
}