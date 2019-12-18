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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_pout ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  pout ; 

__attribute__((used)) static int zylonite_resume_pre(struct platform_device *pdev)
{
	int ret = 0;

	if (clk_pout) {
		ret = clk_enable(pout);
		if (ret != 0)
			dev_err(&pdev->dev, "Unable to enable CLK_POUT: %d\n",
				ret);
	}

	return ret;
}