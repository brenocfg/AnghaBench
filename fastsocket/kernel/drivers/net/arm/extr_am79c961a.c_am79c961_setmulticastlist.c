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
struct net_device {int flags; int /*<<< orphan*/  base_addr; struct dev_mc_list* mc_list; } ;
struct dev_priv {int /*<<< orphan*/  chip_lock; } ;
struct dev_mc_list {struct dev_mc_list* next; } ;
typedef  int /*<<< orphan*/  multi_hash ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned short*) ; 
 scalar_t__ CSR0 ; 
 unsigned short CSR0_STOP ; 
 scalar_t__ CTRL1 ; 
 unsigned short CTRL1_SPND ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ LADRL ; 
 scalar_t__ MODE ; 
 unsigned short MODE_PORT_10BT ; 
 unsigned short MODE_PROMISC ; 
 int /*<<< orphan*/  am79c961_mc_hash (struct dev_mc_list*,unsigned short*) ; 
 int /*<<< orphan*/  memset (unsigned short*,int,int) ; 
 struct dev_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nop () ; 
 unsigned short read_rreg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_rreg (int /*<<< orphan*/ ,scalar_t__,unsigned short) ; 

__attribute__((used)) static void am79c961_setmulticastlist (struct net_device *dev)
{
	struct dev_priv *priv = netdev_priv(dev);
	unsigned long flags;
	unsigned short multi_hash[4], mode;
	int i, stopped;

	mode = MODE_PORT_10BT;

	if (dev->flags & IFF_PROMISC) {
		mode |= MODE_PROMISC;
	} else if (dev->flags & IFF_ALLMULTI) {
		memset(multi_hash, 0xff, sizeof(multi_hash));
	} else {
		struct dev_mc_list *dmi;

		memset(multi_hash, 0x00, sizeof(multi_hash));

		for (dmi = dev->mc_list; dmi; dmi = dmi->next)
			am79c961_mc_hash(dmi, multi_hash);
	}

	spin_lock_irqsave(&priv->chip_lock, flags);

	stopped = read_rreg(dev->base_addr, CSR0) & CSR0_STOP;

	if (!stopped) {
		/*
		 * Put the chip into suspend mode
		 */
		write_rreg(dev->base_addr, CTRL1, CTRL1_SPND);

		/*
		 * Spin waiting for chip to report suspend mode
		 */
		while ((read_rreg(dev->base_addr, CTRL1) & CTRL1_SPND) == 0) {
			spin_unlock_irqrestore(&priv->chip_lock, flags);
			nop();
			spin_lock_irqsave(&priv->chip_lock, flags);
		}
	}

	/*
	 * Update the multicast hash table
	 */
	for (i = 0; i < ARRAY_SIZE(multi_hash); i++)
		write_rreg(dev->base_addr, i + LADRL, multi_hash[i]);

	/*
	 * Write the mode register
	 */
	write_rreg(dev->base_addr, MODE, mode);

	if (!stopped) {
		/*
		 * Put the chip back into running mode
		 */
		write_rreg(dev->base_addr, CTRL1, 0);
	}

	spin_unlock_irqrestore(&priv->chip_lock, flags);
}