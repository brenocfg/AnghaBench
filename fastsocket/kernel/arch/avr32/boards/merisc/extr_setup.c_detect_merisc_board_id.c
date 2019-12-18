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
 int /*<<< orphan*/  AT32_GPIOF_PULLUP ; 
 int /*<<< orphan*/  GPIO_PIN_PA (int) ; 
 int /*<<< orphan*/  at32_select_gpio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 int merisc_board_id ; 

__attribute__((used)) static void detect_merisc_board_id(void)
{
	/* Board ID pins MUST be set as input or the board may be damaged */
	at32_select_gpio(GPIO_PIN_PA(24), AT32_GPIOF_PULLUP);
	at32_select_gpio(GPIO_PIN_PA(25), AT32_GPIOF_PULLUP);
	at32_select_gpio(GPIO_PIN_PA(26), AT32_GPIOF_PULLUP);
	at32_select_gpio(GPIO_PIN_PA(27), AT32_GPIOF_PULLUP);

	merisc_board_id = !gpio_get_value(GPIO_PIN_PA(24)) +
		!gpio_get_value(GPIO_PIN_PA(25)) * 2 +
		!gpio_get_value(GPIO_PIN_PA(26)) * 4 +
		!gpio_get_value(GPIO_PIN_PA(27)) * 8;
}