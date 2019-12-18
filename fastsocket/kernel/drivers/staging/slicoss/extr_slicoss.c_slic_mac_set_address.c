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
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct adapter {int /*<<< orphan*/  currmacaddr; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  slic_config_set (struct adapter*,int) ; 

__attribute__((used)) static int slic_mac_set_address(struct net_device *dev, void *ptr)
{
	struct adapter *adapter = (struct adapter *)netdev_priv(dev);
	struct sockaddr *addr = ptr;

	if (netif_running(dev))
		return -EBUSY;
	if (!adapter)
		return -EBUSY;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	memcpy(adapter->currmacaddr, addr->sa_data, dev->addr_len);

	slic_config_set(adapter, true);
	return 0;
}