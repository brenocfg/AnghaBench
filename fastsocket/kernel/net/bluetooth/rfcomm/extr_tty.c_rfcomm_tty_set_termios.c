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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct tty_struct {scalar_t__ driver_data; struct ktermios* termios; } ;
struct rfcomm_dev {TYPE_1__* dlc; } ;
struct ktermios {int c_cflag; scalar_t__* c_cc; } ;
struct TYPE_2__ {int /*<<< orphan*/  dlci; int /*<<< orphan*/  session; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int CRTSCTS ; 
#define  CS5 131 
#define  CS6 130 
#define  CS7 129 
#define  CS8 128 
 int CSIZE ; 
 int CSTOPB ; 
 int PARENB ; 
 int PARODD ; 
 scalar_t__ RFCOMM_RPN_BR_115200 ; 
 scalar_t__ RFCOMM_RPN_BR_19200 ; 
 scalar_t__ RFCOMM_RPN_BR_230400 ; 
 scalar_t__ RFCOMM_RPN_BR_2400 ; 
 scalar_t__ RFCOMM_RPN_BR_38400 ; 
 scalar_t__ RFCOMM_RPN_BR_4800 ; 
 scalar_t__ RFCOMM_RPN_BR_57600 ; 
 scalar_t__ RFCOMM_RPN_BR_7200 ; 
 scalar_t__ RFCOMM_RPN_BR_9600 ; 
 scalar_t__ RFCOMM_RPN_DATA_5 ; 
 scalar_t__ RFCOMM_RPN_DATA_6 ; 
 scalar_t__ RFCOMM_RPN_DATA_7 ; 
 scalar_t__ RFCOMM_RPN_DATA_8 ; 
 int /*<<< orphan*/  RFCOMM_RPN_FLOW_NONE ; 
 scalar_t__ RFCOMM_RPN_PARITY_EVEN ; 
 scalar_t__ RFCOMM_RPN_PARITY_NONE ; 
 scalar_t__ RFCOMM_RPN_PARITY_ODD ; 
 int RFCOMM_RPN_PM_BITRATE ; 
 int RFCOMM_RPN_PM_DATA ; 
 int RFCOMM_RPN_PM_PARITY ; 
 int RFCOMM_RPN_PM_STOP ; 
 int RFCOMM_RPN_PM_XOFF ; 
 int RFCOMM_RPN_PM_XON ; 
 scalar_t__ RFCOMM_RPN_STOP_1 ; 
 scalar_t__ RFCOMM_RPN_STOP_15 ; 
 scalar_t__ RFCOMM_RPN_XOFF_CHAR ; 
 scalar_t__ RFCOMM_RPN_XON_CHAR ; 
 size_t VSTART ; 
 size_t VSTOP ; 
 int /*<<< orphan*/  rfcomm_send_rpn (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 int tty_termios_baud_rate (struct ktermios*) ; 

__attribute__((used)) static void rfcomm_tty_set_termios(struct tty_struct *tty, struct ktermios *old)
{
	struct ktermios *new = tty->termios;
	int old_baud_rate = tty_termios_baud_rate(old);
	int new_baud_rate = tty_termios_baud_rate(new);

	u8 baud, data_bits, stop_bits, parity, x_on, x_off;
	u16 changes = 0;

	struct rfcomm_dev *dev = (struct rfcomm_dev *) tty->driver_data;

	BT_DBG("tty %p termios %p", tty, old);

	if (!dev || !dev->dlc || !dev->dlc->session)
		return;

	/* Handle turning off CRTSCTS */
	if ((old->c_cflag & CRTSCTS) && !(new->c_cflag & CRTSCTS))
		BT_DBG("Turning off CRTSCTS unsupported");

	/* Parity on/off and when on, odd/even */
	if (((old->c_cflag & PARENB) != (new->c_cflag & PARENB)) ||
			((old->c_cflag & PARODD) != (new->c_cflag & PARODD)) ) {
		changes |= RFCOMM_RPN_PM_PARITY;
		BT_DBG("Parity change detected.");
	}

	/* Mark and space parity are not supported! */
	if (new->c_cflag & PARENB) {
		if (new->c_cflag & PARODD) {
			BT_DBG("Parity is ODD");
			parity = RFCOMM_RPN_PARITY_ODD;
		} else {
			BT_DBG("Parity is EVEN");
			parity = RFCOMM_RPN_PARITY_EVEN;
		}
	} else {
		BT_DBG("Parity is OFF");
		parity = RFCOMM_RPN_PARITY_NONE;
	}

	/* Setting the x_on / x_off characters */
	if (old->c_cc[VSTOP] != new->c_cc[VSTOP]) {
		BT_DBG("XOFF custom");
		x_on = new->c_cc[VSTOP];
		changes |= RFCOMM_RPN_PM_XON;
	} else {
		BT_DBG("XOFF default");
		x_on = RFCOMM_RPN_XON_CHAR;
	}

	if (old->c_cc[VSTART] != new->c_cc[VSTART]) {
		BT_DBG("XON custom");
		x_off = new->c_cc[VSTART];
		changes |= RFCOMM_RPN_PM_XOFF;
	} else {
		BT_DBG("XON default");
		x_off = RFCOMM_RPN_XOFF_CHAR;
	}

	/* Handle setting of stop bits */
	if ((old->c_cflag & CSTOPB) != (new->c_cflag & CSTOPB))
		changes |= RFCOMM_RPN_PM_STOP;

	/* POSIX does not support 1.5 stop bits and RFCOMM does not
	 * support 2 stop bits. So a request for 2 stop bits gets
	 * translated to 1.5 stop bits */
	if (new->c_cflag & CSTOPB) {
		stop_bits = RFCOMM_RPN_STOP_15;
	} else {
		stop_bits = RFCOMM_RPN_STOP_1;
	}

	/* Handle number of data bits [5-8] */
	if ((old->c_cflag & CSIZE) != (new->c_cflag & CSIZE))
		changes |= RFCOMM_RPN_PM_DATA;

	switch (new->c_cflag & CSIZE) {
	case CS5:
		data_bits = RFCOMM_RPN_DATA_5;
		break;
	case CS6:
		data_bits = RFCOMM_RPN_DATA_6;
		break;
	case CS7:
		data_bits = RFCOMM_RPN_DATA_7;
		break;
	case CS8:
		data_bits = RFCOMM_RPN_DATA_8;
		break;
	default:
		data_bits = RFCOMM_RPN_DATA_8;
		break;
	}

	/* Handle baudrate settings */
	if (old_baud_rate != new_baud_rate)
		changes |= RFCOMM_RPN_PM_BITRATE;

	switch (new_baud_rate) {
	case 2400:
		baud = RFCOMM_RPN_BR_2400;
		break;
	case 4800:
		baud = RFCOMM_RPN_BR_4800;
		break;
	case 7200:
		baud = RFCOMM_RPN_BR_7200;
		break;
	case 9600:
		baud = RFCOMM_RPN_BR_9600;
		break;
	case 19200:
		baud = RFCOMM_RPN_BR_19200;
		break;
	case 38400:
		baud = RFCOMM_RPN_BR_38400;
		break;
	case 57600:
		baud = RFCOMM_RPN_BR_57600;
		break;
	case 115200:
		baud = RFCOMM_RPN_BR_115200;
		break;
	case 230400:
		baud = RFCOMM_RPN_BR_230400;
		break;
	default:
		/* 9600 is standard accordinag to the RFCOMM specification */
		baud = RFCOMM_RPN_BR_9600;
		break;

	}

	if (changes)
		rfcomm_send_rpn(dev->dlc->session, 1, dev->dlc->dlci, baud,
				data_bits, stop_bits, parity,
				RFCOMM_RPN_FLOW_NONE, x_on, x_off, changes);

	return;
}