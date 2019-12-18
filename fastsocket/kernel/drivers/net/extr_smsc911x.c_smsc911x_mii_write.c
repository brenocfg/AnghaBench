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
typedef  unsigned int u16 ;
struct smsc911x_data {int /*<<< orphan*/  mac_lock; } ;
struct mii_bus {scalar_t__ priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  MII_ACC ; 
 int MII_ACC_MII_BUSY_ ; 
 int MII_ACC_MII_WRITE_ ; 
 int /*<<< orphan*/  MII_DATA ; 
 int /*<<< orphan*/  SMSC_WARNING (int /*<<< orphan*/ ,char*) ; 
 int smsc911x_mac_read (struct smsc911x_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc911x_mac_write (struct smsc911x_data*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smsc911x_mii_write(struct mii_bus *bus, int phyaddr, int regidx,
			   u16 val)
{
	struct smsc911x_data *pdata = (struct smsc911x_data *)bus->priv;
	unsigned long flags;
	unsigned int addr;
	int i, reg;

	spin_lock_irqsave(&pdata->mac_lock, flags);

	/* Confirm MII not busy */
	if (unlikely(smsc911x_mac_read(pdata, MII_ACC) & MII_ACC_MII_BUSY_)) {
		SMSC_WARNING(HW,
			"MII is busy in smsc911x_mii_write???");
		reg = -EIO;
		goto out;
	}

	/* Put the data to write in the MAC */
	smsc911x_mac_write(pdata, MII_DATA, val);

	/* Set the address, index & direction (write to PHY) */
	addr = ((phyaddr & 0x1F) << 11) | ((regidx & 0x1F) << 6) |
		MII_ACC_MII_WRITE_;
	smsc911x_mac_write(pdata, MII_ACC, addr);

	/* Wait for write to complete w/ timeout */
	for (i = 0; i < 100; i++)
		if (!(smsc911x_mac_read(pdata, MII_ACC) & MII_ACC_MII_BUSY_)) {
			reg = 0;
			goto out;
		}

	SMSC_WARNING(HW, "Timed out waiting for MII write to finish");
	reg = -EIO;

out:
	spin_unlock_irqrestore(&pdata->mac_lock, flags);
	return reg;
}