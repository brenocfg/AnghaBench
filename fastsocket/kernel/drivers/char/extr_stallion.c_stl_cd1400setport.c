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
struct stlport {size_t brdnr; int rxignoremsk; int rxmarkmsk; unsigned int baud_base; unsigned int custom_divisor; unsigned int clk; int portnr; int /*<<< orphan*/  sigs; int /*<<< orphan*/  pagenr; int /*<<< orphan*/  panelnr; TYPE_1__ port; } ;
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
 int /*<<< orphan*/  CAR ; 
 unsigned int CBAUD ; 
 unsigned int CBAUDEX ; 
 int /*<<< orphan*/  CCR ; 
 unsigned char CCR_CORCHANGE ; 
 unsigned char CD1400_NUMCLKS ; 
 int CLOCAL ; 
 int /*<<< orphan*/  COR1 ; 
 unsigned char COR1_CHL5 ; 
 unsigned char COR1_CHL6 ; 
 unsigned char COR1_CHL7 ; 
 unsigned char COR1_CHL8 ; 
 unsigned char COR1_PARENB ; 
 unsigned char COR1_PAREVEN ; 
 unsigned char COR1_PARIGNORE ; 
 unsigned char COR1_PARNONE ; 
 unsigned char COR1_PARODD ; 
 unsigned char COR1_STOP1 ; 
 unsigned char COR1_STOP2 ; 
 int /*<<< orphan*/  COR2 ; 
 unsigned char COR2_CTSAE ; 
 unsigned char COR2_IXM ; 
 unsigned char COR2_TXIBE ; 
 int /*<<< orphan*/  COR3 ; 
 unsigned char COR3_SCD12 ; 
 int /*<<< orphan*/  COR4 ; 
 unsigned char COR4_IGNBRK ; 
 int /*<<< orphan*/  COR5 ; 
 int CRTSCTS ; 
#define  CS5 130 
#define  CS6 129 
#define  CS7 128 
 int CSIZE ; 
 int CSTOPB ; 
 unsigned char FIFO_RTSTHRESHOLD ; 
 unsigned char FIFO_RXTHRESHOLD ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int IXANY ; 
 int IXON ; 
 int /*<<< orphan*/  MCOR1 ; 
 unsigned char MCOR1_DCD ; 
 int /*<<< orphan*/  MCOR2 ; 
 unsigned char MCOR2_DCD ; 
 int /*<<< orphan*/  MSVR1 ; 
 unsigned char MSVR1_DCD ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  RBPR ; 
 int /*<<< orphan*/  RCOR ; 
 int /*<<< orphan*/  RTPR ; 
 int /*<<< orphan*/  SCHR1 ; 
 int /*<<< orphan*/  SCHR2 ; 
 int /*<<< orphan*/  SCHR3 ; 
 int /*<<< orphan*/  SCHR4 ; 
 int /*<<< orphan*/  SRER ; 
 unsigned char SRER_MODEM ; 
 unsigned int STL_CD1400MAXBAUD ; 
 int ST_BREAK ; 
 int ST_FRAMING ; 
 int ST_OVERRUN ; 
 int ST_PARITY ; 
 int /*<<< orphan*/  TBPR ; 
 int /*<<< orphan*/  TCOR ; 
 int /*<<< orphan*/  TIOCM_CD ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  brd_lock ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned char,unsigned char,unsigned char,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int* stl_baudrates ; 
 struct stlbrd** stl_brds ; 
 int /*<<< orphan*/  stl_cd1400ccrwait (struct stlport*) ; 
 unsigned int* stl_cd1400clkdivs ; 
 unsigned char stl_cd1400getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_cd1400setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 
 scalar_t__ stl_cd1400updatereg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_cd1400setport(struct stlport *portp, struct ktermios *tiosp)
{
	struct stlbrd	*brdp;
	unsigned long	flags;
	unsigned int	clkdiv, baudrate;
	unsigned char	cor1, cor2, cor3;
	unsigned char	cor4, cor5, ccr;
	unsigned char	srer, sreron, sreroff;
	unsigned char	mcor1, mcor2, rtpr;
	unsigned char	clk, div;

	cor1 = 0;
	cor2 = 0;
	cor3 = 0;
	cor4 = 0;
	cor5 = 0;
	ccr = 0;
	rtpr = 0;
	clk = 0;
	div = 0;
	mcor1 = 0;
	mcor2 = 0;
	sreron = 0;
	sreroff = 0;

	brdp = stl_brds[portp->brdnr];
	if (brdp == NULL)
		return;

/*
 *	Set up the RX char ignore mask with those RX error types we
 *	can ignore. We can get the cd1400 to help us out a little here,
 *	it will ignore parity errors and breaks for us.
 */
	portp->rxignoremsk = 0;
	if (tiosp->c_iflag & IGNPAR) {
		portp->rxignoremsk |= (ST_PARITY | ST_FRAMING | ST_OVERRUN);
		cor1 |= COR1_PARIGNORE;
	}
	if (tiosp->c_iflag & IGNBRK) {
		portp->rxignoremsk |= ST_BREAK;
		cor4 |= COR4_IGNBRK;
	}

	portp->rxmarkmsk = ST_OVERRUN;
	if (tiosp->c_iflag & (INPCK | PARMRK))
		portp->rxmarkmsk |= (ST_PARITY | ST_FRAMING);
	if (tiosp->c_iflag & BRKINT)
		portp->rxmarkmsk |= ST_BREAK;

/*
 *	Go through the char size, parity and stop bits and set all the
 *	option register appropriately.
 */
	switch (tiosp->c_cflag & CSIZE) {
	case CS5:
		cor1 |= COR1_CHL5;
		break;
	case CS6:
		cor1 |= COR1_CHL6;
		break;
	case CS7:
		cor1 |= COR1_CHL7;
		break;
	default:
		cor1 |= COR1_CHL8;
		break;
	}

	if (tiosp->c_cflag & CSTOPB)
		cor1 |= COR1_STOP2;
	else
		cor1 |= COR1_STOP1;

	if (tiosp->c_cflag & PARENB) {
		if (tiosp->c_cflag & PARODD)
			cor1 |= (COR1_PARENB | COR1_PARODD);
		else
			cor1 |= (COR1_PARENB | COR1_PAREVEN);
	} else {
		cor1 |= COR1_PARNONE;
	}

/*
 *	Set the RX FIFO threshold at 6 chars. This gives a bit of breathing
 *	space for hardware flow control and the like. This should be set to
 *	VMIN. Also here we will set the RX data timeout to 10ms - this should
 *	really be based on VTIME.
 */
	cor3 |= FIFO_RXTHRESHOLD;
	rtpr = 2;

/*
 *	Calculate the baud rate timers. For now we will just assume that
 *	the input and output baud are the same. Could have used a baud
 *	table here, but this way we can generate virtually any baud rate
 *	we like!
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
	if (baudrate > STL_CD1400MAXBAUD)
		baudrate = STL_CD1400MAXBAUD;

	if (baudrate > 0) {
		for (clk = 0; clk < CD1400_NUMCLKS; clk++) {
			clkdiv = (portp->clk / stl_cd1400clkdivs[clk]) / baudrate;
			if (clkdiv < 0x100)
				break;
		}
		div = (unsigned char) clkdiv;
	}

/*
 *	Check what form of modem signaling is required and set it up.
 */
	if ((tiosp->c_cflag & CLOCAL) == 0) {
		mcor1 |= MCOR1_DCD;
		mcor2 |= MCOR2_DCD;
		sreron |= SRER_MODEM;
		portp->port.flags |= ASYNC_CHECK_CD;
	} else
		portp->port.flags &= ~ASYNC_CHECK_CD;

/*
 *	Setup cd1400 enhanced modes if we can. In particular we want to
 *	handle as much of the flow control as possible automatically. As
 *	well as saving a few CPU cycles it will also greatly improve flow
 *	control reliability.
 */
	if (tiosp->c_iflag & IXON) {
		cor2 |= COR2_TXIBE;
		cor3 |= COR3_SCD12;
		if (tiosp->c_iflag & IXANY)
			cor2 |= COR2_IXM;
	}

	if (tiosp->c_cflag & CRTSCTS) {
		cor2 |= COR2_CTSAE;
		mcor1 |= FIFO_RTSTHRESHOLD;
	}

/*
 *	All cd1400 register values calculated so go through and set
 *	them all up.
 */

	pr_debug("SETPORT: portnr=%d panelnr=%d brdnr=%d\n",
		portp->portnr, portp->panelnr, portp->brdnr);
	pr_debug("    cor1=%x cor2=%x cor3=%x cor4=%x cor5=%x\n",
		cor1, cor2, cor3, cor4, cor5);
	pr_debug("    mcor1=%x mcor2=%x rtpr=%x sreron=%x sreroff=%x\n",
		mcor1, mcor2, rtpr, sreron, sreroff);
	pr_debug("    tcor=%x tbpr=%x rcor=%x rbpr=%x\n", clk, div, clk, div);
	pr_debug("    schr1=%x schr2=%x schr3=%x schr4=%x\n",
		tiosp->c_cc[VSTART], tiosp->c_cc[VSTOP],
		tiosp->c_cc[VSTART], tiosp->c_cc[VSTOP]);

	spin_lock_irqsave(&brd_lock, flags);
	BRDENABLE(portp->brdnr, portp->pagenr);
	stl_cd1400setreg(portp, CAR, (portp->portnr & 0x3));
	srer = stl_cd1400getreg(portp, SRER);
	stl_cd1400setreg(portp, SRER, 0);
	if (stl_cd1400updatereg(portp, COR1, cor1))
		ccr = 1;
	if (stl_cd1400updatereg(portp, COR2, cor2))
		ccr = 1;
	if (stl_cd1400updatereg(portp, COR3, cor3))
		ccr = 1;
	if (ccr) {
		stl_cd1400ccrwait(portp);
		stl_cd1400setreg(portp, CCR, CCR_CORCHANGE);
	}
	stl_cd1400setreg(portp, COR4, cor4);
	stl_cd1400setreg(portp, COR5, cor5);
	stl_cd1400setreg(portp, MCOR1, mcor1);
	stl_cd1400setreg(portp, MCOR2, mcor2);
	if (baudrate > 0) {
		stl_cd1400setreg(portp, TCOR, clk);
		stl_cd1400setreg(portp, TBPR, div);
		stl_cd1400setreg(portp, RCOR, clk);
		stl_cd1400setreg(portp, RBPR, div);
	}
	stl_cd1400setreg(portp, SCHR1, tiosp->c_cc[VSTART]);
	stl_cd1400setreg(portp, SCHR2, tiosp->c_cc[VSTOP]);
	stl_cd1400setreg(portp, SCHR3, tiosp->c_cc[VSTART]);
	stl_cd1400setreg(portp, SCHR4, tiosp->c_cc[VSTOP]);
	stl_cd1400setreg(portp, RTPR, rtpr);
	mcor1 = stl_cd1400getreg(portp, MSVR1);
	if (mcor1 & MSVR1_DCD)
		portp->sigs |= TIOCM_CD;
	else
		portp->sigs &= ~TIOCM_CD;
	stl_cd1400setreg(portp, SRER, ((srer & ~sreroff) | sreron));
	BRDDISABLE(portp->brdnr);
	spin_unlock_irqrestore(&brd_lock, flags);
}