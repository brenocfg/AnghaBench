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
struct uart_amba_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCMBIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIOCM_DTR ; 
 int /*<<< orphan*/  TIOCM_LOOP ; 
 int /*<<< orphan*/  TIOCM_OUT1 ; 
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int /*<<< orphan*/  TIOCM_RTS ; 
 scalar_t__ UART011_CR ; 
 int /*<<< orphan*/  UART011_CR_DTR ; 
 int /*<<< orphan*/  UART011_CR_LBE ; 
 int /*<<< orphan*/  UART011_CR_OUT1 ; 
 int /*<<< orphan*/  UART011_CR_OUT2 ; 
 int /*<<< orphan*/  UART011_CR_RTS ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static void pl011_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;
	unsigned int cr;

	cr = readw(uap->port.membase + UART011_CR);

#define	TIOCMBIT(tiocmbit, uartbit)		\
	if (mctrl & tiocmbit)		\
		cr |= uartbit;		\
	else				\
		cr &= ~uartbit

	TIOCMBIT(TIOCM_RTS, UART011_CR_RTS);
	TIOCMBIT(TIOCM_DTR, UART011_CR_DTR);
	TIOCMBIT(TIOCM_OUT1, UART011_CR_OUT1);
	TIOCMBIT(TIOCM_OUT2, UART011_CR_OUT2);
	TIOCMBIT(TIOCM_LOOP, UART011_CR_LBE);
#undef TIOCMBIT

	writew(cr, uap->port.membase + UART011_CR);
}