#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_serial {TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char MCT_U232_MCR_DTR ; 
 unsigned char MCT_U232_MCR_NONE ; 
 unsigned char MCT_U232_MCR_RTS ; 
 int /*<<< orphan*/  MCT_U232_SET_MODEM_CTRL_REQUEST ; 
 int /*<<< orphan*/  MCT_U232_SET_MODEM_CTRL_SIZE ; 
 int /*<<< orphan*/  MCT_U232_SET_REQUEST_TYPE ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 int /*<<< orphan*/  dbg (char*,unsigned int,unsigned char) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned char,int) ; 
 int usb_control_msg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mct_u232_set_modem_ctrl(struct usb_serial *serial,
				   unsigned int control_state)
{
	int rc;
	unsigned char mcr = MCT_U232_MCR_NONE;

	if (control_state & TIOCM_DTR)
		mcr |= MCT_U232_MCR_DTR;
	if (control_state & TIOCM_RTS)
		mcr |= MCT_U232_MCR_RTS;

	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			MCT_U232_SET_MODEM_CTRL_REQUEST,
			MCT_U232_SET_REQUEST_TYPE,
			0, 0, &mcr, MCT_U232_SET_MODEM_CTRL_SIZE,
			WDR_TIMEOUT);
	if (rc < 0)
		dev_err(&serial->dev->dev,
			"Set MODEM CTRL 0x%x failed (error = %d)\n", mcr, rc);
	dbg("set_modem_ctrl: state=0x%x ==> mcr=0x%x", control_state, mcr);

	return rc;
}