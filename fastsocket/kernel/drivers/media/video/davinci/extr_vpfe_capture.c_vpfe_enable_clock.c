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
struct vpfe_device {TYPE_1__* pdev; struct vpfe_config* cfg; } ;
struct vpfe_config {int /*<<< orphan*/ * slaveclk; int /*<<< orphan*/ * vpssclk; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ clk_enable (int /*<<< orphan*/ *) ; 
 void* clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vpfe_enable_clock(struct vpfe_device *vpfe_dev)
{
	struct vpfe_config *vpfe_cfg = vpfe_dev->cfg;
	int ret = -ENOENT;

	vpfe_cfg->vpssclk = clk_get(vpfe_dev->pdev, "vpss_master");
	if (NULL == vpfe_cfg->vpssclk) {
		v4l2_err(vpfe_dev->pdev->driver, "No clock defined for"
			 "vpss_master\n");
		return ret;
	}

	if (clk_enable(vpfe_cfg->vpssclk)) {
		v4l2_err(vpfe_dev->pdev->driver,
			"vpfe vpss master clock not enabled\n");
		goto out;
	}
	v4l2_info(vpfe_dev->pdev->driver,
		 "vpfe vpss master clock enabled\n");

	vpfe_cfg->slaveclk = clk_get(vpfe_dev->pdev, "vpss_slave");
	if (NULL == vpfe_cfg->slaveclk) {
		v4l2_err(vpfe_dev->pdev->driver,
			"No clock defined for vpss slave\n");
		goto out;
	}

	if (clk_enable(vpfe_cfg->slaveclk)) {
		v4l2_err(vpfe_dev->pdev->driver,
			 "vpfe vpss slave clock not enabled\n");
		goto out;
	}
	v4l2_info(vpfe_dev->pdev->driver, "vpfe vpss slave clock enabled\n");
	return 0;
out:
	if (vpfe_cfg->vpssclk)
		clk_put(vpfe_cfg->vpssclk);
	if (vpfe_cfg->slaveclk)
		clk_put(vpfe_cfg->slaveclk);

	return -1;
}