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
struct sm501_platdata_gpio_i2c {int /*<<< orphan*/  pin_scl; int /*<<< orphan*/  pin_sda; int /*<<< orphan*/  bus_num; int /*<<< orphan*/  udelay; int /*<<< orphan*/  timeout; } ;
struct sm501_devdata {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct i2c_gpio_platform_data* platform_data; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct i2c_gpio_platform_data {void* scl_pin; void* sda_pin; int /*<<< orphan*/  udelay; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct platform_device* sm501_create_subdev (struct sm501_devdata*,char*,int /*<<< orphan*/ ,int) ; 
 void* sm501_gpio_pin2nr (struct sm501_devdata*,int /*<<< orphan*/ ) ; 
 int sm501_register_device (struct sm501_devdata*,struct platform_device*) ; 

__attribute__((used)) static int sm501_register_gpio_i2c_instance(struct sm501_devdata *sm,
					    struct sm501_platdata_gpio_i2c *iic)
{
	struct i2c_gpio_platform_data *icd;
	struct platform_device *pdev;

	pdev = sm501_create_subdev(sm, "i2c-gpio", 0,
				   sizeof(struct i2c_gpio_platform_data));
	if (!pdev)
		return -ENOMEM;

	icd = pdev->dev.platform_data;

	/* We keep the pin_sda and pin_scl fields relative in case the
	 * same platform data is passed to >1 SM501.
	 */

	icd->sda_pin = sm501_gpio_pin2nr(sm, iic->pin_sda);
	icd->scl_pin = sm501_gpio_pin2nr(sm, iic->pin_scl);
	icd->timeout = iic->timeout;
	icd->udelay = iic->udelay;

	/* note, we can't use either of the pin numbers, as the i2c-gpio
	 * driver uses the platform.id field to generate the bus number
	 * to register with the i2c core; The i2c core doesn't have enough
	 * entries to deal with anything we currently use.
	*/

	pdev->id = iic->bus_num;

	dev_info(sm->dev, "registering i2c-%d: sda=%d (%d), scl=%d (%d)\n",
		 iic->bus_num,
		 icd->sda_pin, iic->pin_sda, icd->scl_pin, iic->pin_scl);

	return sm501_register_device(sm, pdev);
}