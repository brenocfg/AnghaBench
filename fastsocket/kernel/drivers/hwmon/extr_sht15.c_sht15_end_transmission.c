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
struct sht15_data {TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_sck; int /*<<< orphan*/  gpio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHT15_TSCKH ; 
 int /*<<< orphan*/  SHT15_TSCKL ; 
 int /*<<< orphan*/  SHT15_TSU ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sht15_end_transmission(struct sht15_data *data)
{
	gpio_direction_output(data->pdata->gpio_data, 1);
	ndelay(SHT15_TSU);
	gpio_set_value(data->pdata->gpio_sck, 1);
	ndelay(SHT15_TSCKH);
	gpio_set_value(data->pdata->gpio_sck, 0);
	ndelay(SHT15_TSCKL);
}