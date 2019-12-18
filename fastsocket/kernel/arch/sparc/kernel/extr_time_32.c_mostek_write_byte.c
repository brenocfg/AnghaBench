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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_2__ {struct m48t59_plat_data* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct m48t59_plat_data {scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct platform_device* to_platform_device (struct device*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mostek_write_byte(struct device *dev, u32 ofs, u8 val)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct m48t59_plat_data *pdata = pdev->dev.platform_data;

	writeb(val, pdata->ioaddr + ofs);
}