#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_1__* termios; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxrtsoff; int /*<<< orphan*/  rxxoff; int /*<<< orphan*/  rxrtson; int /*<<< orphan*/  rxxon; } ;
struct stlport {int portnr; int /*<<< orphan*/  brdnr; TYPE_2__ stats; int /*<<< orphan*/  pagenr; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int c_iflag; int c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAR ; 
 int /*<<< orphan*/  CCR ; 
 int CCR_SENDSCHR1 ; 
 int CCR_SENDSCHR2 ; 
 int CRTSCTS ; 
 int FIFO_RTSTHRESHOLD ; 
 int IXOFF ; 
 int /*<<< orphan*/  MCOR1 ; 
 int /*<<< orphan*/  MSVR2 ; 
 int MSVR2_RTS ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stl_cd1400ccrwait (struct stlport*) ; 
 int stl_cd1400getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_cd1400setreg (struct stlport*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stl_cd1400flowctrl(struct stlport *portp, int state)
{
	struct tty_struct	*tty;
	unsigned long		flags;

	pr_debug("stl_cd1400flowctrl(portp=%p,state=%x)\n", portp, state);

	if (portp == NULL)
		return;
	tty = tty_port_tty_get(&portp->port);
	if (tty == NULL)
		return;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_cd1400setreg(portp, CAR, (portp->portnr & 0x03));

	if (state) {
		if (tty->termios->c_iflag & IXOFF) {
			stl_cd1400ccrwait(portp);
			stl_cd1400setreg(portp, CCR, CCR_SENDSCHR1);
			portp->stats.rxxon++;
			stl_cd1400ccrwait(portp);
		}
/*
 *		Question: should we return RTS to what it was before? It may
 *		have been set by an ioctl... Suppose not, since if you have
 *		hardware flow control set then it is pretty silly to go and
 *		set the RTS line by hand.
 */
		if (tty->termios->c_cflag & CRTSCTS) {
			stl_cd1400setreg(portp, MCOR1,
				(stl_cd1400getreg(portp, MCOR1) |
				FIFO_RTSTHRESHOLD));
			stl_cd1400setreg(portp, MSVR2, MSVR2_RTS);
			portp->stats.rxrtson++;
		}
	} else {
		if (tty->termios->c_iflag & IXOFF) {
			stl_cd1400ccrwait(portp);
			stl_cd1400setreg(portp, CCR, CCR_SENDSCHR2);
			portp->stats.rxxoff++;
			stl_cd1400ccrwait(portp);
		}
		if (tty->termios->c_cflag & CRTSCTS) {
			stl_cd1400setreg(portp, MCOR1,
				(stl_cd1400getreg(portp, MCOR1) & 0xf0));
			stl_cd1400setreg(portp, MSVR2, 0);
			portp->stats.rxrtsoff++;
		}
	}

	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
	tty_kref_put(tty);
}