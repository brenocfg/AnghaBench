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
struct sht15_data {TYPE_1__* pdata; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  gpio_sck; int /*<<< orphan*/  gpio_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  SHT15_TSCKH ; 
 int /*<<< orphan*/  SHT15_TSCKL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpio_direction_input (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sht15_connection_reset (struct sht15_data*) ; 

__attribute__((used)) static int sht15_wait_for_response(struct sht15_data *data)
{
	gpio_direction_input(data->pdata->gpio_data);
	gpio_set_value(data->pdata->gpio_sck, 1);
	ndelay(SHT15_TSCKH);
	if (gpio_get_value(data->pdata->gpio_data)) {
		gpio_set_value(data->pdata->gpio_sck, 0);
		dev_err(data->dev, "Command not acknowledged\n");
		sht15_connection_reset(data);
		return -EIO;
	}
	gpio_set_value(data->pdata->gpio_sck, 0);
	ndelay(SHT15_TSCKL);
	return 0;
}