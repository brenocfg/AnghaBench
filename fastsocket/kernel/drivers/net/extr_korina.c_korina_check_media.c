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
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ full_duplex; } ;
struct korina_private {TYPE_1__* eth_regs; TYPE_2__ mii_if; } ;
struct TYPE_3__ {int /*<<< orphan*/  ethmac2; } ;

/* Variables and functions */
 int ETH_MAC2_FD ; 
 int /*<<< orphan*/  mii_check_media (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 struct korina_private* netdev_priv (struct net_device*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void korina_check_media(struct net_device *dev, unsigned int init_media)
{
	struct korina_private *lp = netdev_priv(dev);

	mii_check_media(&lp->mii_if, 0, init_media);

	if (lp->mii_if.full_duplex)
		writel(readl(&lp->eth_regs->ethmac2) | ETH_MAC2_FD,
						&lp->eth_regs->ethmac2);
	else
		writel(readl(&lp->eth_regs->ethmac2) & ~ETH_MAC2_FD,
						&lp->eth_regs->ethmac2);
}