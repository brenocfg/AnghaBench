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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOSA_GPIO_CARD_VCC_ON ; 
 int gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tosa_tc6393xb_setup(struct platform_device *dev)
{
	int rc;

	rc = gpio_request(TOSA_GPIO_CARD_VCC_ON, "CARD_VCC_ON");
	if (rc)
		goto err_req;

	rc = gpio_direction_output(TOSA_GPIO_CARD_VCC_ON, 1);
	if (rc)
		goto err_dir;

	return rc;

err_dir:
	gpio_free(TOSA_GPIO_CARD_VCC_ON);
err_req:
	return rc;
}