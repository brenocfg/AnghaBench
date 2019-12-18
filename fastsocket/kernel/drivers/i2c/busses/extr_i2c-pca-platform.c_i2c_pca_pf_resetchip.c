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
struct i2c_pca_pf_data {int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static void i2c_pca_pf_resetchip(void *pd)
{
	struct i2c_pca_pf_data *i2c = pd;

	gpio_set_value(i2c->gpio, 0);
	ndelay(100);
	gpio_set_value(i2c->gpio, 1);
}