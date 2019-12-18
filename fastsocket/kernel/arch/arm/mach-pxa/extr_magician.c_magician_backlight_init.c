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
 int /*<<< orphan*/  EGPIO_MAGICIAN_BL_POWER ; 
 int /*<<< orphan*/  EGPIO_MAGICIAN_BL_POWER2 ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int gpio_request (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int magician_backlight_init(struct device *dev)
{
	int ret;

	ret = gpio_request(EGPIO_MAGICIAN_BL_POWER, "BL_POWER");
	if (ret)
		goto err;
	ret = gpio_request(EGPIO_MAGICIAN_BL_POWER2, "BL_POWER2");
	if (ret)
		goto err2;
	return 0;

err2:
	gpio_free(EGPIO_MAGICIAN_BL_POWER);
err:
	return ret;
}