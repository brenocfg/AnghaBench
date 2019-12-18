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
struct uart_port {int dummy; } ;
struct uart_cpm_port {scalar_t__* gpios; } ;

/* Variables and functions */
 size_t GPIO_CTS ; 
 size_t GPIO_DCD ; 
 size_t GPIO_DSR ; 
 size_t GPIO_RI ; 
 unsigned int TIOCM_CAR ; 
 unsigned int TIOCM_CTS ; 
 unsigned int TIOCM_DSR ; 
 unsigned int TIOCM_RNG ; 
 scalar_t__ gpio_get_value (scalar_t__) ; 

__attribute__((used)) static unsigned int cpm_uart_get_mctrl(struct uart_port *port)
{
	struct uart_cpm_port *pinfo = (struct uart_cpm_port *)port;
	unsigned int mctrl = TIOCM_CTS | TIOCM_DSR | TIOCM_CAR;

	if (pinfo->gpios[GPIO_CTS] >= 0) {
		if (gpio_get_value(pinfo->gpios[GPIO_CTS]))
			mctrl &= ~TIOCM_CTS;
	}

	if (pinfo->gpios[GPIO_DSR] >= 0) {
		if (gpio_get_value(pinfo->gpios[GPIO_DSR]))
			mctrl &= ~TIOCM_DSR;
	}

	if (pinfo->gpios[GPIO_DCD] >= 0) {
		if (gpio_get_value(pinfo->gpios[GPIO_DCD]))
			mctrl &= ~TIOCM_CAR;
	}

	if (pinfo->gpios[GPIO_RI] >= 0) {
		if (!gpio_get_value(pinfo->gpios[GPIO_RI]))
			mctrl |= TIOCM_RNG;
	}

	return mctrl;
}