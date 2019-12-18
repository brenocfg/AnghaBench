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
 size_t ASIC3_CLOCK_OWM ; 
 int /*<<< orphan*/  ASIC3_EXTCF_OWM_EN ; 
 int /*<<< orphan*/  ASIC3_EXTCF_OWM_RESET ; 
 int /*<<< orphan*/  ASIC3_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTCF ; 
 int /*<<< orphan*/  RESET ; 
 int /*<<< orphan*/  SELECT ; 
 int /*<<< orphan*/  asic3_clk_enable (struct asic3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asic3_set_register (struct asic3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct asic3* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int ds1wm_enable(struct platform_device *pdev)
{
	struct asic3 *asic = dev_get_drvdata(pdev->dev.parent);

	/* Turn on external clocks and the OWM clock */
	asic3_clk_enable(asic, &asic->clocks[ASIC3_CLOCK_EX0]);
	asic3_clk_enable(asic, &asic->clocks[ASIC3_CLOCK_EX1]);
	asic3_clk_enable(asic, &asic->clocks[ASIC3_CLOCK_OWM]);
	msleep(1);

	/* Reset and enable DS1WM */
	asic3_set_register(asic, ASIC3_OFFSET(EXTCF, RESET),
			   ASIC3_EXTCF_OWM_RESET, 1);
	msleep(1);
	asic3_set_register(asic, ASIC3_OFFSET(EXTCF, RESET),
			   ASIC3_EXTCF_OWM_RESET, 0);
	msleep(1);
	asic3_set_register(asic, ASIC3_OFFSET(EXTCF, SELECT),
			   ASIC3_EXTCF_OWM_EN, 1);
	msleep(1);

	return 0;
}