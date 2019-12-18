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
struct TYPE_2__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct plat_stmmacphy_data {int /*<<< orphan*/  bus_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stmmacphy_dvr_probe(struct platform_device *pdev)
{
	struct plat_stmmacphy_data *plat_dat;
	plat_dat = (struct plat_stmmacphy_data *)((pdev->dev).platform_data);

	pr_debug("stmmacphy_dvr_probe: added phy for bus %d\n",
	       plat_dat->bus_id);

	return 0;
}