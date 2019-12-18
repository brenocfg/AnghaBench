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
typedef  int u32 ;
struct temac_local {int /*<<< orphan*/  indirect_mutex; } ;
struct net_device {int flags; int mc_count; int /*<<< orphan*/  dev; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int* dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MULTICAST_CAM_TABLE_NUM ; 
 int XTE_AFM_EPPRM_MASK ; 
 int /*<<< orphan*/  XTE_AFM_OFFSET ; 
 int /*<<< orphan*/  XTE_MAW0_OFFSET ; 
 int /*<<< orphan*/  XTE_MAW1_OFFSET ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int temac_indirect_in32 (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_indirect_out32 (struct temac_local*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void temac_set_multicast_list(struct net_device *ndev)
{
	struct temac_local *lp = netdev_priv(ndev);
	u32 multi_addr_msw, multi_addr_lsw, val;
	int i;

	mutex_lock(&lp->indirect_mutex);
	if (ndev->flags & (IFF_ALLMULTI | IFF_PROMISC)
			|| ndev->mc_count > MULTICAST_CAM_TABLE_NUM) {
		/*
		 *	We must make the kernel realise we had to move
		 *	into promisc mode or we start all out war on
		 *	the cable. If it was a promisc request the
		 *	flag is already set. If not we assert it.
		 */
		ndev->flags |= IFF_PROMISC;
		temac_indirect_out32(lp, XTE_AFM_OFFSET, XTE_AFM_EPPRM_MASK);
		dev_info(&ndev->dev, "Promiscuous mode enabled.\n");
	} else if (ndev->mc_count) {
		struct dev_mc_list *mclist = ndev->mc_list;
		for (i = 0; mclist && i < ndev->mc_count; i++) {

			if (i >= MULTICAST_CAM_TABLE_NUM)
				break;
			multi_addr_msw = ((mclist->dmi_addr[3] << 24) |
					  (mclist->dmi_addr[2] << 16) |
					  (mclist->dmi_addr[1] << 8) |
					  (mclist->dmi_addr[0]));
			temac_indirect_out32(lp, XTE_MAW0_OFFSET,
					     multi_addr_msw);
			multi_addr_lsw = ((mclist->dmi_addr[5] << 8) |
					  (mclist->dmi_addr[4]) | (i << 16));
			temac_indirect_out32(lp, XTE_MAW1_OFFSET,
					     multi_addr_lsw);
			mclist = mclist->next;
		}
	} else {
		val = temac_indirect_in32(lp, XTE_AFM_OFFSET);
		temac_indirect_out32(lp, XTE_AFM_OFFSET,
				     val & ~XTE_AFM_EPPRM_MASK);
		temac_indirect_out32(lp, XTE_MAW0_OFFSET, 0);
		temac_indirect_out32(lp, XTE_MAW1_OFFSET, 0);
		dev_info(&ndev->dev, "Promiscuous mode disabled.\n");
	}
	mutex_unlock(&lp->indirect_mutex);
}