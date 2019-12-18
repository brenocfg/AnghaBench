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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * evm_sw_gpio ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_unexport (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int evm_sw_teardown(struct i2c_client *client, int gpio,
			unsigned ngpio, void *c)
{
	int i;

	for (i = 0; i < 4; ++i) {
		if (evm_sw_gpio[i] != -EINVAL) {
			gpio_unexport(evm_sw_gpio[i]);
			gpio_free(evm_sw_gpio[i]);
			evm_sw_gpio[i] = -EINVAL;
		}
	}
	return 0;
}