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
struct specialix_board {int flags; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int SX_BOARD_ACTIVE ; 
 int /*<<< orphan*/  SX_DEBUG_IRQ ; 
 int /*<<< orphan*/  board_No (struct specialix_board*) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct specialix_board*) ; 
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 int /*<<< orphan*/  turn_ints_off (struct specialix_board*) ; 

__attribute__((used)) static void sx_shutdown_board(struct specialix_board *bp)
{
	func_enter();

	if (!(bp->flags & SX_BOARD_ACTIVE)) {
		func_exit();
		return;
	}

	bp->flags &= ~SX_BOARD_ACTIVE;

	dprintk(SX_DEBUG_IRQ, "Freeing IRQ%d for board %d.\n",
		 bp->irq, board_No(bp));
	free_irq(bp->irq, bp);
	turn_ints_off(bp);
	func_exit();
}