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
 int /*<<< orphan*/  avr_uart_configure () ; 
 int /*<<< orphan*/  avr_uart_send (char) ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static void linkstation_power_off(void)
{
	local_irq_disable();

	/* Power down system via AVR */
	avr_uart_configure();
	/* send shutdown command */
	avr_uart_send('E');

	for(;;)  /* Spin until power-off happens */
		avr_uart_send('G');	/* "kick" */
	/* NOTREACHED */
}