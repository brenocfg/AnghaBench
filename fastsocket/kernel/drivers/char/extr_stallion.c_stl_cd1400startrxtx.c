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
struct stlport {int portnr; int /*<<< orphan*/  istate; int /*<<< orphan*/  brdnr; int /*<<< orphan*/  pagenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYI_TXBUSY ; 
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAR ; 
 int /*<<< orphan*/  SRER ; 
 unsigned char SRER_RXDATA ; 
 unsigned char SRER_TXDATA ; 
 unsigned char SRER_TXEMPTY ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char stl_cd1400getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_cd1400setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_cd1400startrxtx(struct stlport *portp, int rx, int tx)
{
	unsigned char	sreron, sreroff;
	unsigned long	flags;

	pr_debug("stl_cd1400startrxtx(portp=%p,rx=%d,tx=%d)\n", portp, rx, tx);

	sreron = 0;
	sreroff = 0;
	if (tx == 0)
		sreroff |= (SRER_TXDATA | SRER_TXEMPTY);
	else if (tx == 1)
		sreron |= SRER_TXDATA;
	else if (tx >= 2)
		sreron |= SRER_TXEMPTY;
	if (rx == 0)
		sreroff |= SRER_RXDATA;
	else if (rx > 0)
		sreron |= SRER_RXDATA;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_cd1400setreg(portp, CAR, (portp->portnr & 0x03));
	stl_cd1400setreg(portp, SRER,
		((stl_cd1400getreg(portp, SRER) & ~sreroff) | sreron));
	BRDDISABLE(portp->brdnr);
	if (tx > 0)
		set_bit(ASYI_TXBUSY, &portp->istate);
	spin_unlock_irqrestore(&brd_lock, flags);
}