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
struct usb_serial_port {int /*<<< orphan*/  number; } ;
struct quatech2_port {int tx_pending_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*,int /*<<< orphan*/ ,int,int) ; 
 struct quatech2_port* qt2_get_port_private (struct usb_serial_port*) ; 

__attribute__((used)) static void qt2_process_xmit_empty(struct usb_serial_port *port,
	unsigned char fourth_char, unsigned char fifth_char)
{
	int byte_count;
	/* obtain the private structure for the port */
	struct quatech2_port *port_extra = qt2_get_port_private(port);

	byte_count = (int)(fifth_char * 16);
	byte_count +=  (int)fourth_char;
	/* byte_count indicates how many bytes the device has written out. This
	 * message appears to occur regularly, and is used in the vendor driver
	 * to keep track of the fill state of the port transmit buffer */
	port_extra->tx_pending_bytes -= byte_count;
	/* reduce the stored data queue length by the known number of bytes
	 * sent */
	dbg("port %d: %d bytes reported sent, %d still pending", port->number,
			byte_count, port_extra->tx_pending_bytes);

	/*port_extra->xmit_fifo_room_bytes = FIFO_DEPTH; ???*/
}