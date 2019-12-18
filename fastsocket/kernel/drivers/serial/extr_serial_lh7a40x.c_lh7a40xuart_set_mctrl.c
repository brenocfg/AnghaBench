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
struct uart_port {scalar_t__ mapbase; } ;
struct TYPE_2__ {int /*<<< orphan*/  pbdr; } ;
typedef  TYPE_1__ gpioRegs_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOB_UART1_RTS ; 
 int /*<<< orphan*/  GPIO_PHYS ; 
 scalar_t__ IO_ADDRESS (int /*<<< orphan*/ ) ; 
 unsigned int TIOCM_RTS ; 
 scalar_t__ UART1_PHYS ; 

__attribute__((used)) static void lh7a40xuart_set_mctrl (struct uart_port* port, unsigned int mctrl)
{
	/* None of the ports supports DTR. UART1 supports RTS through GPIO. */
	/* Note, kernel appears to be setting DTR and RTS on console. */

	/* *** FIXME: this deserves more work.  There's some work in
	       tracing all of the IO pins. */
#if 0
	if( port->mapbase == UART1_PHYS) {
		gpioRegs_t *gpio = (gpioRegs_t *)IO_ADDRESS(GPIO_PHYS);

		if (mctrl & TIOCM_RTS)
			gpio->pbdr &= ~GPIOB_UART1_RTS;
		else
			gpio->pbdr |= GPIOB_UART1_RTS;
	}
#endif
}