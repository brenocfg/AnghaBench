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
typedef  unsigned long u64 ;
struct net_device {int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct ioc3_private {int ehar_h; int ehar_l; int /*<<< orphan*/  emcr; struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;
struct dev_mc_list {char* dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMCR_PROMISC ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 unsigned long ioc3_hash (char*) ; 
 int /*<<< orphan*/  ioc3_r_emcr () ; 
 int /*<<< orphan*/  ioc3_w_ehar_h (unsigned long) ; 
 int /*<<< orphan*/  ioc3_w_ehar_l (unsigned long) ; 
 int /*<<< orphan*/  ioc3_w_emcr (int /*<<< orphan*/ ) ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void ioc3_set_multicast_list(struct net_device *dev)
{
	struct dev_mc_list *dmi = dev->mc_list;
	struct ioc3_private *ip = netdev_priv(dev);
	struct ioc3 *ioc3 = ip->regs;
	u64 ehar = 0;
	int i;

	netif_stop_queue(dev);				/* Lock out others. */

	if (dev->flags & IFF_PROMISC) {			/* Set promiscuous.  */
		ip->emcr |= EMCR_PROMISC;
		ioc3_w_emcr(ip->emcr);
		(void) ioc3_r_emcr();
	} else {
		ip->emcr &= ~EMCR_PROMISC;
		ioc3_w_emcr(ip->emcr);			/* Clear promiscuous. */
		(void) ioc3_r_emcr();

		if ((dev->flags & IFF_ALLMULTI) || (dev->mc_count > 64)) {
			/* Too many for hashing to make sense or we want all
			   multicast packets anyway,  so skip computing all the
			   hashes and just accept all packets.  */
			ip->ehar_h = 0xffffffff;
			ip->ehar_l = 0xffffffff;
		} else {
			for (i = 0; i < dev->mc_count; i++) {
				char *addr = dmi->dmi_addr;
				dmi = dmi->next;

				if (!(*addr & 1))
					continue;

				ehar |= (1UL << ioc3_hash(addr));
			}
			ip->ehar_h = ehar >> 32;
			ip->ehar_l = ehar & 0xffffffff;
		}
		ioc3_w_ehar_h(ip->ehar_h);
		ioc3_w_ehar_l(ip->ehar_l);
	}

	netif_wake_queue(dev);			/* Let us get going again. */
}