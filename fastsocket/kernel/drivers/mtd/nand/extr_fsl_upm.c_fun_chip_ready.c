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
struct mtd_info {int dummy; } ;
struct fsl_upm_nand {size_t mchip_number; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rnb_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 struct fsl_upm_nand* to_fsl_upm_nand (struct mtd_info*) ; 

__attribute__((used)) static int fun_chip_ready(struct mtd_info *mtd)
{
	struct fsl_upm_nand *fun = to_fsl_upm_nand(mtd);

	if (gpio_get_value(fun->rnb_gpio[fun->mchip_number]))
		return 1;

	dev_vdbg(fun->dev, "busy\n");
	return 0;
}