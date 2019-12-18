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
struct device {int dummy; } ;

/* Variables and functions */
 int IR_OFF ; 
 int /*<<< orphan*/  TOSA_GPIO_IRDA_TX ; 
 int /*<<< orphan*/  TOSA_GPIO_IR_POWERDWN ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pxa2xx_transceiver_mode (struct device*,int) ; 

__attribute__((used)) static void tosa_irda_transceiver_mode(struct device *dev, int mode)
{
	if (mode & IR_OFF) {
		gpio_set_value(TOSA_GPIO_IR_POWERDWN, 0);
		pxa2xx_transceiver_mode(dev, mode);
		gpio_direction_output(TOSA_GPIO_IRDA_TX, 0);
	} else {
		pxa2xx_transceiver_mode(dev, mode);
		gpio_set_value(TOSA_GPIO_IR_POWERDWN, 1);
	}
}