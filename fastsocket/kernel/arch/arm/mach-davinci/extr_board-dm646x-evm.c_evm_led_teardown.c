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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * evm_led_dev ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int evm_led_teardown(struct i2c_client *client, int gpio,
				unsigned ngpio, void *c)
{
	if (evm_led_dev) {
		platform_device_unregister(evm_led_dev);
		evm_led_dev = NULL;
	}
	return 0;
}