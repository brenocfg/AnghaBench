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
struct apanel {int /*<<< orphan*/  ipdev; int /*<<< orphan*/  mail_led; } ;

/* Variables and functions */
 size_t APANEL_DEV_LED ; 
 scalar_t__ CHIP_NONE ; 
 scalar_t__* device_chip ; 
 struct apanel* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  input_free_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_unregister_polled_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_classdev_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apanel_remove(struct i2c_client *client)
{
	struct apanel *ap = i2c_get_clientdata(client);

	if (device_chip[APANEL_DEV_LED] != CHIP_NONE)
		led_classdev_unregister(&ap->mail_led);

	input_unregister_polled_device(ap->ipdev);
	input_free_polled_device(ap->ipdev);

	return 0;
}