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
struct phy_device {scalar_t__ duplex; int /*<<< orphan*/  speed; scalar_t__ link; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

void phy_print_status(struct phy_device *phydev)
{
	pr_info("PHY: %s - Link is %s", dev_name(&phydev->dev),
			phydev->link ? "Up" : "Down");
	if (phydev->link)
		printk(" - %d/%s", phydev->speed,
				DUPLEX_FULL == phydev->duplex ?
				"Full" : "Half");

	printk("\n");
}