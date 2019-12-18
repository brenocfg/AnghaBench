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
struct gpio_ress {int gpio; int dir; int /*<<< orphan*/  init; int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_input (int) ; 
 int /*<<< orphan*/  gpio_direction_output (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int) ; 
 int gpio_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hx4700_gpio_request(struct gpio_ress *gpios, int size)
{
	int i, rc = 0;
	int gpio;
	int dir;

	for (i = 0; (!rc) && (i < size); i++) {
		gpio = gpios[i].gpio;
		dir = gpios[i].dir;
		rc = gpio_request(gpio, gpios[i].desc);
		if (rc) {
			pr_err("Error requesting GPIO %d(%s) : %d\n",
			       gpio, gpios[i].desc, rc);
			continue;
		}
		if (dir)
			gpio_direction_output(gpio, gpios[i].init);
		else
			gpio_direction_input(gpio);
	}
	while ((rc) && (--i >= 0))
		gpio_free(gpios[i].gpio);
	return rc;
}