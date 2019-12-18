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
struct uart_port {int dummy; } ;
struct TYPE_2__ {scalar_t__ membase; } ;
struct uart_amba_port {int im; TYPE_1__ port; } ;

/* Variables and functions */
 int UART011_BEIM ; 
 int UART011_FEIM ; 
 scalar_t__ UART011_IMSC ; 
 int UART011_OEIM ; 
 int UART011_PEIM ; 
 int UART011_RTIM ; 
 int UART011_RXIM ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void pl011_stop_rx(struct uart_port *port)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;

	uap->im &= ~(UART011_RXIM|UART011_RTIM|UART011_FEIM|
		     UART011_PEIM|UART011_BEIM|UART011_OEIM);
	writew(uap->im, uap->port.membase + UART011_IMSC);
}