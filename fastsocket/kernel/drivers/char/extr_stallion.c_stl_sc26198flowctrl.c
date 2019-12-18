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
struct stlport {int /*<<< orphan*/  brdnr; TYPE_2__ stats; int /*<<< orphan*/  pagenr; int /*<<< orphan*/  port; } ;
struct TYPE_3__ {int c_iflag; int c_cflag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRDDISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRDENABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CRTSCTS ; 
 unsigned char CR_TXSENDXOFF ; 
 unsigned char CR_TXSENDXON ; 
 int /*<<< orphan*/  IOPIOR ; 
 unsigned char IOPR_RTS ; 
 int IXOFF ; 
 int /*<<< orphan*/  MR0 ; 
 unsigned char MR0_SWFRX ; 
 unsigned char MR0_SWFRXTX ; 
 int /*<<< orphan*/  MR1 ; 
 unsigned char MR1_AUTORTS ; 
 int /*<<< orphan*/  SCCR ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char stl_sc26198getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  stl_sc26198wait (struct stlport*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stl_sc26198flowctrl(struct stlport *portp, int state)
{
	struct tty_struct	*tty;
	unsigned long		flags;
	unsigned char		mr0;

	pr_debug("stl_sc26198flowctrl(portp=%p,state=%x)\n", portp, state);

	if (portp == NULL)
		return;
	tty = tty_port_tty_get(&portp->port);
	if (tty == NULL)
		return;

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);

	if (state) {
		if (tty->termios->c_iflag & IXOFF) {
			mr0 = stl_sc26198getreg(portp, MR0);
			stl_sc26198setreg(portp, MR0, (mr0 & ~MR0_SWFRXTX));
			stl_sc26198setreg(portp, SCCR, CR_TXSENDXON);
			mr0 |= MR0_SWFRX;
			portp->stats.rxxon++;
			stl_sc26198wait(portp);
			stl_sc26198setreg(portp, MR0, mr0);
		}
/*
 *		Question: should we return RTS to what it was before? It may
 *		have been set by an ioctl... Suppose not, since if you have
 *		hardware flow control set then it is pretty silly to go and
 *		set the RTS line by hand.
 */
		if (tty->termios->c_cflag & CRTSCTS) {
			stl_sc26198setreg(portp, MR1,
				(stl_sc26198getreg(portp, MR1) | MR1_AUTORTS));
			stl_sc26198setreg(portp, IOPIOR,
				(stl_sc26198getreg(portp, IOPIOR) | IOPR_RTS));
			portp->stats.rxrtson++;
		}
	} else {
		if (tty->termios->c_iflag & IXOFF) {
			mr0 = stl_sc26198getreg(portp, MR0);
			stl_sc26198setreg(portp, MR0, (mr0 & ~MR0_SWFRXTX));
			stl_sc26198setreg(portp, SCCR, CR_TXSENDXOFF);
			mr0 &= ~MR0_SWFRX;
			portp->stats.rxxoff++;
			stl_sc26198wait(portp);
			stl_sc26198setreg(portp, MR0, mr0);
		}
		if (tty->termios->c_cflag & CRTSCTS) {
			stl_sc26198setreg(portp, MR1,
				(stl_sc26198getreg(portp, MR1) & ~MR1_AUTORTS));
			stl_sc26198setreg(portp, IOPIOR,
				(stl_sc26198getreg(portp, IOPIOR) & ~IOPR_RTS));
			portp->stats.rxrtsoff++;
		}
	}

	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
	tty_kref_put(tty);
}