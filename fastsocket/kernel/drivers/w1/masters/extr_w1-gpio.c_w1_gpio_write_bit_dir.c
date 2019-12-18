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
typedef  scalar_t__ u8 ;
struct w1_gpio_platform_data {int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w1_gpio_write_bit_dir(void *data, u8 bit)
{
	struct w1_gpio_platform_data *pdata = data;

	if (bit)
		gpio_direction_input(pdata->pin);
	else
		gpio_direction_output(pdata->pin, 0);
}