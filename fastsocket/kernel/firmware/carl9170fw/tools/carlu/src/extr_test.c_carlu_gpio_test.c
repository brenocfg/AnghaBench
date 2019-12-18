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
typedef  int /*<<< orphan*/  uint32_t ;
struct carlu {int dummy; } ;

/* Variables and functions */
 int AR9170_GPIO_PORT_LED_0 ; 
 int AR9170_GPIO_PORT_LED_1 ; 
 int /*<<< orphan*/  AR9170_GPIO_REG_PORT_DATA ; 
 int /*<<< orphan*/  CHK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int /*<<< orphan*/  carlu_cmd_read_mem (struct carlu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  carlu_cmd_write_mem (struct carlu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  info (char*,int /*<<< orphan*/ ) ; 

int carlu_gpio_test(struct carlu *ar)
{
	uint32_t gpio;

#define CHK(cmd)				\
	do {					\
		int __err = cmd;		\
		if ((__err))			\
			return __err;		\
	} while (0)

	CHK(carlu_cmd_read_mem(ar, AR9170_GPIO_REG_PORT_DATA, &gpio));
	info("GPIO state:%x\n", gpio);

	/* turn both LEDs on */
	CHK(carlu_cmd_write_mem(ar, AR9170_GPIO_REG_PORT_DATA,
	    AR9170_GPIO_PORT_LED_0 | AR9170_GPIO_PORT_LED_1));

	SDL_Delay(700);

	CHK(carlu_cmd_read_mem(ar, AR9170_GPIO_REG_PORT_DATA, &gpio));
	info("GPIO state:%x\n", gpio);

	/* turn LEDs off everything */
	CHK(carlu_cmd_write_mem(ar, AR9170_GPIO_REG_PORT_DATA, 0));

	CHK(carlu_cmd_read_mem(ar, AR9170_GPIO_REG_PORT_DATA, &gpio));
	info("GPIO state:%x\n", gpio);
}