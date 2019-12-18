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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  board_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  BMCR_RESET ; 
 int /*<<< orphan*/  DM9000_GPR ; 
 int /*<<< orphan*/  DM9000_IMR ; 
 int /*<<< orphan*/  DM9000_RCR ; 
 int IMR_PAR ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  dm9000_phy_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iow (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
dm9000_shutdown(struct net_device *dev)
{
	board_info_t *db = netdev_priv(dev);

	/* RESET device */
	dm9000_phy_write(dev, 0, MII_BMCR, BMCR_RESET);	/* PHY RESET */
	iow(db, DM9000_GPR, 0x01);	/* Power-Down PHY */
	iow(db, DM9000_IMR, IMR_PAR);	/* Disable all interrupt */
	iow(db, DM9000_RCR, 0x00);	/* Disable RX */
}