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

/* Variables and functions */
 int /*<<< orphan*/  LSR ; 
 int /*<<< orphan*/  RX ; 
 int UART_LSR_DR ; 
 int __UART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clr_IRL () ; 
 int /*<<< orphan*/  __clr_RC (int) ; 
 int* gdbstub_rx_buffer ; 
 unsigned int gdbstub_rx_inp ; 
 unsigned int gdbstub_rx_outp ; 

void gdbstub_do_rx(void)
{
	unsigned ix, nix;

	ix = gdbstub_rx_inp;

	while (__UART(LSR) & UART_LSR_DR) {
		nix = (ix + 2) & 0xfff;
		if (nix == gdbstub_rx_outp)
			break;

		gdbstub_rx_buffer[ix++] = __UART(LSR);
		gdbstub_rx_buffer[ix++] = __UART(RX);
		ix = nix;
	}

	gdbstub_rx_inp = ix;

	__clr_RC(15);
	__clr_IRL();

}