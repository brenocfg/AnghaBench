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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARK3116_RCV_QUIET (struct usb_serial*,int,int,int,int,char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ark3116_tiocmget(struct tty_struct *tty, struct file *file)
{
	struct usb_serial_port *port = tty->driver_data;
	struct usb_serial *serial = port->serial;
	char *buf;
	char temp;

	/* seems like serial port status info (RTS, CTS, ...) is stored
	 * in reg(?) 0x0006
	 * pcb connection point 11 = GND -> sets bit4 of response
	 * pcb connection point  7 = GND -> sets bit6 of response
	 */

	buf = kmalloc(1, GFP_KERNEL);
	if (!buf) {
		dbg("error kmalloc");
		return -ENOMEM;
	}

	/* read register */
	ARK3116_RCV_QUIET(serial, 0xFE, 0xC0, 0x0000, 0x0006, buf);
	temp = buf[0];
	kfree(buf);

	/* i do not really know if bit4=CTS and bit6=DSR... just a
	 * quick guess!
	 */
	return (temp & (1<<4) ? TIOCM_CTS : 0)
	       | (temp & (1<<6) ? TIOCM_DSR : 0);
}