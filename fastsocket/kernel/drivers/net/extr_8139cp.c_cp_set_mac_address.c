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
struct net_device {scalar_t__ dev_addr; int /*<<< orphan*/  addr_len; } ;
struct cp_private {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  Cfg9346 ; 
 int /*<<< orphan*/  Cfg9346_Lock ; 
 int /*<<< orphan*/  Cfg9346_Unlock ; 
 int EADDRNOTAVAIL ; 
 scalar_t__ MAC0 ; 
 int /*<<< orphan*/  cpw32_f (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw8_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cp_set_mac_address(struct net_device *dev, void *p)
{
	struct cp_private *cp = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	spin_lock_irq(&cp->lock);

	cpw8_f(Cfg9346, Cfg9346_Unlock);
	cpw32_f(MAC0 + 0, le32_to_cpu (*(__le32 *) (dev->dev_addr + 0)));
	cpw32_f(MAC0 + 4, le32_to_cpu (*(__le32 *) (dev->dev_addr + 4)));
	cpw8_f(Cfg9346, Cfg9346_Lock);

	spin_unlock_irq(&cp->lock);

	return 0;
}