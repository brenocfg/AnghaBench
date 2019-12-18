#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* dev; } ;
struct tosa_bat {scalar_t__ gpio_temp; scalar_t__ adc_temp; unsigned long adc_temp_divider; TYPE_3__ psy; } ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bat_lock ; 
 int /*<<< orphan*/  gpio_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long wm97xx_read_aux_adc (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static unsigned long tosa_read_temp(struct tosa_bat *bat)
{
	unsigned long value = 0;

	if (bat->gpio_temp < 0 || bat->adc_temp < 0)
		return 0;

	mutex_lock(&bat_lock);
	gpio_set_value(bat->gpio_temp, 1);
	msleep(5);
	value = wm97xx_read_aux_adc(bat->psy.dev->parent->driver_data,
			bat->adc_temp);
	gpio_set_value(bat->gpio_temp, 0);
	mutex_unlock(&bat_lock);

	value = value * 10000 / bat->adc_temp_divider;

	return value;
}