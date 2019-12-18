#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ds1wm_driver_data {int /*<<< orphan*/  clock_rate; } ;
struct ds1wm_data {TYPE_2__* pdev; TYPE_1__* cell; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable ) (TYPE_2__*) ;struct ds1wm_driver_data* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1WM_CLKDIV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ds1wm_find_divisor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1wm_reset (struct ds1wm_data*) ; 
 int /*<<< orphan*/  ds1wm_write_register (struct ds1wm_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void ds1wm_up(struct ds1wm_data *ds1wm_data)
{
	int divisor;
	struct ds1wm_driver_data *plat = ds1wm_data->cell->driver_data;

	if (ds1wm_data->cell->enable)
		ds1wm_data->cell->enable(ds1wm_data->pdev);

	divisor = ds1wm_find_divisor(plat->clock_rate);
	if (divisor == 0) {
		dev_err(&ds1wm_data->pdev->dev,
			"no suitable divisor for %dHz clock\n",
			plat->clock_rate);
		return;
	}
	ds1wm_write_register(ds1wm_data, DS1WM_CLKDIV, divisor);

	/* Let the w1 clock stabilize. */
	msleep(1);

	ds1wm_reset(ds1wm_data);
}