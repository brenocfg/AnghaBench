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
struct usbnet {TYPE_1__* net; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_MAC_OFFSET ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  devdbg (struct usbnet*,char*) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_ifup (struct usbnet*) ; 
 int /*<<< orphan*/  random_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ smsc95xx_read_eeprom (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smsc95xx_init_mac_address(struct usbnet *dev)
{
	/* try reading mac address from EEPROM */
	if (smsc95xx_read_eeprom(dev, EEPROM_MAC_OFFSET, ETH_ALEN,
			dev->net->dev_addr) == 0) {
		if (is_valid_ether_addr(dev->net->dev_addr)) {
			/* eeprom values are valid so use them */
			if (netif_msg_ifup(dev))
				devdbg(dev, "MAC address read from EEPROM");
			return;
		}
	}

	/* no eeprom, or eeprom values are invalid. generate random MAC */
	random_ether_addr(dev->net->dev_addr);
	if (netif_msg_ifup(dev))
		devdbg(dev, "MAC address set to random_ether_addr");
}