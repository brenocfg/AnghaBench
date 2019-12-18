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
 int /*<<< orphan*/  IOPIOR ; 
 unsigned char IPR_DTR ; 
 unsigned char IPR_RTS ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char stl_sc26198getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_sc26198setsignals(struct stlport *portp, int dtr, int rts)
{
	unsigned char	iopioron, iopioroff;
	unsigned long	flags;

	pr_debug("stl_sc26198setsignals(portp=%p,dtr=%d,rts=%d)\n", portp,
			dtr, rts);

	iopioron = 0;
	iopioroff = 0;
	if (dtr == 0)
		iopioroff |= IPR_DTR;
	else if (dtr > 0)
		iopioron |= IPR_DTR;
	if (rts == 0)
		iopioroff |= IPR_RTS;
	else if (rts > 0)
		iopioron |= IPR_RTS;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_sc26198setreg(portp, IOPIOR,
		((stl_sc26198getreg(portp, IOPIOR) & ~iopioroff) | iopioron));
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
}