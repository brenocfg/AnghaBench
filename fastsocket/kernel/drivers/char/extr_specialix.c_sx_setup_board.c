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
 int IRQF_DISABLED ; 
 int IRQF_SHARED ; 
 int SX_BOARD_ACTIVE ; 
 int SX_BOARD_IS_PCI ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct specialix_board*) ; 
 int /*<<< orphan*/  sx_interrupt ; 
 int /*<<< orphan*/  turn_ints_on (struct specialix_board*) ; 

__attribute__((used)) static int sx_setup_board(struct specialix_board *bp)
{
	int error;

	if (bp->flags & SX_BOARD_ACTIVE)
		return 0;

	if (bp->flags & SX_BOARD_IS_PCI)
		error = request_irq(bp->irq, sx_interrupt,
			IRQF_DISABLED | IRQF_SHARED, "specialix IO8+", bp);
	else
		error = request_irq(bp->irq, sx_interrupt,
			IRQF_DISABLED, "specialix IO8+", bp);

	if (error)
		return error;

	turn_ints_on(bp);
	bp->flags |= SX_BOARD_ACTIVE;

	return 0;
}