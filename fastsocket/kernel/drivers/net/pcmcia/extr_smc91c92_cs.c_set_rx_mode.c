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
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct smc_private {int /*<<< orphan*/  lock; } ;
struct net_device {unsigned int base_addr; int flags; int /*<<< orphan*/  mc_list; scalar_t__ mc_count; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ MULTICAST0 ; 
 scalar_t__ MULTICAST4 ; 
 scalar_t__ RCR ; 
 int RxAllMulti ; 
 int RxEnable ; 
 int RxPromisc ; 
 int RxStripCRC ; 
 int /*<<< orphan*/  SMC_SELECT_BANK (int) ; 
 int /*<<< orphan*/  fill_multicast_tbl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct smc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void set_rx_mode(struct net_device *dev)
{
    unsigned int ioaddr = dev->base_addr;
    struct smc_private *smc = netdev_priv(dev);
    u_int multicast_table[ 2 ] = { 0, };
    unsigned long flags;
    u_short rx_cfg_setting;

    if (dev->flags & IFF_PROMISC) {
	rx_cfg_setting = RxStripCRC | RxEnable | RxPromisc | RxAllMulti;
    } else if (dev->flags & IFF_ALLMULTI)
	rx_cfg_setting = RxStripCRC | RxEnable | RxAllMulti;
    else {
	if (dev->mc_count)  {
	    fill_multicast_tbl(dev->mc_count, dev->mc_list,
			       (u_char *)multicast_table);
	}
	rx_cfg_setting = RxStripCRC | RxEnable;
    }

    /* Load MC table and Rx setting into the chip without interrupts. */
    spin_lock_irqsave(&smc->lock, flags);
    SMC_SELECT_BANK(3);
    outl(multicast_table[0], ioaddr + MULTICAST0);
    outl(multicast_table[1], ioaddr + MULTICAST4);
    SMC_SELECT_BANK(0);
    outw(rx_cfg_setting, ioaddr + RCR);
    SMC_SELECT_BANK(2);
    spin_unlock_irqrestore(&smc->lock, flags);

    return;
}