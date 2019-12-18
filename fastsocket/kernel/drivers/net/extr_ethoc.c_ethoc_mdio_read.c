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
struct mii_bus {struct ethoc* priv; } ;
struct ethoc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 unsigned long ETHOC_MII_TIMEOUT ; 
 int /*<<< orphan*/  MIIADDRESS ; 
 int /*<<< orphan*/  MIIADDRESS_ADDR (int,int) ; 
 int /*<<< orphan*/  MIICOMMAND ; 
 int /*<<< orphan*/  MIICOMMAND_READ ; 
 int /*<<< orphan*/  MIIRX_DATA ; 
 int /*<<< orphan*/  MIISTATUS ; 
 int MIISTATUS_BUSY ; 
 int ethoc_read (struct ethoc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethoc_write (struct ethoc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int ethoc_mdio_read(struct mii_bus *bus, int phy, int reg)
{
	unsigned long timeout = jiffies + ETHOC_MII_TIMEOUT;
	struct ethoc *priv = bus->priv;

	ethoc_write(priv, MIIADDRESS, MIIADDRESS_ADDR(phy, reg));
	ethoc_write(priv, MIICOMMAND, MIICOMMAND_READ);

	while (time_before(jiffies, timeout)) {
		u32 status = ethoc_read(priv, MIISTATUS);
		if (!(status & MIISTATUS_BUSY)) {
			u32 data = ethoc_read(priv, MIIRX_DATA);
			/* reset MII command register */
			ethoc_write(priv, MIICOMMAND, 0);
			return data;
		}

		schedule();
	}

	return -EBUSY;
}