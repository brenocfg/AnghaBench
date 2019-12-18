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
struct driver_data {TYPE_1__* pdev; struct chip_data* cur_chip; } ;
struct chip_data {int /*<<< orphan*/  baud; int /*<<< orphan*/  ctl_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_STAT_CLR ; 
 int /*<<< orphan*/  bfin_spi_cs_active (struct driver_data*,struct chip_data*) ; 
 int /*<<< orphan*/  bfin_spi_disable (struct driver_data*) ; 
 int /*<<< orphan*/  bfin_spi_enable (struct driver_data*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_BAUD (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_CTRL (struct driver_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_STAT (struct driver_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bfin_spi_restore_state(struct driver_data *drv_data)
{
	struct chip_data *chip = drv_data->cur_chip;

	/* Clear status and disable clock */
	write_STAT(drv_data, BIT_STAT_CLR);
	bfin_spi_disable(drv_data);
	dev_dbg(&drv_data->pdev->dev, "restoring spi ctl state\n");

	/* Load the registers */
	write_CTRL(drv_data, chip->ctl_reg);
	write_BAUD(drv_data, chip->baud);

	bfin_spi_enable(drv_data);
	bfin_spi_cs_active(drv_data, chip);
}