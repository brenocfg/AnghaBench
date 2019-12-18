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
struct stlport {int /*<<< orphan*/  brdnr; int /*<<< orphan*/  pagenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPR ; 
 unsigned char IPR_CTS ; 
 unsigned char IPR_DCD ; 
 unsigned char IPR_DTR ; 
 unsigned char IPR_RTS ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char stl_sc26198getreg (struct stlport*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stl_sc26198getsignals(struct stlport *portp)
{
	unsigned char	ipr;
	unsigned long	flags;
	int		sigs;

	pr_debug("stl_sc26198getsignals(portp=%p)\n", portp);

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	ipr = stl_sc26198getreg(portp, IPR);
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);

	sigs = 0;
	sigs |= (ipr & IPR_DCD) ? 0 : TIOCM_CD;
	sigs |= (ipr & IPR_CTS) ? 0 : TIOCM_CTS;
	sigs |= (ipr & IPR_DTR) ? 0: TIOCM_DTR;
	sigs |= (ipr & IPR_RTS) ? 0: TIOCM_RTS;
	sigs |= TIOCM_DSR;
	return sigs;
}