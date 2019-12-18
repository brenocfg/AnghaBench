#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct gpio_led {int /*<<< orphan*/  gpio; } ;
struct TYPE_7__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_8__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  evm_led_data ; 
 TYPE_2__* evm_led_dev ; 
 struct gpio_led* evm_leds ; 
 int platform_device_add (TYPE_2__*) ; 
 int /*<<< orphan*/  platform_device_add_data (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_put (TYPE_2__*) ; 

__attribute__((used)) static int
evm_led_setup(struct i2c_client *client, int gpio, unsigned ngpio, void *c)
{
	struct gpio_led *leds = evm_leds;
	int status;

	while (ngpio--) {
		leds->gpio = gpio++;
		leds++;
	}

	/* what an extremely annoying way to be forced to handle
	 * device unregistration ...
	 */
	evm_led_dev = platform_device_alloc("leds-gpio", 0);
	platform_device_add_data(evm_led_dev,
			&evm_led_data, sizeof evm_led_data);

	evm_led_dev->dev.parent = &client->dev;
	status = platform_device_add(evm_led_dev);
	if (status < 0) {
		platform_device_put(evm_led_dev);
		evm_led_dev = NULL;
	}
	return status;
}