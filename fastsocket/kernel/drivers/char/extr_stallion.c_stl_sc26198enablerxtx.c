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
struct stlport {unsigned char crenable; int /*<<< orphan*/  brdnr; int /*<<< orphan*/  pagenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char CR_RXENABLE ; 
 unsigned char CR_TXENABLE ; 
 int /*<<< orphan*/  SCCR ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_sc26198enablerxtx(struct stlport *portp, int rx, int tx)
{
	unsigned char	ccr;
	unsigned long	flags;

	pr_debug("stl_sc26198enablerxtx(portp=%p,rx=%d,tx=%d)\n", portp, rx,tx);

	ccr = portp->crenable;
	if (tx == 0)
		ccr &= ~CR_TXENABLE;
	else if (tx > 0)
		ccr |= CR_TXENABLE;
	if (rx == 0)
		ccr &= ~CR_RXENABLE;
	else if (rx > 0)
		ccr |= CR_RXENABLE;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_sc26198setreg(portp, SCCR, ccr);
	BRDDISABLE(portp->brdnr);
	portp->crenable = ccr;
	spin_unlock_irqrestore(&brd_lock, flags);
}