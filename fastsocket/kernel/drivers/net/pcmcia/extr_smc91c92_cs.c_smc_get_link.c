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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct smc_private {int /*<<< orphan*/  lock; } ;
struct net_device {unsigned int base_addr; } ;

/* Variables and functions */
 scalar_t__ BANK_SELECT ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int inw (scalar_t__) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  smc_link_ok (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 smc_get_link(struct net_device *dev)
{
	struct smc_private *smc = netdev_priv(dev);
	unsigned int ioaddr = dev->base_addr;
	u16 saved_bank = inw(ioaddr + BANK_SELECT);
	u32 ret;

	spin_lock_irq(&smc->lock);
	SMC_SELECT_BANK(3);
	ret = smc_link_ok(dev);
	SMC_SELECT_BANK(saved_bank);
	spin_unlock_irq(&smc->lock);
	return ret;
}