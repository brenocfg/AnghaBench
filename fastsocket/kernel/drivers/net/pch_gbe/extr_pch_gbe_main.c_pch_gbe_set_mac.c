#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_8__ {TYPE_3__* reg; TYPE_1__ mac; } ;
struct pch_gbe_adapter {TYPE_4__ hw; } ;
struct net_device {int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_len; } ;
struct TYPE_7__ {TYPE_2__* mac_adr; } ;
struct TYPE_6__ {int /*<<< orphan*/  low; int /*<<< orphan*/  high; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_gbe_mac_mar_set (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 

__attribute__((used)) static int pch_gbe_set_mac(struct net_device *netdev, void *addr)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct sockaddr *skaddr = addr;
	int ret_val;

	if (!is_valid_ether_addr(skaddr->sa_data)) {
		ret_val = -EADDRNOTAVAIL;
	} else {
		memcpy(netdev->dev_addr, skaddr->sa_data, netdev->addr_len);
		memcpy(adapter->hw.mac.addr, skaddr->sa_data, netdev->addr_len);
		pch_gbe_mac_mar_set(&adapter->hw, adapter->hw.mac.addr, 0);
		ret_val = 0;
	}
	pr_debug("ret_val : 0x%08x\n", ret_val);
	pr_debug("dev_addr : %pM\n", netdev->dev_addr);
	pr_debug("mac_addr : %pM\n", adapter->hw.mac.addr);
	pr_debug("MAC_ADR1AB reg : 0x%08x 0x%08x\n",
		 ioread32(&adapter->hw.reg->mac_adr[0].high),
		 ioread32(&adapter->hw.reg->mac_adr[0].low));
	return ret_val;
}