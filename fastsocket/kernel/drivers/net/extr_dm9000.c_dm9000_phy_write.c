#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  addr_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  io_addr; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_EPAR ; 
 int /*<<< orphan*/  DM9000_EPCR ; 
 int /*<<< orphan*/  DM9000_EPDRH ; 
 int /*<<< orphan*/  DM9000_EPDRL ; 
 int DM9000_PHY ; 
 int EPCR_EPOS ; 
 int EPCR_ERPRW ; 
 int /*<<< orphan*/  dm9000_dbg (TYPE_1__*,int,char*,int,int) ; 
 int /*<<< orphan*/  dm9000_msleep (TYPE_1__*,int) ; 
 int /*<<< orphan*/  iow (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 unsigned long readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeb (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dm9000_phy_write(struct net_device *dev,
		 int phyaddr_unused, int reg, int value)
{
	board_info_t *db = netdev_priv(dev);
	unsigned long flags;
	unsigned long reg_save;

	dm9000_dbg(db, 5, "phy_write[%02x] = %04x\n", reg, value);
	mutex_lock(&db->addr_lock);

	spin_lock_irqsave(&db->lock,flags);

	/* Save previous register address */
	reg_save = readb(db->io_addr);

	/* Fill the phyxcer register into REG_0C */
	iow(db, DM9000_EPAR, DM9000_PHY | reg);

	/* Fill the written data into REG_0D & REG_0E */
	iow(db, DM9000_EPDRL, value);
	iow(db, DM9000_EPDRH, value >> 8);

	iow(db, DM9000_EPCR, EPCR_EPOS | EPCR_ERPRW);	/* Issue phyxcer write command */

	writeb(reg_save, db->io_addr);
	spin_unlock_irqrestore(&db->lock, flags);

	dm9000_msleep(db, 1);		/* Wait write complete */

	spin_lock_irqsave(&db->lock,flags);
	reg_save = readb(db->io_addr);

	iow(db, DM9000_EPCR, 0x0);	/* Clear phyxcer write command */

	/* restore the previous address */
	writeb(reg_save, db->io_addr);

	spin_unlock_irqrestore(&db->lock, flags);
	mutex_unlock(&db->addr_lock);
}