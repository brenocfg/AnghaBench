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
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_GPIO_REG_PORT_TYPE ; 
 int carl9170_led_set_state (struct ar9170*,int /*<<< orphan*/ ) ; 
 int carl9170_write_reg (struct ar9170*,int /*<<< orphan*/ ,int) ; 

int carl9170_led_init(struct ar9170 *ar)
{
	int err;

	/* disable LEDs */
	/* GPIO [0/1 mode: output, 2/3: input] */
	err = carl9170_write_reg(ar, AR9170_GPIO_REG_PORT_TYPE, 3);
	if (err)
		goto out;

	/* GPIO 0/1 value: off */
	err = carl9170_led_set_state(ar, 0);

out:
	return err;
}