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
 int /*<<< orphan*/  TIOCM_CAR ; 
 int /*<<< orphan*/  TIOCM_CTS ; 
 int /*<<< orphan*/  TIOCM_DSR ; 
 int /*<<< orphan*/  TIOCM_RNG ; 
 int /*<<< orphan*/  UART011_FR_RI ; 
 scalar_t__ UART01x_FR ; 
 int /*<<< orphan*/  UART01x_FR_CTS ; 
 int /*<<< orphan*/  UART01x_FR_DCD ; 
 int /*<<< orphan*/  UART01x_FR_DSR ; 
 unsigned int readw (scalar_t__) ; 

__attribute__((used)) static unsigned int pl01x_get_mctrl(struct uart_port *port)
{
	struct uart_amba_port *uap = (struct uart_amba_port *)port;
	unsigned int result = 0;
	unsigned int status = readw(uap->port.membase + UART01x_FR);

#define TIOCMBIT(uartbit, tiocmbit)	\
	if (status & uartbit)		\
		result |= tiocmbit

	TIOCMBIT(UART01x_FR_DCD, TIOCM_CAR);
	TIOCMBIT(UART01x_FR_DSR, TIOCM_DSR);
	TIOCMBIT(UART01x_FR_CTS, TIOCM_CTS);
	TIOCMBIT(UART011_FR_RI, TIOCM_RNG);
#undef TIOCMBIT
	return result;
}