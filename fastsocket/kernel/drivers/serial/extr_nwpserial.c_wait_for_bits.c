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
struct nwpserial_port {int /*<<< orphan*/  dcr_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LSR ; 
 unsigned int dcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void wait_for_bits(struct nwpserial_port *up, int bits)
{
	unsigned int status, tmout = 10000;

	/* Wait up to 10ms for the character(s) to be sent. */
	do {
		status = dcr_read(up->dcr_host, UART_LSR);

		if (--tmout == 0)
			break;
		udelay(1);
	} while ((status & bits) != bits);
}