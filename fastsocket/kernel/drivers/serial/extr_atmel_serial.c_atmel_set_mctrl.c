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
typedef  int u_int ;
struct uart_port {scalar_t__ mapbase; } ;

/* Variables and functions */
 scalar_t__ AT91RM9200_BASE_US0 ; 
 int /*<<< orphan*/  AT91_PIN_PA21 ; 
 unsigned int ATMEL_US_CHMODE ; 
 unsigned int ATMEL_US_CHMODE_LOC_LOOP ; 
 unsigned int ATMEL_US_CHMODE_NORMAL ; 
 unsigned int ATMEL_US_DTRDIS ; 
 unsigned int ATMEL_US_DTREN ; 
 unsigned int ATMEL_US_RTSDIS ; 
 unsigned int ATMEL_US_RTSEN ; 
 int TIOCM_DTR ; 
 int TIOCM_LOOP ; 
 int TIOCM_RTS ; 
 unsigned int UART_GET_MR (struct uart_port*) ; 
 int /*<<< orphan*/  UART_PUT_CR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  UART_PUT_MR (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  at91_set_gpio_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ cpu_is_at91rm9200 () ; 

__attribute__((used)) static void atmel_set_mctrl(struct uart_port *port, u_int mctrl)
{
	unsigned int control = 0;
	unsigned int mode;

#ifdef CONFIG_ARCH_AT91RM9200
	if (cpu_is_at91rm9200()) {
		/*
		 * AT91RM9200 Errata #39: RTS0 is not internally connected
		 * to PA21. We need to drive the pin manually.
		 */
		if (port->mapbase == AT91RM9200_BASE_US0) {
			if (mctrl & TIOCM_RTS)
				at91_set_gpio_value(AT91_PIN_PA21, 0);
			else
				at91_set_gpio_value(AT91_PIN_PA21, 1);
		}
	}
#endif

	if (mctrl & TIOCM_RTS)
		control |= ATMEL_US_RTSEN;
	else
		control |= ATMEL_US_RTSDIS;

	if (mctrl & TIOCM_DTR)
		control |= ATMEL_US_DTREN;
	else
		control |= ATMEL_US_DTRDIS;

	UART_PUT_CR(port, control);

	/* Local loopback mode? */
	mode = UART_GET_MR(port) & ~ATMEL_US_CHMODE;
	if (mctrl & TIOCM_LOOP)
		mode |= ATMEL_US_CHMODE_LOC_LOOP;
	else
		mode |= ATMEL_US_CHMODE_NORMAL;
	UART_PUT_MR(port, mode);
}