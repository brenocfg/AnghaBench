#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct metronomefb_par {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR_GPIO_PIN ; 
 int /*<<< orphan*/  LED_GPIO_PIN ; 
 int /*<<< orphan*/  PCBPWR_GPIO_PIN ; 
 int /*<<< orphan*/  RDY_GPIO_PIN ; 
 int /*<<< orphan*/  RST_GPIO_PIN ; 
 int /*<<< orphan*/  STDBY_GPIO_PIN ; 
 TYPE_1__* am200_device ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpio_names ; 
 int gpio_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpios ; 

__attribute__((used)) static int am200_init_gpio_regs(struct metronomefb_par *par)
{
	int i;
	int err;

	for (i = 0; i < ARRAY_SIZE(gpios); i++) {
		err = gpio_request(gpios[i], gpio_names[i]);
		if (err) {
			dev_err(&am200_device->dev, "failed requesting "
				"gpio %s, err=%d\n", gpio_names[i], err);
			goto err_req_gpio;
		}
	}

	gpio_direction_output(LED_GPIO_PIN, 0);
	gpio_direction_output(STDBY_GPIO_PIN, 0);
	gpio_direction_output(RST_GPIO_PIN, 0);

	gpio_direction_input(RDY_GPIO_PIN);
	gpio_direction_input(ERR_GPIO_PIN);

	gpio_direction_output(PCBPWR_GPIO_PIN, 0);

	return 0;

err_req_gpio:
	while (i > 0)
		gpio_free(gpios[i--]);

	return err;
}