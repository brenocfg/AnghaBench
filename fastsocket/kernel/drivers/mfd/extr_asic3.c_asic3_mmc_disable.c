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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct asic3 {int /*<<< orphan*/ * clocks; } ;

/* Variables and functions */
 size_t ASIC3_CLOCK_EX0 ; 
 size_t ASIC3_CLOCK_EX1 ; 
 size_t ASIC3_CLOCK_SD_BUS ; 
 size_t ASIC3_CLOCK_SD_HOST ; 
 int /*<<< orphan*/  ASIC3_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASIC3_SDHWCTRL_SUSPEND ; 
 int /*<<< orphan*/  SDCONF ; 
 int /*<<< orphan*/  SDHWCTRL ; 
 int /*<<< orphan*/  asic3_clk_disable (struct asic3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asic3_set_register (struct asic3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct asic3* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asic3_mmc_disable(struct platform_device *pdev)
{
	struct asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	/* Put in suspend mode */
	asic3_set_register(asic, ASIC3_OFFSET(SDHWCTRL, SDCONF),
			   ASIC3_SDHWCTRL_SUSPEND, 1);

	/* Disable clocks */
	asic3_clk_disable(asic, &asic->clocks[ASIC3_CLOCK_SD_HOST]);
	asic3_clk_disable(asic, &asic->clocks[ASIC3_CLOCK_SD_BUS]);
	asic3_clk_disable(asic, &asic->clocks[ASIC3_CLOCK_EX0]);
	asic3_clk_disable(asic, &asic->clocks[ASIC3_CLOCK_EX1]);
	return 0;
}