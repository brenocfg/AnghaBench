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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct uart_8250_port {int capabilities; TYPE_1__ port; int /*<<< orphan*/  bugs; scalar_t__ acr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_AUTOCONF (char*,unsigned int,...) ; 
 int /*<<< orphan*/  PORT_16650V2 ; 
 int /*<<< orphan*/  PORT_16654 ; 
 int /*<<< orphan*/  PORT_16850 ; 
 int /*<<< orphan*/  PORT_16C950 ; 
 int /*<<< orphan*/  UART_BUG_QUOT ; 
 int UART_CAP_EFR ; 
 int UART_CAP_SLEEP ; 
 int /*<<< orphan*/  UART_EFR ; 
 int UART_EFR_ECB ; 
 int /*<<< orphan*/  UART_ID1 ; 
 int /*<<< orphan*/  UART_ID2 ; 
 int /*<<< orphan*/  UART_ID3 ; 
 int /*<<< orphan*/  UART_LCR ; 
 int /*<<< orphan*/  UART_REV ; 
 unsigned int autoconfig_read_divisor_id (struct uart_8250_port*) ; 
 unsigned int serial_icr_read (struct uart_8250_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct uart_8250_port*,int /*<<< orphan*/ ,int) ; 
 int size_fifo (struct uart_8250_port*) ; 

__attribute__((used)) static void autoconfig_has_efr(struct uart_8250_port *up)
{
	unsigned int id1, id2, id3, rev;

	/*
	 * Everything with an EFR has SLEEP
	 */
	up->capabilities |= UART_CAP_EFR | UART_CAP_SLEEP;

	/*
	 * First we check to see if it's an Oxford Semiconductor UART.
	 *
	 * If we have to do this here because some non-National
	 * Semiconductor clone chips lock up if you try writing to the
	 * LSR register (which serial_icr_read does)
	 */

	/*
	 * Check for Oxford Semiconductor 16C950.
	 *
	 * EFR [4] must be set else this test fails.
	 *
	 * This shouldn't be necessary, but Mike Hudson (Exoray@isys.ca)
	 * claims that it's needed for 952 dual UART's (which are not
	 * recommended for new designs).
	 */
	up->acr = 0;
	serial_out(up, UART_LCR, 0xBF);
	serial_out(up, UART_EFR, UART_EFR_ECB);
	serial_out(up, UART_LCR, 0x00);
	id1 = serial_icr_read(up, UART_ID1);
	id2 = serial_icr_read(up, UART_ID2);
	id3 = serial_icr_read(up, UART_ID3);
	rev = serial_icr_read(up, UART_REV);

	DEBUG_AUTOCONF("950id=%02x:%02x:%02x:%02x ", id1, id2, id3, rev);

	if (id1 == 0x16 && id2 == 0xC9 &&
	    (id3 == 0x50 || id3 == 0x52 || id3 == 0x54)) {
		up->port.type = PORT_16C950;

		/*
		 * Enable work around for the Oxford Semiconductor 952 rev B
		 * chip which causes it to seriously miscalculate baud rates
		 * when DLL is 0.
		 */
		if (id3 == 0x52 && rev == 0x01)
			up->bugs |= UART_BUG_QUOT;
		return;
	}

	/*
	 * We check for a XR16C850 by setting DLL and DLM to 0, and then
	 * reading back DLL and DLM.  The chip type depends on the DLM
	 * value read back:
	 *  0x10 - XR16C850 and the DLL contains the chip revision.
	 *  0x12 - XR16C2850.
	 *  0x14 - XR16C854.
	 */
	id1 = autoconfig_read_divisor_id(up);
	DEBUG_AUTOCONF("850id=%04x ", id1);

	id2 = id1 >> 8;
	if (id2 == 0x10 || id2 == 0x12 || id2 == 0x14) {
		up->port.type = PORT_16850;
		return;
	}

	/*
	 * It wasn't an XR16C850.
	 *
	 * We distinguish between the '654 and the '650 by counting
	 * how many bytes are in the FIFO.  I'm using this for now,
	 * since that's the technique that was sent to me in the
	 * serial driver update, but I'm not convinced this works.
	 * I've had problems doing this in the past.  -TYT
	 */
	if (size_fifo(up) == 64)
		up->port.type = PORT_16654;
	else
		up->port.type = PORT_16650V2;
}