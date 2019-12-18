#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
struct stlport {size_t brdnr; int rxignoremsk; int rxmarkmsk; unsigned int baud_base; unsigned int custom_divisor; unsigned char imr; int /*<<< orphan*/  sigs; int /*<<< orphan*/  pagenr; int /*<<< orphan*/  panelnr; int /*<<< orphan*/  portnr; TYPE_1__ port; } ;
struct stlbrd {int dummy; } ;
struct ktermios {int c_iflag; int c_cflag; unsigned char* c_cc; } ;

/* Variables and functions */
 int ASYNC_CHECK_CD ; 
 int ASYNC_SPD_CUST ; 
 int ASYNC_SPD_HI ; 
 int ASYNC_SPD_MASK ; 
 int ASYNC_SPD_SHI ; 
 int ASYNC_SPD_VHI ; 
 int ASYNC_SPD_WARP ; 
 unsigned int B38400 ; 
 int /*<<< orphan*/  BRDDISABLE (size_t) ; 
 int /*<<< orphan*/  BRDENABLE (size_t,int /*<<< orphan*/ ) ; 
 int BRKINT ; 
 unsigned int CBAUD ; 
 unsigned int CBAUDEX ; 
 int CLOCAL ; 
 int CRTSCTS ; 
 unsigned char CR_RXERRBLOCK ; 
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 int CSIZE ; 
 int CSTOPB ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int /*<<< orphan*/  IMR ; 
 int INPCK ; 
 int /*<<< orphan*/  IOPIOR ; 
 unsigned char IOPR_DCDCOS ; 
 int /*<<< orphan*/  IPR ; 
 unsigned char IPR_CHANGEMASK ; 
 unsigned char IPR_DCD ; 
 unsigned char IR_IOPORT ; 
 unsigned char IR_XONXOFF ; 
 int IXOFF ; 
 int IXON ; 
 int /*<<< orphan*/  MR0 ; 
 unsigned char MR0_SWFRX ; 
 unsigned char MR0_SWFT ; 
 unsigned char MR0_SWFTX ; 
 int /*<<< orphan*/  MR1 ; 
 unsigned char MR1_AUTORTS ; 
 unsigned char MR1_CS5 ; 
 unsigned char MR1_CS6 ; 
 unsigned char MR1_CS7 ; 
 unsigned char MR1_CS8 ; 
 unsigned char MR1_ERRBLOCK ; 
 unsigned char MR1_PARENB ; 
 unsigned char MR1_PAREVEN ; 
 unsigned char MR1_PARNONE ; 
 unsigned char MR1_PARODD ; 
 int /*<<< orphan*/  MR2 ; 
 unsigned char MR2_AUTOCTS ; 
 unsigned char MR2_RXFIFOHALF ; 
 unsigned char MR2_STOP1 ; 
 unsigned char MR2_STOP2 ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  RXCSR ; 
 unsigned char SC26198_NRBAUDS ; 
 int /*<<< orphan*/  SCCR ; 
 int SR_RXBREAK ; 
 int SR_RXFRAMING ; 
 int SR_RXOVERRUN ; 
 int SR_RXPARITY ; 
 unsigned int STL_SC26198MAXBAUD ; 
 int /*<<< orphan*/  TIOCM_CD ; 
 int /*<<< orphan*/  TXCSR ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  XOFFCR ; 
 int /*<<< orphan*/  XONCR ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char,unsigned char,unsigned char,...) ; 
 unsigned int* sc26198_baudtable ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int* stl_baudrates ; 
 struct stlbrd** stl_brds ; 
 unsigned char stl_sc26198getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  stl_sc26198updatereg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_sc26198setport(struct stlport *portp, struct ktermios *tiosp)
{
	struct stlbrd	*brdp;
	unsigned long	flags;
	unsigned int	baudrate;
	unsigned char	mr0, mr1, mr2, clk;
	unsigned char	imron, imroff, iopr, ipr;

	mr0 = 0;
	mr1 = 0;
	mr2 = 0;
	clk = 0;
	iopr = 0;
	imron = 0;
	imroff = 0;

	brdp = stl_brds[portp->brdnr];
	if (brdp == NULL)
		return;

/*
 *	Set up the RX char ignore mask with those RX error types we
 *	can ignore.
 */
	portp->rxignoremsk = 0;
	if (tiosp->c_iflag & IGNPAR)
		portp->rxignoremsk |= (SR_RXPARITY | SR_RXFRAMING |
			SR_RXOVERRUN);
	if (tiosp->c_iflag & IGNBRK)
		portp->rxignoremsk |= SR_RXBREAK;

	portp->rxmarkmsk = SR_RXOVERRUN;
	if (tiosp->c_iflag & (INPCK | PARMRK))
		portp->rxmarkmsk |= (SR_RXPARITY | SR_RXFRAMING);
	if (tiosp->c_iflag & BRKINT)
		portp->rxmarkmsk |= SR_RXBREAK;

/*
 *	Go through the char size, parity and stop bits and set all the
 *	option register appropriately.
 */
	switch (tiosp->c_cflag & CSIZE) {
	case CS5:
		mr1 |= MR1_CS5;
		break;
	case CS6:
		mr1 |= MR1_CS6;
		break;
	case CS7:
		mr1 |= MR1_CS7;
		break;
	default:
		mr1 |= MR1_CS8;
		break;
	}

	if (tiosp->c_cflag & CSTOPB)
		mr2 |= MR2_STOP2;
	else
		mr2 |= MR2_STOP1;

	if (tiosp->c_cflag & PARENB) {
		if (tiosp->c_cflag & PARODD)
			mr1 |= (MR1_PARENB | MR1_PARODD);
		else
			mr1 |= (MR1_PARENB | MR1_PAREVEN);
	} else
		mr1 |= MR1_PARNONE;

	mr1 |= MR1_ERRBLOCK;

/*
 *	Set the RX FIFO threshold at 8 chars. This gives a bit of breathing
 *	space for hardware flow control and the like. This should be set to
 *	VMIN.
 */
	mr2 |= MR2_RXFIFOHALF;

/*
 *	Calculate the baud rate timers. For now we will just assume that
 *	the input and output baud are the same. The sc26198 has a fixed
 *	baud rate table, so only discrete baud rates possible.
 */
	baudrate = tiosp->c_cflag & CBAUD;
	if (baudrate & CBAUDEX) {
		baudrate &= ~CBAUDEX;
		if ((baudrate < 1) || (baudrate > 4))
			tiosp->c_cflag &= ~CBAUDEX;
		else
			baudrate += 15;
	}
	baudrate = stl_baudrates[baudrate];
	if ((tiosp->c_cflag & CBAUD) == B38400) {
		if ((portp->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_HI)
			baudrate = 57600;
		else if ((portp->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_VHI)
			baudrate = 115200;
		else if ((portp->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_SHI)
			baudrate = 230400;
		else if ((portp->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_WARP)
			baudrate = 460800;
		else if ((portp->port.flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST)
			baudrate = (portp->baud_base / portp->custom_divisor);
	}
	if (baudrate > STL_SC26198MAXBAUD)
		baudrate = STL_SC26198MAXBAUD;

	if (baudrate > 0)
		for (clk = 0; clk < SC26198_NRBAUDS; clk++)
			if (baudrate <= sc26198_baudtable[clk])
				break;

/*
 *	Check what form of modem signaling is required and set it up.
 */
	if (tiosp->c_cflag & CLOCAL) {
		portp->port.flags &= ~ASYNC_CHECK_CD;
	} else {
		iopr |= IOPR_DCDCOS;
		imron |= IR_IOPORT;
		portp->port.flags |= ASYNC_CHECK_CD;
	}

/*
 *	Setup sc26198 enhanced modes if we can. In particular we want to
 *	handle as much of the flow control as possible automatically. As
 *	well as saving a few CPU cycles it will also greatly improve flow
 *	control reliability.
 */
	if (tiosp->c_iflag & IXON) {
		mr0 |= MR0_SWFTX | MR0_SWFT;
		imron |= IR_XONXOFF;
	} else
		imroff |= IR_XONXOFF;

	if (tiosp->c_iflag & IXOFF)
		mr0 |= MR0_SWFRX;

	if (tiosp->c_cflag & CRTSCTS) {
		mr2 |= MR2_AUTOCTS;
		mr1 |= MR1_AUTORTS;
	}

/*
 *	All sc26198 register values calculated so go through and set
 *	them all up.
 */

	pr_debug("SETPORT: portnr=%d panelnr=%d brdnr=%d\n",
		portp->portnr, portp->panelnr, portp->brdnr);
	pr_debug("    mr0=%x mr1=%x mr2=%x clk=%x\n", mr0, mr1, mr2, clk);
	pr_debug("    iopr=%x imron=%x imroff=%x\n", iopr, imron, imroff);
	pr_debug("    schr1=%x schr2=%x schr3=%x schr4=%x\n",
		tiosp->c_cc[VSTART], tiosp->c_cc[VSTOP],
		tiosp->c_cc[VSTART], tiosp->c_cc[VSTOP]);

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_sc26198setreg(portp, IMR, 0);
	stl_sc26198updatereg(portp, MR0, mr0);
	stl_sc26198updatereg(portp, MR1, mr1);
	stl_sc26198setreg(portp, SCCR, CR_RXERRBLOCK);
	stl_sc26198updatereg(portp, MR2, mr2);
	stl_sc26198updatereg(portp, IOPIOR,
		((stl_sc26198getreg(portp, IOPIOR) & ~IPR_CHANGEMASK) | iopr));

	if (baudrate > 0) {
		stl_sc26198setreg(portp, TXCSR, clk);
		stl_sc26198setreg(portp, RXCSR, clk);
	}

	stl_sc26198setreg(portp, XONCR, tiosp->c_cc[VSTART]);
	stl_sc26198setreg(portp, XOFFCR, tiosp->c_cc[VSTOP]);

	ipr = stl_sc26198getreg(portp, IPR);
	if (ipr & IPR_DCD)
		portp->sigs &= ~TIOCM_CD;
	else
		portp->sigs |= TIOCM_CD;

	portp->imr = (portp->imr & ~imroff) | imron;
	stl_sc26198setreg(portp, IMR, portp->imr);
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
}