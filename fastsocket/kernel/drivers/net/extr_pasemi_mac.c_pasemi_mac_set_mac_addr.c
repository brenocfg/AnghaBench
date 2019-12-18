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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct pasemi_mac {int dummy; } ;
struct net_device {int* dev_addr; int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PAS_MAC_CFG_ADR0 ; 
 int /*<<< orphan*/  PAS_MAC_CFG_ADR1 ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pasemi_mac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pasemi_mac_intf_disable (struct pasemi_mac*) ; 
 int /*<<< orphan*/  pasemi_mac_intf_enable (struct pasemi_mac*) ; 
 unsigned int read_mac_reg (struct pasemi_mac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_mac_reg (struct pasemi_mac*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int pasemi_mac_set_mac_addr(struct net_device *dev, void *p)
{
	struct pasemi_mac *mac = netdev_priv(dev);
	struct sockaddr *addr = p;
	unsigned int adr0, adr1;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EINVAL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	adr0 = dev->dev_addr[2] << 24 |
	       dev->dev_addr[3] << 16 |
	       dev->dev_addr[4] << 8 |
	       dev->dev_addr[5];
	adr1 = read_mac_reg(mac, PAS_MAC_CFG_ADR1);
	adr1 &= ~0xffff;
	adr1 |= dev->dev_addr[0] << 8 | dev->dev_addr[1];

	pasemi_mac_intf_disable(mac);
	write_mac_reg(mac, PAS_MAC_CFG_ADR0, adr0);
	write_mac_reg(mac, PAS_MAC_CFG_ADR1, adr1);
	pasemi_mac_intf_enable(mac);

	return 0;
}