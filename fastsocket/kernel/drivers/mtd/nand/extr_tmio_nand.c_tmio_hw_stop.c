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
struct tmio_nand {scalar_t__ fcr; } ;
struct TYPE_2__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mfd_cell {int /*<<< orphan*/  (* disable ) (struct platform_device*) ;} ;

/* Variables and functions */
 scalar_t__ FCR_MODE ; 
 int /*<<< orphan*/  FCR_MODE_POWER_OFF ; 
 int /*<<< orphan*/  stub1 (struct platform_device*) ; 
 int /*<<< orphan*/  tmio_iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tmio_hw_stop(struct platform_device *dev, struct tmio_nand *tmio)
{
	struct mfd_cell *cell = (struct mfd_cell *)dev->dev.platform_data;

	tmio_iowrite8(FCR_MODE_POWER_OFF, tmio->fcr + FCR_MODE);
	if (cell->disable)
		cell->disable(dev);
}