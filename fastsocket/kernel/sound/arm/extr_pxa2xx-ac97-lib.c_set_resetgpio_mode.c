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
 int GPIO_ALT_FN_1_OUT ; 
 int GPIO_ALT_FN_2_OUT ; 
 int GPIO_DFLT_HIGH ; 
 int GPIO_DFLT_LOW ; 
 int GPIO_OUT ; 
#define  RESETGPIO_FORCE_HIGH 130 
#define  RESETGPIO_FORCE_LOW 129 
#define  RESETGPIO_NORMAL_ALTFUNC 128 
 int /*<<< orphan*/  pxa_gpio_mode (int) ; 
 int reset_gpio ; 

__attribute__((used)) static void set_resetgpio_mode(int resetgpio_action)
{
	int mode = 0;

	if (reset_gpio)
		switch (resetgpio_action) {
		case RESETGPIO_NORMAL_ALTFUNC:
			if (reset_gpio == 113)
				mode = 113 | GPIO_ALT_FN_2_OUT;
			if (reset_gpio == 95)
				mode = 95 | GPIO_ALT_FN_1_OUT;
			break;
		case RESETGPIO_FORCE_LOW:
			mode = reset_gpio | GPIO_OUT | GPIO_DFLT_LOW;
			break;
		case RESETGPIO_FORCE_HIGH:
			mode = reset_gpio | GPIO_OUT | GPIO_DFLT_HIGH;
			break;
		};

	if (mode)
		pxa_gpio_mode(mode);
}