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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mii_bus {struct ethoc* priv; } ;
struct ethoc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned long ETHOC_MII_TIMEOUT ; 
 int /*<<< orphan*/  MIIADDRESS ; 
 int /*<<< orphan*/  MIIADDRESS_ADDR (int,int) ; 
 int /*<<< orphan*/  MIICOMMAND ; 
 int /*<<< orphan*/  MIICOMMAND_WRITE ; 
 int /*<<< orphan*/  MIISTATUS ; 
 int MIISTATUS_BUSY ; 
 int /*<<< orphan*/  MIITX_DATA ; 
 int ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_write (struct ethoc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ethoc_mdio_write(struct mii_bus *bus, int phy, int reg, u16 val)
{
	unsigned long timeout = jiffies + ETHOC_MII_TIMEOUT;
	struct ethoc *priv = bus->priv;

	ethoc_write(priv, MIIADDRESS, MIIADDRESS_ADDR(phy, reg));
	ethoc_write(priv, MIITX_DATA, val);
	ethoc_write(priv, MIICOMMAND, MIICOMMAND_WRITE);

	while (time_before(jiffies, timeout)) {
		u32 stat = ethoc_read(priv, MIISTATUS);
		if (!(stat & MIISTATUS_BUSY))
			return 0;

		schedule();
	}

	return -EBUSY;
}