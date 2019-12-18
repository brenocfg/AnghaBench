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
struct seq_file {int dummy; } ;
struct TYPE_2__ {int frame; int parity; int brk; int overrun; int cts; int dsr; int rng; int dcd; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; } ;
struct sdio_uart_port {TYPE_1__ icount; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int UART_NR ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 struct sdio_uart_port* sdio_uart_port_get (int) ; 
 int /*<<< orphan*/  sdio_uart_port_put (struct sdio_uart_port*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

__attribute__((used)) static int sdio_uart_proc_show(struct seq_file *m, void *v)
{
	int i;

	seq_printf(m, "serinfo:1.0 driver%s%s revision:%s\n",
		       "", "", "");
	for (i = 0; i < UART_NR; i++) {
		struct sdio_uart_port *port = sdio_uart_port_get(i);
		if (port) {
			seq_printf(m, "%d: uart:SDIO", i);
			if(capable(CAP_SYS_ADMIN)) {
				seq_printf(m, " tx:%d rx:%d",
					       port->icount.tx, port->icount.rx);
				if (port->icount.frame)
					seq_printf(m, " fe:%d",
						       port->icount.frame);
				if (port->icount.parity)
					seq_printf(m, " pe:%d",
						       port->icount.parity);
				if (port->icount.brk)
					seq_printf(m, " brk:%d",
						       port->icount.brk);
				if (port->icount.overrun)
					seq_printf(m, " oe:%d",
						       port->icount.overrun);
				if (port->icount.cts)
					seq_printf(m, " cts:%d",
						       port->icount.cts);
				if (port->icount.dsr)
					seq_printf(m, " dsr:%d",
						       port->icount.dsr);
				if (port->icount.rng)
					seq_printf(m, " rng:%d",
						       port->icount.rng);
				if (port->icount.dcd)
					seq_printf(m, " dcd:%d",
						       port->icount.dcd);
			}
			sdio_uart_port_put(port);
			seq_putc(m, '\n');
		}
	}
	return 0;
}