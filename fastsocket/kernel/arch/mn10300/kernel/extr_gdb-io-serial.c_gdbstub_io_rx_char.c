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
typedef  int u8 ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EIO ; 
 int UART_LSR_BI ; 
 int UART_LSR_FE ; 
 int UART_LSR_OE ; 
 int UART_LSR_PE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  gdbstub_proto (char*,...) ; 
 int* gdbstub_rx_buffer ; 
 unsigned int gdbstub_rx_inp ; 
 unsigned int gdbstub_rx_outp ; 
 char gdbstub_rx_unget ; 
 scalar_t__ watchdog_alert_counter ; 

int gdbstub_io_rx_char(unsigned char *_ch, int nonblock)
{
	unsigned ix;
	u8 ch, st;

	*_ch = 0xff;

	if (gdbstub_rx_unget) {
		*_ch = gdbstub_rx_unget;
		gdbstub_rx_unget = 0;
		return 0;
	}

 try_again:
	/* pull chars out of the buffer */
	ix = gdbstub_rx_outp;
	barrier();
	if (ix == gdbstub_rx_inp) {
		if (nonblock)
			return -EAGAIN;
#ifdef CONFIG_MN10300_WD_TIMER
		watchdog_alert_counter = 0;
#endif /* CONFIG_MN10300_WD_TIMER */
		goto try_again;
	}

	ch = gdbstub_rx_buffer[ix++];
	st = gdbstub_rx_buffer[ix++];
	barrier();
	gdbstub_rx_outp = ix & 0x00000fff;

	if (st & UART_LSR_BI) {
		gdbstub_proto("### GDB Rx Break Detected ###\n");
		return -EINTR;
	} else if (st & (UART_LSR_FE | UART_LSR_OE | UART_LSR_PE)) {
		gdbstub_proto("### GDB Rx Error (st=%02x) ###\n", st);
		return -EIO;
	} else {
		gdbstub_proto("### GDB Rx %02x (st=%02x) ###\n", ch, st);
		*_ch = ch & 0x7f;
		return 0;
	}
}