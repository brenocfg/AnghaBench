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
struct stlport {int portnr; int /*<<< orphan*/  brdnr; int /*<<< orphan*/  pagenr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAR ; 
 int /*<<< orphan*/  MSVR1 ; 
 unsigned char MSVR1_DTR ; 
 int /*<<< orphan*/  MSVR2 ; 
 unsigned char MSVR2_RTS ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stl_cd1400setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_cd1400setsignals(struct stlport *portp, int dtr, int rts)
{
	unsigned char	msvr1, msvr2;
	unsigned long	flags;

	pr_debug("stl_cd1400setsignals(portp=%p,dtr=%d,rts=%d)\n",
			portp, dtr, rts);

	msvr1 = 0;
	msvr2 = 0;
	if (dtr > 0)
		msvr1 = MSVR1_DTR;
	if (rts > 0)
		msvr2 = MSVR2_RTS;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_cd1400setreg(portp, CAR, (portp->portnr & 0x03));
	if (rts >= 0)
		stl_cd1400setreg(portp, MSVR2, msvr2);
	if (dtr >= 0)
		stl_cd1400setreg(portp, MSVR1, msvr1);
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
}