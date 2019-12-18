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
 unsigned char MSVR1_CTS ; 
 unsigned char MSVR1_DCD ; 
 unsigned char MSVR1_DSR ; 
 unsigned char MSVR1_DTR ; 
 unsigned char MSVR1_RI ; 
 int /*<<< orphan*/  MSVR2 ; 
 unsigned char MSVR2_RTS ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_DTR ; 
 int TIOCM_RI ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char stl_cd1400getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_cd1400setreg (struct stlport*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stl_cd1400getsignals(struct stlport *portp)
{
	unsigned char	msvr1, msvr2;
	unsigned long	flags;
	int		sigs;

	pr_debug("stl_cd1400getsignals(portp=%p)\n", portp);

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_cd1400setreg(portp, CAR, (portp->portnr & 0x03));
	msvr1 = stl_cd1400getreg(portp, MSVR1);
	msvr2 = stl_cd1400getreg(portp, MSVR2);
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);

	sigs = 0;
	sigs |= (msvr1 & MSVR1_DCD) ? TIOCM_CD : 0;
	sigs |= (msvr1 & MSVR1_CTS) ? TIOCM_CTS : 0;
	sigs |= (msvr1 & MSVR1_DTR) ? TIOCM_DTR : 0;
	sigs |= (msvr2 & MSVR2_RTS) ? TIOCM_RTS : 0;
#if 0
	sigs |= (msvr1 & MSVR1_RI) ? TIOCM_RI : 0;
	sigs |= (msvr1 & MSVR1_DSR) ? TIOCM_DSR : 0;
#else
	sigs |= TIOCM_DSR;
#endif
	return sigs;
}