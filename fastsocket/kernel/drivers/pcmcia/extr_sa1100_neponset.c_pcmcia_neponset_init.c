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
struct sa1111_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int GPIO_A0 ; 
 int GPIO_A1 ; 
 int GPIO_A2 ; 
 int GPIO_A3 ; 
 scalar_t__ machine_is_assabet () ; 
 int /*<<< orphan*/  neponset_pcmcia_ops ; 
 int /*<<< orphan*/  sa1111_set_io (struct sa1111_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_io_dir (struct sa1111_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa1111_set_sleep_io (struct sa1111_dev*,int,int /*<<< orphan*/ ) ; 
 int sa11xx_drv_pcmcia_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pcmcia_neponset_init(struct sa1111_dev *sadev)
{
	int ret = -ENODEV;

	if (machine_is_assabet()) {
		/*
		 * Set GPIO_A<3:0> to be outputs for the MAX1600,
		 * and switch to standby mode.
		 */
		sa1111_set_io_dir(sadev, GPIO_A0|GPIO_A1|GPIO_A2|GPIO_A3, 0, 0);
		sa1111_set_io(sadev, GPIO_A0|GPIO_A1|GPIO_A2|GPIO_A3, 0);
		sa1111_set_sleep_io(sadev, GPIO_A0|GPIO_A1|GPIO_A2|GPIO_A3, 0);
		ret = sa11xx_drv_pcmcia_probe(&sadev->dev, &neponset_pcmcia_ops, 0, 2);
	}

	return ret;
}