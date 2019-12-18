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
struct vmxnet3_adapter {int dummy; } ;
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmxnet3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vmxnet3_write_mac_addr (struct vmxnet3_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vmxnet3_set_mac_addr(struct net_device *netdev, void *p)
{
	struct sockaddr *addr = p;
	struct vmxnet3_adapter *adapter = netdev_priv(netdev);

	memcpy(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	vmxnet3_write_mac_addr(adapter, addr->sa_data);

	return 0;
}