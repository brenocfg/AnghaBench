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
struct sbmac_softc {int sbm_devflags; int /*<<< orphan*/  sbm_lock; } ;
struct net_device {int flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 struct sbmac_softc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sbmac_promiscuous_mode (struct sbmac_softc*,int) ; 
 int /*<<< orphan*/  sbmac_setmulti (struct sbmac_softc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sbmac_set_rx_mode(struct net_device *dev)
{
	unsigned long flags;
	struct sbmac_softc *sc = netdev_priv(dev);

	spin_lock_irqsave(&sc->sbm_lock, flags);
	if ((dev->flags ^ sc->sbm_devflags) & IFF_PROMISC) {
		/*
		 * Promiscuous changed.
		 */

		if (dev->flags & IFF_PROMISC) {
			sbmac_promiscuous_mode(sc,1);
		}
		else {
			sbmac_promiscuous_mode(sc,0);
		}
	}
	spin_unlock_irqrestore(&sc->sbm_lock, flags);

	/*
	 * Program the multicasts.  Do this every time.
	 */

	sbmac_setmulti(sc);

}