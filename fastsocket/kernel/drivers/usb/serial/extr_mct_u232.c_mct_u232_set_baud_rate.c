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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;
struct usb_serial {int /*<<< orphan*/  dev; } ;
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  speed_t ;
typedef  unsigned char __le32 ;

/* Variables and functions */
 scalar_t__ C_CRTSCTS (struct tty_struct*) ; 
 int /*<<< orphan*/  MCT_U232_SET_BAUD_RATE_REQUEST ; 
 int /*<<< orphan*/  MCT_U232_SET_BAUD_RATE_SIZE ; 
 int /*<<< orphan*/  MCT_U232_SET_CTS_REQUEST ; 
 int /*<<< orphan*/  MCT_U232_SET_CTS_SIZE ; 
 int /*<<< orphan*/  MCT_U232_SET_REQUEST_TYPE ; 
 int /*<<< orphan*/  MCT_U232_SET_UNKNOWN1_REQUEST ; 
 int /*<<< orphan*/  MCT_U232_SET_UNKNOWN1_SIZE ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 unsigned char cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg (char*,unsigned char,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mct_u232_calculate_baud_rate (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_encode_baud_rate (struct tty_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mct_u232_set_baud_rate(struct tty_struct *tty,
	struct usb_serial *serial, struct usb_serial_port *port, speed_t value)
{
	__le32 divisor;
	int rc;
	unsigned char zero_byte = 0;
	unsigned char cts_enable_byte = 0;
	speed_t speed;

	divisor = cpu_to_le32(mct_u232_calculate_baud_rate(serial, value,
								&speed));

	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				MCT_U232_SET_BAUD_RATE_REQUEST,
				MCT_U232_SET_REQUEST_TYPE,
				0, 0, &divisor, MCT_U232_SET_BAUD_RATE_SIZE,
				WDR_TIMEOUT);
	if (rc < 0)	/*FIXME: What value speed results */
		dev_err(&port->dev, "Set BAUD RATE %d failed (error = %d)\n",
			value, rc);
	else
		tty_encode_baud_rate(tty, speed, speed);
	dbg("set_baud_rate: value: 0x%x, divisor: 0x%x", value, divisor);

	/* Mimic the MCT-supplied Windows driver (version 1.21P.0104), which
	   always sends two extra USB 'device request' messages after the
	   'baud rate change' message.  The actual functionality of the
	   request codes in these messages is not fully understood but these
	   particular codes are never seen in any operation besides a baud
	   rate change.  Both of these messages send a single byte of data.
	   In the first message, the value of this byte is always zero.

	   The second message has been determined experimentally to control
	   whether data will be transmitted to a device which is not asserting
	   the 'CTS' signal.  If the second message's data byte is zero, data
	   will be transmitted even if 'CTS' is not asserted (i.e. no hardware
	   flow control).  if the second message's data byte is nonzero (a
	   value of 1 is used by this driver), data will not be transmitted to
	   a device which is not asserting 'CTS'.
	*/

	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				MCT_U232_SET_UNKNOWN1_REQUEST,
				MCT_U232_SET_REQUEST_TYPE,
				0, 0, &zero_byte, MCT_U232_SET_UNKNOWN1_SIZE,
				WDR_TIMEOUT);
	if (rc < 0)
		dev_err(&port->dev, "Sending USB device request code %d "
			"failed (error = %d)\n", MCT_U232_SET_UNKNOWN1_REQUEST,
			rc);

	if (port && C_CRTSCTS(tty))
	   cts_enable_byte = 1;

	dbg("set_baud_rate: send second control message, data = %02X",
							cts_enable_byte);
	rc = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
			MCT_U232_SET_CTS_REQUEST,
			MCT_U232_SET_REQUEST_TYPE,
			0, 0, &cts_enable_byte, MCT_U232_SET_CTS_SIZE,
			WDR_TIMEOUT);
	if (rc < 0)
		dev_err(&port->dev, "Sending USB device request code %d "
			"failed (error = %d)\n", MCT_U232_SET_CTS_REQUEST, rc);

	return rc;
}