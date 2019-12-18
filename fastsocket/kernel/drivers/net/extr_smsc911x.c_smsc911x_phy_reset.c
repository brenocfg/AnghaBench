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
struct smsc911x_data {struct phy_device* phy_dev; } ;
struct phy_device {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 unsigned int BMCR_RESET ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  SMSC_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SMSC_WARNING (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int smsc911x_mii_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_mii_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int smsc911x_phy_reset(struct smsc911x_data *pdata)
{
	struct phy_device *phy_dev = pdata->phy_dev;
	unsigned int temp;
	unsigned int i = 100000;

	BUG_ON(!phy_dev);
	BUG_ON(!phy_dev->bus);

	SMSC_TRACE(HW, "Performing PHY BCR Reset");
	smsc911x_mii_write(phy_dev->bus, phy_dev->addr, MII_BMCR, BMCR_RESET);
	do {
		msleep(1);
		temp = smsc911x_mii_read(phy_dev->bus, phy_dev->addr,
			MII_BMCR);
	} while ((i--) && (temp & BMCR_RESET));

	if (temp & BMCR_RESET) {
		SMSC_WARNING(HW, "PHY reset failed to complete.");
		return -EIO;
	}
	/* Extra delay required because the phy may not be completed with
	* its reset when BMCR_RESET is cleared. Specs say 256 uS is
	* enough delay but using 1ms here to be safe */
	msleep(1);

	return 0;
}