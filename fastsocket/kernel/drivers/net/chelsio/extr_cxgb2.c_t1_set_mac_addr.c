#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {size_t if_port; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/  addr_len; struct adapter* ml_priv; } ;
struct cmac {TYPE_2__* ops; } ;
struct adapter {TYPE_1__* port; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* macaddress_set ) (struct cmac*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct cmac* mac; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cmac*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int t1_set_mac_addr(struct net_device *dev, void *p)
{
	struct adapter *adapter = dev->ml_priv;
	struct cmac *mac = adapter->port[dev->if_port].mac;
	struct sockaddr *addr = p;

	if (!mac->ops->macaddress_set)
		return -EOPNOTSUPP;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	mac->ops->macaddress_set(mac, dev->dev_addr);
	return 0;
}