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
struct cx231xx_reg_seq {scalar_t__ sleep; int /*<<< orphan*/  val; int /*<<< orphan*/  bit; } ;
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int cx231xx_set_gpio_value (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 

int cx231xx_gpio_set(struct cx231xx *dev, struct cx231xx_reg_seq *gpio)
{
	int rc = 0;

	if (!gpio)
		return rc;

	/* Send GPIO reset sequences specified at board entry */
	while (gpio->sleep >= 0) {
		rc = cx231xx_set_gpio_value(dev, gpio->bit, gpio->val);
		if (rc < 0)
			return rc;

		if (gpio->sleep > 0)
			msleep(gpio->sleep);

		gpio++;
	}
	return rc;
}