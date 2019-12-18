#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {struct ktermios* termios; } ;
struct TYPE_27__ {TYPE_1__* CtlP; } ;
struct r_port {size_t board; int cps; int cd_status; int read_status_mask; int ignore_status_mask; unsigned int flags; TYPE_2__ channel; int /*<<< orphan*/  slock; int /*<<< orphan*/  intmask; } ;
struct ktermios {unsigned int c_cflag; } ;
struct TYPE_26__ {scalar_t__ boardType; } ;
typedef  TYPE_2__ CHANNEL_t ;

/* Variables and functions */
 int CD_ACT ; 
 unsigned int CLOCAL ; 
 unsigned int CRTSCTS ; 
 unsigned int CS8 ; 
 unsigned int CSIZE ; 
 unsigned int CSTOPB ; 
 int /*<<< orphan*/  DELTA_CD ; 
 int /*<<< orphan*/  DELTA_CTS ; 
 scalar_t__ I_BRKINT (struct tty_struct*) ; 
 scalar_t__ I_IGNBRK (struct tty_struct*) ; 
 scalar_t__ I_IGNPAR (struct tty_struct*) ; 
 scalar_t__ I_INPCK (struct tty_struct*) ; 
 scalar_t__ I_IXANY (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 int /*<<< orphan*/  InterfaceModeRS232 ; 
 int /*<<< orphan*/  InterfaceModeRS232T ; 
 int /*<<< orphan*/  InterfaceModeRS422 ; 
 int /*<<< orphan*/  InterfaceModeRS485 ; 
 unsigned int PARENB ; 
 unsigned int PARODD ; 
 unsigned int ROCKET_MODE_MASK ; 
#define  ROCKET_MODE_RS232 130 
#define  ROCKET_MODE_RS422 129 
#define  ROCKET_MODE_RS485 128 
 int ROCKET_RTS_TOGGLE ; 
 scalar_t__ ROCKET_TYPE_PC104 ; 
 int /*<<< orphan*/  START_CHAR (struct tty_struct*) ; 
 int STMBREAKH ; 
 int STMFRAMEH ; 
 int STMPARITYH ; 
 int STMRCVROVRH ; 
 int /*<<< orphan*/  STOP_CHAR (struct tty_struct*) ; 
 int* rp_baud_base ; 
 int /*<<< orphan*/  sClrTxXOFF (TYPE_2__*) ; 
 int /*<<< orphan*/  sDisCTSFlowCtl (TYPE_2__*) ; 
 int /*<<< orphan*/  sDisIXANY (TYPE_2__*) ; 
 int /*<<< orphan*/  sDisParity (TYPE_2__*) ; 
 int /*<<< orphan*/  sDisRTSToggle (TYPE_2__*) ; 
 int /*<<< orphan*/  sDisTxSoftFlowCtl (TYPE_2__*) ; 
 int /*<<< orphan*/  sEnCTSFlowCtl (TYPE_2__*) ; 
 int /*<<< orphan*/  sEnIXANY (TYPE_2__*) ; 
 int /*<<< orphan*/  sEnParity (TYPE_2__*) ; 
 int /*<<< orphan*/  sEnRTSToggle (TYPE_2__*) ; 
 int /*<<< orphan*/  sEnTxSoftFlowCtl (TYPE_2__*) ; 
 int sGetChanStatus (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetBaud (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sSetData7 (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetData8 (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetEvenParity (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetInterfaceMode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sSetOddParity (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetRTS (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetStop1 (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetStop2 (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetTxXOFFChar (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sSetTxXONChar (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,int,int) ; 
 int tty_get_baud_rate (struct tty_struct*) ; 
 int tty_termios_baud_rate (struct ktermios*) ; 

__attribute__((used)) static void configure_r_port(struct tty_struct *tty, struct r_port *info,
			     struct ktermios *old_termios)
{
	unsigned cflag;
	unsigned long flags;
	unsigned rocketMode;
	int bits, baud, divisor;
	CHANNEL_t *cp;
	struct ktermios *t = tty->termios;

	cp = &info->channel;
	cflag = t->c_cflag;

	/* Byte size and parity */
	if ((cflag & CSIZE) == CS8) {
		sSetData8(cp);
		bits = 10;
	} else {
		sSetData7(cp);
		bits = 9;
	}
	if (cflag & CSTOPB) {
		sSetStop2(cp);
		bits++;
	} else {
		sSetStop1(cp);
	}

	if (cflag & PARENB) {
		sEnParity(cp);
		bits++;
		if (cflag & PARODD) {
			sSetOddParity(cp);
		} else {
			sSetEvenParity(cp);
		}
	} else {
		sDisParity(cp);
	}

	/* baud rate */
	baud = tty_get_baud_rate(tty);
	if (!baud)
		baud = 9600;
	divisor = ((rp_baud_base[info->board] + (baud >> 1)) / baud) - 1;
	if ((divisor >= 8192 || divisor < 0) && old_termios) {
		baud = tty_termios_baud_rate(old_termios);
		if (!baud)
			baud = 9600;
		divisor = (rp_baud_base[info->board] / baud) - 1;
	}
	if (divisor >= 8192 || divisor < 0) {
		baud = 9600;
		divisor = (rp_baud_base[info->board] / baud) - 1;
	}
	info->cps = baud / bits;
	sSetBaud(cp, divisor);

	/* FIXME: Should really back compute a baud rate from the divisor */
	tty_encode_baud_rate(tty, baud, baud);

	if (cflag & CRTSCTS) {
		info->intmask |= DELTA_CTS;
		sEnCTSFlowCtl(cp);
	} else {
		info->intmask &= ~DELTA_CTS;
		sDisCTSFlowCtl(cp);
	}
	if (cflag & CLOCAL) {
		info->intmask &= ~DELTA_CD;
	} else {
		spin_lock_irqsave(&info->slock, flags);
		if (sGetChanStatus(cp) & CD_ACT)
			info->cd_status = 1;
		else
			info->cd_status = 0;
		info->intmask |= DELTA_CD;
		spin_unlock_irqrestore(&info->slock, flags);
	}

	/*
	 * Handle software flow control in the board
	 */
#ifdef ROCKET_SOFT_FLOW
	if (I_IXON(tty)) {
		sEnTxSoftFlowCtl(cp);
		if (I_IXANY(tty)) {
			sEnIXANY(cp);
		} else {
			sDisIXANY(cp);
		}
		sSetTxXONChar(cp, START_CHAR(tty));
		sSetTxXOFFChar(cp, STOP_CHAR(tty));
	} else {
		sDisTxSoftFlowCtl(cp);
		sDisIXANY(cp);
		sClrTxXOFF(cp);
	}
#endif

	/*
	 * Set up ignore/read mask words
	 */
	info->read_status_mask = STMRCVROVRH | 0xFF;
	if (I_INPCK(tty))
		info->read_status_mask |= STMFRAMEH | STMPARITYH;
	if (I_BRKINT(tty) || I_PARMRK(tty))
		info->read_status_mask |= STMBREAKH;

	/*
	 * Characters to ignore
	 */
	info->ignore_status_mask = 0;
	if (I_IGNPAR(tty))
		info->ignore_status_mask |= STMFRAMEH | STMPARITYH;
	if (I_IGNBRK(tty)) {
		info->ignore_status_mask |= STMBREAKH;
		/*
		 * If we're ignoring parity and break indicators,
		 * ignore overruns too.  (For real raw support).
		 */
		if (I_IGNPAR(tty))
			info->ignore_status_mask |= STMRCVROVRH;
	}

	rocketMode = info->flags & ROCKET_MODE_MASK;

	if ((info->flags & ROCKET_RTS_TOGGLE)
	    || (rocketMode == ROCKET_MODE_RS485))
		sEnRTSToggle(cp);
	else
		sDisRTSToggle(cp);

	sSetRTS(&info->channel);

	if (cp->CtlP->boardType == ROCKET_TYPE_PC104) {
		switch (rocketMode) {
		case ROCKET_MODE_RS485:
			sSetInterfaceMode(cp, InterfaceModeRS485);
			break;
		case ROCKET_MODE_RS422:
			sSetInterfaceMode(cp, InterfaceModeRS422);
			break;
		case ROCKET_MODE_RS232:
		default:
			if (info->flags & ROCKET_RTS_TOGGLE)
				sSetInterfaceMode(cp, InterfaceModeRS232T);
			else
				sSetInterfaceMode(cp, InterfaceModeRS232);
			break;
		}
	}
}