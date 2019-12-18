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
struct uart_port {int iotype; int /*<<< orphan*/  (* serial_out ) (struct uart_port*,int,int) ;int /*<<< orphan*/  (* serial_in ) (struct uart_port*,int /*<<< orphan*/ ) ;} ;
struct uart_8250_port {struct uart_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LCR ; 
#define  UPIO_AU 131 
#define  UPIO_DWAPB 130 
#define  UPIO_MEM 129 
#define  UPIO_MEM32 128 
 int /*<<< orphan*/  stub1 (struct uart_port*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct uart_port*,int,int) ; 

__attribute__((used)) static void
serial_out_sync(struct uart_8250_port *up, int offset, int value)
{
	struct uart_port *p = &up->port;
	switch (p->iotype) {
	case UPIO_MEM:
	case UPIO_MEM32:
#ifdef CONFIG_SERIAL_8250_AU1X00
	case UPIO_AU:
#endif
	case UPIO_DWAPB:
		p->serial_out(p, offset, value);
		p->serial_in(p, UART_LCR);	/* safe, no side-effects */
		break;
	default:
		p->serial_out(p, offset, value);
	}
}