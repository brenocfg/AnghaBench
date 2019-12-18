#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int tcflag_t ;
struct ktermios {int c_lflag; int c_cflag; int c_iflag; char* c_cc; } ;
typedef  TYPE_2__* i2ChanStrPtr ;
struct TYPE_10__ {TYPE_1__* termios; } ;
struct TYPE_9__ {int dataSetOut; int flags; scalar_t__ speed; int BaudBase; int BaudDivisor; TYPE_6__* pTTY; } ;
struct TYPE_8__ {int c_lflag; int c_cflag; int c_iflag; } ;

/* Variables and functions */
 int ASYNC_CHECK_CD ; 
 int ASYNC_SPD_CUST ; 
 int ASYNC_SPD_HI ; 
 int ASYNC_SPD_MASK ; 
 int ASYNC_SPD_VHI ; 
#define  B0 154 
#define  B110 153 
#define  B115200 152 
#define  B1200 151 
#define  B134 150 
#define  B150 149 
#define  B153600 148 
#define  B1800 147 
#define  B19200 146 
#define  B200 145 
#define  B230400 144 
#define  B2400 143 
#define  B300 142 
#define  B307200 141 
#define  B38400 140 
#define  B460800 139 
#define  B4800 138 
#define  B50 137 
#define  B57600 136 
#define  B600 135 
#define  B75 134 
#define  B921600 133 
#define  B9600 132 
 int BRKINT ; 
 int CBAUD ; 
 scalar_t__ CBR_110 ; 
 void* CBR_115200 ; 
 scalar_t__ CBR_1200 ; 
 scalar_t__ CBR_134 ; 
 scalar_t__ CBR_150 ; 
 scalar_t__ CBR_153600 ; 
 scalar_t__ CBR_1800 ; 
 scalar_t__ CBR_19200 ; 
 scalar_t__ CBR_200 ; 
 scalar_t__ CBR_230400 ; 
 scalar_t__ CBR_2400 ; 
 scalar_t__ CBR_300 ; 
 scalar_t__ CBR_307200 ; 
 scalar_t__ CBR_38400 ; 
 scalar_t__ CBR_460800 ; 
 scalar_t__ CBR_4800 ; 
 scalar_t__ CBR_50 ; 
 void* CBR_57600 ; 
 scalar_t__ CBR_600 ; 
 scalar_t__ CBR_75 ; 
 void* CBR_921600 ; 
 void* CBR_9600 ; 
 scalar_t__ CBR_C1 ; 
 int /*<<< orphan*/  CIX_NONE ; 
 int /*<<< orphan*/  CIX_XANY ; 
 int /*<<< orphan*/  CIX_XON ; 
 int CLOCAL ; 
 int /*<<< orphan*/  CMD_BAUD_DEF1 (int) ; 
 int /*<<< orphan*/  CMD_BRK_NREP ; 
 int /*<<< orphan*/  CMD_BRK_REP (char) ; 
 int /*<<< orphan*/  CMD_CTSFL_DSAB ; 
 int /*<<< orphan*/  CMD_CTSFL_ENAB ; 
 int /*<<< orphan*/  CMD_DCD_NREP ; 
 int /*<<< orphan*/  CMD_DCD_REP ; 
 int /*<<< orphan*/  CMD_DEF_IXOFF (char) ; 
 int /*<<< orphan*/  CMD_DEF_IXON (char) ; 
 int /*<<< orphan*/  CMD_DEF_OXOFF (char) ; 
 int /*<<< orphan*/  CMD_DEF_OXON (char) ; 
 int /*<<< orphan*/  CMD_DTRDN ; 
 int /*<<< orphan*/  CMD_DTRUP ; 
 int /*<<< orphan*/  CMD_ISTRIP_OPT (char) ; 
 int /*<<< orphan*/  CMD_IXON_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_OXON_OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_PARCHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_PAUSE (int) ; 
 int /*<<< orphan*/  CMD_RTSDN ; 
 int /*<<< orphan*/  CMD_RTSFL_DSAB ; 
 int /*<<< orphan*/  CMD_RTSFL_ENAB ; 
 int /*<<< orphan*/  CMD_RTSUP ; 
 int /*<<< orphan*/  CMD_SETBAUD (scalar_t__) ; 
 int /*<<< orphan*/  CMD_SETBITS (int) ; 
 int /*<<< orphan*/  CMD_SETPAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_SETSTOP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_SET_ERROR (char) ; 
 int /*<<< orphan*/  COX_NONE ; 
 int /*<<< orphan*/  COX_XON ; 
 int /*<<< orphan*/  CPK_DSAB ; 
 int /*<<< orphan*/  CPK_ENAB ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int /*<<< orphan*/  CSP_EV ; 
 int /*<<< orphan*/  CSP_NP ; 
 int /*<<< orphan*/  CSP_OD ; 
 int CSTOPB ; 
 int /*<<< orphan*/  CST_1 ; 
 int /*<<< orphan*/  CST_2 ; 
 int CSZ_5 ; 
 int CSZ_6 ; 
 int CSZ_7 ; 
 int CSZ_8 ; 
 int I2_DTR ; 
 int I2_RTS ; 
 int IGNBRK ; 
 int IGNPAR ; 
 int INPCK ; 
 int ISTRIP ; 
 int IXANY ; 
 int IXOFF ; 
 int IXON ; 
 int PARENB ; 
 int PARMRK ; 
 int PARODD ; 
 int /*<<< orphan*/  PTYPE_BYPASS ; 
 int /*<<< orphan*/  PTYPE_INLINE ; 
 char START_CHAR (TYPE_6__*) ; 
 char STOP_CHAR (TYPE_6__*) ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 char __DISABLED_CHAR ; 
 int /*<<< orphan*/  i2DrainOutput (TYPE_2__*,int) ; 
 int /*<<< orphan*/  i2QueueCommands (int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
set_params( i2ChanStrPtr pCh, struct ktermios *o_tios )
{
	tcflag_t cflag, iflag, lflag;
	char stop_char, start_char;
	struct ktermios dummy;

	lflag = pCh->pTTY->termios->c_lflag;
	cflag = pCh->pTTY->termios->c_cflag;
	iflag = pCh->pTTY->termios->c_iflag;

	if (o_tios == NULL) {
		dummy.c_lflag = ~lflag;
		dummy.c_cflag = ~cflag;
		dummy.c_iflag = ~iflag;
		o_tios = &dummy;
	}

	{
		switch ( cflag & CBAUD ) {
		case B0:
			i2QueueCommands( PTYPE_BYPASS, pCh, 100, 2, CMD_RTSDN, CMD_DTRDN);
			pCh->dataSetOut &= ~(I2_DTR | I2_RTS);
			i2QueueCommands( PTYPE_INLINE, pCh, 100, 1, CMD_PAUSE(25));
			pCh->pTTY->termios->c_cflag |= (CBAUD & o_tios->c_cflag);
			goto service_it;
			break;
		case B38400:
			/*
			 * This is the speed that is overloaded with all the other high
			 * speeds, depending upon the flag settings.
			 */
			if ( ( pCh->flags & ASYNC_SPD_MASK ) == ASYNC_SPD_HI ) {
				pCh->speed = CBR_57600;
			} else if ( (pCh->flags & ASYNC_SPD_MASK) == ASYNC_SPD_VHI ) {
				pCh->speed = CBR_115200;
			} else if ( (pCh->flags & ASYNC_SPD_MASK) == ASYNC_SPD_CUST ) {
				pCh->speed = CBR_C1;
			} else {
				pCh->speed = CBR_38400;
			}
			break;
		case B50:      pCh->speed = CBR_50;      break;
		case B75:      pCh->speed = CBR_75;      break;
		case B110:     pCh->speed = CBR_110;     break;
		case B134:     pCh->speed = CBR_134;     break;
		case B150:     pCh->speed = CBR_150;     break;
		case B200:     pCh->speed = CBR_200;     break;
		case B300:     pCh->speed = CBR_300;     break;
		case B600:     pCh->speed = CBR_600;     break;
		case B1200:    pCh->speed = CBR_1200;    break;
		case B1800:    pCh->speed = CBR_1800;    break;
		case B2400:    pCh->speed = CBR_2400;    break;
		case B4800:    pCh->speed = CBR_4800;    break;
		case B9600:    pCh->speed = CBR_9600;    break;
		case B19200:   pCh->speed = CBR_19200;   break;
		case B57600:   pCh->speed = CBR_57600;   break;
		case B115200:  pCh->speed = CBR_115200;  break;
		case B153600:  pCh->speed = CBR_153600;  break;
		case B230400:  pCh->speed = CBR_230400;  break;
		case B307200:  pCh->speed = CBR_307200;  break;
		case B460800:  pCh->speed = CBR_460800;  break;
		case B921600:  pCh->speed = CBR_921600;  break;
		default:       pCh->speed = CBR_9600;    break;
		}
		if ( pCh->speed == CBR_C1 ) {
			// Process the custom speed parameters.
			int bps = pCh->BaudBase / pCh->BaudDivisor;
			if ( bps == 921600 ) {
				pCh->speed = CBR_921600;
			} else {
				bps = bps/10;
				i2QueueCommands( PTYPE_INLINE, pCh, 100, 1, CMD_BAUD_DEF1(bps) );
			}
		}
		i2QueueCommands( PTYPE_INLINE, pCh, 100, 1, CMD_SETBAUD(pCh->speed));
		
		i2QueueCommands ( PTYPE_INLINE, pCh, 100, 2, CMD_DTRUP, CMD_RTSUP);
		pCh->dataSetOut |= (I2_DTR | I2_RTS);
	}
	if ( (CSTOPB & cflag) ^ (CSTOPB & o_tios->c_cflag)) 
	{
		i2QueueCommands ( PTYPE_INLINE, pCh, 100, 1, 
			CMD_SETSTOP( ( cflag & CSTOPB ) ? CST_2 : CST_1));
	}
	if (((PARENB|PARODD) & cflag) ^ ((PARENB|PARODD) & o_tios->c_cflag)) 
	{
		i2QueueCommands ( PTYPE_INLINE, pCh, 100, 1,
			CMD_SETPAR( 
				(cflag & PARENB ?  (cflag & PARODD ? CSP_OD : CSP_EV) : CSP_NP)
			)
		);
	}
	/* byte size and parity */
	if ( (CSIZE & cflag)^(CSIZE & o_tios->c_cflag)) 
	{
		int datasize;
		switch ( cflag & CSIZE ) {
		case CS5: datasize = CSZ_5; break;
		case CS6: datasize = CSZ_6; break;
		case CS7: datasize = CSZ_7; break;
		case CS8: datasize = CSZ_8; break;
		default:  datasize = CSZ_5; break;	/* as per serial.c */
		}
		i2QueueCommands ( PTYPE_INLINE, pCh, 100, 1, CMD_SETBITS(datasize) );
	}
	/* Process CTS flow control flag setting */
	if ( (cflag & CRTSCTS) ) {
		i2QueueCommands(PTYPE_INLINE, pCh, 100,
						2, CMD_CTSFL_ENAB, CMD_RTSFL_ENAB);
	} else {
		i2QueueCommands(PTYPE_INLINE, pCh, 100,
						2, CMD_CTSFL_DSAB, CMD_RTSFL_DSAB);
	}
	//
	// Process XON/XOFF flow control flags settings
	//
	stop_char = STOP_CHAR(pCh->pTTY);
	start_char = START_CHAR(pCh->pTTY);

	//////////// can't be \000
	if (stop_char == __DISABLED_CHAR ) 
	{
		stop_char = ~__DISABLED_CHAR; 
	}
	if (start_char == __DISABLED_CHAR ) 
	{
		start_char = ~__DISABLED_CHAR;
	}
	/////////////////////////////////

	if ( o_tios->c_cc[VSTART] != start_char ) 
	{
		i2QueueCommands(PTYPE_BYPASS, pCh, 100, 1, CMD_DEF_IXON(start_char));
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_DEF_OXON(start_char));
	}
	if ( o_tios->c_cc[VSTOP] != stop_char ) 
	{
		 i2QueueCommands(PTYPE_BYPASS, pCh, 100, 1, CMD_DEF_IXOFF(stop_char));
		 i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_DEF_OXOFF(stop_char));
	}
	if (stop_char == __DISABLED_CHAR ) 
	{
		stop_char = ~__DISABLED_CHAR;  //TEST123
		goto no_xoff;
	}
	if ((iflag & (IXOFF))^(o_tios->c_iflag & (IXOFF))) 
	{
		if ( iflag & IXOFF ) {	// Enable XOFF output flow control
			i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_OXON_OPT(COX_XON));
		} else {	// Disable XOFF output flow control
no_xoff:
			i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_OXON_OPT(COX_NONE));
		}
	}
	if (start_char == __DISABLED_CHAR ) 
	{
		goto no_xon;
	}
	if ((iflag & (IXON|IXANY)) ^ (o_tios->c_iflag & (IXON|IXANY))) 
	{
		if ( iflag & IXON ) {
			if ( iflag & IXANY ) { // Enable XON/XANY output flow control
				i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_IXON_OPT(CIX_XANY));
			} else { // Enable XON output flow control
				i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_IXON_OPT(CIX_XON));
			}
		} else { // Disable XON output flow control
no_xon:
			i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_IXON_OPT(CIX_NONE));
		}
	}
	if ( (iflag & ISTRIP) ^ ( o_tios->c_iflag & (ISTRIP)) ) 
	{
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, 
				CMD_ISTRIP_OPT((iflag & ISTRIP ? 1 : 0)));
	}
	if ( (iflag & INPCK) ^ ( o_tios->c_iflag & (INPCK)) ) 
	{
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, 
				CMD_PARCHK((iflag & INPCK) ? CPK_ENAB : CPK_DSAB));
	}

	if ( (iflag & (IGNBRK|PARMRK|BRKINT|IGNPAR)) 
			^	( o_tios->c_iflag & (IGNBRK|PARMRK|BRKINT|IGNPAR)) ) 
	{
		char brkrpt = 0;
		char parrpt = 0;

		if ( iflag & IGNBRK ) { /* Ignore breaks altogether */
			/* Ignore breaks altogether */
			i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_BRK_NREP);
		} else {
			if ( iflag & BRKINT ) {
				if ( iflag & PARMRK ) {
					brkrpt = 0x0a;	// exception an inline triple
				} else {
					brkrpt = 0x1a;	// exception and NULL
				}
				brkrpt |= 0x04;	// flush input
			} else {
				if ( iflag & PARMRK ) {
					brkrpt = 0x0b;	//POSIX triple \0377 \0 \0
				} else {
					brkrpt = 0x01;	// Null only
				}
			}
			i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_BRK_REP(brkrpt));
		} 

		if (iflag & IGNPAR) {
			parrpt = 0x20;
													/* would be 2 for not cirrus bug */
													/* would be 0x20 cept for cirrus bug */
		} else {
			if ( iflag & PARMRK ) {
				/*
				 * Replace error characters with 3-byte sequence (\0377,\0,char)
				 */
				parrpt = 0x04 ;
				i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_ISTRIP_OPT((char)0));
			} else {
				parrpt = 0x03;
			} 
		}
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_SET_ERROR(parrpt));
	}
	if (cflag & CLOCAL) {
		// Status reporting fails for DCD if this is off
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_DCD_NREP);
		pCh->flags &= ~ASYNC_CHECK_CD;
	} else {
		i2QueueCommands(PTYPE_INLINE, pCh, 100, 1, CMD_DCD_REP);
		pCh->flags	|= ASYNC_CHECK_CD;
	}

service_it:
	i2DrainOutput( pCh, 100 );		
}