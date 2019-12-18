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
struct spider_net_card {int dummy; } ;
struct sockaddr {int* sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  SPIDER_NET_GMACOPEMD ; 
 int /*<<< orphan*/  SPIDER_NET_GMACUNIMACL ; 
 int /*<<< orphan*/  SPIDER_NET_GMACUNIMACU ; 
 int /*<<< orphan*/  is_valid_ether_addr (int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 scalar_t__ spider_net_get_mac_address (struct net_device*) ; 
 int spider_net_read_reg (struct spider_net_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spider_net_set_promisc (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
spider_net_set_mac(struct net_device *netdev, void *p)
{
	struct spider_net_card *card = netdev_priv(netdev);
	u32 macl, macu, regvalue;
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	/* switch off GMACTPE and GMACRPE */
	regvalue = spider_net_read_reg(card, SPIDER_NET_GMACOPEMD);
	regvalue &= ~((1 << 5) | (1 << 6));
	spider_net_write_reg(card, SPIDER_NET_GMACOPEMD, regvalue);

	/* write mac */
	macu = (addr->sa_data[0]<<24) + (addr->sa_data[1]<<16) +
		(addr->sa_data[2]<<8) + (addr->sa_data[3]);
	macl = (addr->sa_data[4]<<8) + (addr->sa_data[5]);
	spider_net_write_reg(card, SPIDER_NET_GMACUNIMACU, macu);
	spider_net_write_reg(card, SPIDER_NET_GMACUNIMACL, macl);

	/* switch GMACTPE and GMACRPE back on */
	regvalue = spider_net_read_reg(card, SPIDER_NET_GMACOPEMD);
	regvalue |= ((1 << 5) | (1 << 6));
	spider_net_write_reg(card, SPIDER_NET_GMACOPEMD, regvalue);

	spider_net_set_promisc(card);

	/* look up, whether we have been successful */
	if (spider_net_get_mac_address(netdev))
		return -EADDRNOTAVAIL;
	if (memcmp(netdev->dev_addr,addr->sa_data,netdev->addr_len))
		return -EADDRNOTAVAIL;

	return 0;
}