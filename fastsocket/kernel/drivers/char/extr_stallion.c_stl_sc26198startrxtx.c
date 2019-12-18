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
struct stlport {unsigned char imr; int /*<<< orphan*/  istate; int /*<<< orphan*/  brdnr; int /*<<< orphan*/  pagenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYI_TXBUSY ; 
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMR ; 
 unsigned char IR_RXBREAK ; 
 unsigned char IR_RXRDY ; 
 unsigned char IR_RXWATCHDOG ; 
 unsigned char IR_TXRDY ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_sc26198startrxtx(struct stlport *portp, int rx, int tx)
{
	unsigned char	imr;
	unsigned long	flags;

	pr_debug("stl_sc26198startrxtx(portp=%p,rx=%d,tx=%d)\n", portp, rx, tx);

	imr = portp->imr;
	if (tx == 0)
		imr &= ~IR_TXRDY;
	else if (tx == 1)
		imr |= IR_TXRDY;
	if (rx == 0)
		imr &= ~(IR_RXRDY | IR_RXBREAK | IR_RXWATCHDOG);
	else if (rx > 0)
		imr |= IR_RXRDY | IR_RXBREAK | IR_RXWATCHDOG;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_sc26198setreg(portp, IMR, imr);
	BRDDISABLE(portp->brdnr);
	portp->imr = imr;
	if (tx > 0)
		set_bit(ASYI_TXBUSY, &portp->istate);
	spin_unlock_irqrestore(&brd_lock, flags);
}