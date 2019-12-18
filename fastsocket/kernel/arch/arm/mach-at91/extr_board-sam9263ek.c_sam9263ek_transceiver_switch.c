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
 int /*<<< orphan*/  AT91_PIN_PA18 ; 
 int /*<<< orphan*/  AT91_PIN_PA19 ; 
 int /*<<< orphan*/  at91_set_gpio_output (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sam9263ek_transceiver_switch(int on)
{
	if (on) {
		at91_set_gpio_output(AT91_PIN_PA18, 1); /* CANRXEN */
		at91_set_gpio_output(AT91_PIN_PA19, 0); /* CANRS */
	} else {
		at91_set_gpio_output(AT91_PIN_PA18, 0); /* CANRXEN */
		at91_set_gpio_output(AT91_PIN_PA19, 1); /* CANRS */
	}
}