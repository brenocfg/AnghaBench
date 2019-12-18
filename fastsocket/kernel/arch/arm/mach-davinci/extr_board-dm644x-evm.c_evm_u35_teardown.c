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
 int /*<<< orphan*/  gpio_free (int) ; 

__attribute__((used)) static int
evm_u35_teardown(struct i2c_client *client, int gpio, unsigned ngpio, void *c)
{
	gpio_free(gpio + 7);
	gpio_free(gpio + 6);
	gpio_free(gpio + 5);
	gpio_free(gpio + 3);
	gpio_free(gpio + 2);
	gpio_free(gpio + 1);
	gpio_free(gpio + 0);
	return 0;
}