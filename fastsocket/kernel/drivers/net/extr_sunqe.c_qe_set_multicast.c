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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct sunqe {int mconfig; scalar_t__ mregs; } ;
struct net_device {int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {char* dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ MREGS_FILTER ; 
 scalar_t__ MREGS_IACONFIG ; 
 int MREGS_IACONFIG_ACHNGE ; 
 int MREGS_IACONFIG_LARESET ; 
 scalar_t__ MREGS_MCONFIG ; 
 int MREGS_MCONFIG_PROMISC ; 
 int /*<<< orphan*/  barrier () ; 
 int ether_crc_le (int,char*) ; 
 struct sunqe* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int sbus_readb (scalar_t__) ; 
 int /*<<< orphan*/  sbus_writeb (int,scalar_t__) ; 

__attribute__((used)) static void qe_set_multicast(struct net_device *dev)
{
	struct sunqe *qep = netdev_priv(dev);
	struct dev_mc_list *dmi = dev->mc_list;
	u8 new_mconfig = qep->mconfig;
	char *addrs;
	int i;
	u32 crc;

	/* Lock out others. */
	netif_stop_queue(dev);

	if ((dev->flags & IFF_ALLMULTI) || (dev->mc_count > 64)) {
		sbus_writeb(MREGS_IACONFIG_ACHNGE | MREGS_IACONFIG_LARESET,
			    qep->mregs + MREGS_IACONFIG);
		while ((sbus_readb(qep->mregs + MREGS_IACONFIG) & MREGS_IACONFIG_ACHNGE) != 0)
			barrier();
		for (i = 0; i < 8; i++)
			sbus_writeb(0xff, qep->mregs + MREGS_FILTER);
		sbus_writeb(0, qep->mregs + MREGS_IACONFIG);
	} else if (dev->flags & IFF_PROMISC) {
		new_mconfig |= MREGS_MCONFIG_PROMISC;
	} else {
		u16 hash_table[4];
		u8 *hbytes = (unsigned char *) &hash_table[0];

		for (i = 0; i < 4; i++)
			hash_table[i] = 0;

		for (i = 0; i < dev->mc_count; i++) {
			addrs = dmi->dmi_addr;
			dmi = dmi->next;

			if (!(*addrs & 1))
				continue;
			crc = ether_crc_le(6, addrs);
			crc >>= 26;
			hash_table[crc >> 4] |= 1 << (crc & 0xf);
		}
		/* Program the qe with the new filter value. */
		sbus_writeb(MREGS_IACONFIG_ACHNGE | MREGS_IACONFIG_LARESET,
			    qep->mregs + MREGS_IACONFIG);
		while ((sbus_readb(qep->mregs + MREGS_IACONFIG) & MREGS_IACONFIG_ACHNGE) != 0)
			barrier();
		for (i = 0; i < 8; i++) {
			u8 tmp = *hbytes++;
			sbus_writeb(tmp, qep->mregs + MREGS_FILTER);
		}
		sbus_writeb(0, qep->mregs + MREGS_IACONFIG);
	}

	/* Any change of the logical address filter, the physical address,
	 * or enabling/disabling promiscuous mode causes the MACE to disable
	 * the receiver.  So we must re-enable them here or else the MACE
	 * refuses to listen to anything on the network.  Sheesh, took
	 * me a day or two to find this bug.
	 */
	qep->mconfig = new_mconfig;
	sbus_writeb(qep->mconfig, qep->mregs + MREGS_MCONFIG);

	/* Let us get going again. */
	netif_wake_queue(dev);
}