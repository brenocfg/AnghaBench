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
struct net_device {unsigned char* dev_addr; int /*<<< orphan*/  addr_len; } ;
struct gem {int /*<<< orphan*/  pm_mutex; scalar_t__ regs; scalar_t__ running; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 scalar_t__ MAC_ADDR0 ; 
 scalar_t__ MAC_ADDR1 ; 
 scalar_t__ MAC_ADDR2 ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct gem* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  writel (unsigned char,scalar_t__) ; 

__attribute__((used)) static int gem_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *macaddr = (struct sockaddr *) addr;
	struct gem *gp = netdev_priv(dev);
	unsigned char *e = &dev->dev_addr[0];

	if (!is_valid_ether_addr(macaddr->sa_data))
		return -EADDRNOTAVAIL;

	if (!netif_running(dev) || !netif_device_present(dev)) {
		/* We'll just catch it later when the
		 * device is up'd or resumed.
		 */
		memcpy(dev->dev_addr, macaddr->sa_data, dev->addr_len);
		return 0;
	}

	mutex_lock(&gp->pm_mutex);
	memcpy(dev->dev_addr, macaddr->sa_data, dev->addr_len);
	if (gp->running) {
		writel((e[4] << 8) | e[5], gp->regs + MAC_ADDR0);
		writel((e[2] << 8) | e[3], gp->regs + MAC_ADDR1);
		writel((e[0] << 8) | e[1], gp->regs + MAC_ADDR2);
	}
	mutex_unlock(&gp->pm_mutex);

	return 0;
}