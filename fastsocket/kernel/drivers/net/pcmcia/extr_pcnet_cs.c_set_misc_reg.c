#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct net_device {unsigned int base_addr; int if_port; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  eth_phy; int /*<<< orphan*/  mii_reset; } ;
typedef  TYPE_1__ pcnet_dev_t ;

/* Variables and functions */
 scalar_t__ DLINK_DIAG ; 
 scalar_t__ DLINK_GPIO ; 
 int HAS_IBM_MISC ; 
 int HAS_MII ; 
 int HAS_MISC_REG ; 
 int IS_DL10019 ; 
 int IS_DL10022 ; 
 scalar_t__ PCNET_MISC ; 
 TYPE_1__* PRIV (struct net_device*) ; 
 int USE_BIG_BUF ; 
 scalar_t__ full_duplex ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mdio_write (scalar_t__,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static void set_misc_reg(struct net_device *dev)
{
    unsigned int nic_base = dev->base_addr;
    pcnet_dev_t *info = PRIV(dev);
    u_char tmp;

    if (info->flags & HAS_MISC_REG) {
	tmp = inb_p(nic_base + PCNET_MISC) & ~3;
	if (dev->if_port == 2)
	    tmp |= 1;
	if (info->flags & USE_BIG_BUF)
	    tmp |= 2;
	if (info->flags & HAS_IBM_MISC)
	    tmp |= 8;
	outb_p(tmp, nic_base + PCNET_MISC);
    }
    if (info->flags & IS_DL10022) {
	if (info->flags & HAS_MII) {
	    /* Advertise 100F, 100H, 10F, 10H */
	    mdio_write(nic_base + DLINK_GPIO, info->eth_phy, 4, 0x01e1);
	    /* Restart MII autonegotiation */
	    mdio_write(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x0000);
	    mdio_write(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x1200);
	    info->mii_reset = jiffies;
	} else {
	    outb(full_duplex ? 4 : 0, nic_base + DLINK_DIAG);
	}
    } else if (info->flags & IS_DL10019) {
	/* Advertise 100F, 100H, 10F, 10H */
	mdio_write(nic_base + DLINK_GPIO, info->eth_phy, 4, 0x01e1);
	/* Restart MII autonegotiation */
	mdio_write(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x0000);
	mdio_write(nic_base + DLINK_GPIO, info->eth_phy, 0, 0x1200);
    }
}