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
struct smsc9420_pdata {int dummy; } ;
struct net_device {int flags; scalar_t__ mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {struct dev_mc_list* next; int /*<<< orphan*/  dmi_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HASHH ; 
 int /*<<< orphan*/  HASHL ; 
 int /*<<< orphan*/  HW ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MAC_CR ; 
 int MAC_CR_HPFILT_ ; 
 int MAC_CR_MCPAS_ ; 
 int MAC_CR_PRMS_ ; 
 struct smsc9420_pdata* netdev_priv (struct net_device*) ; 
 int smsc9420_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_pci_flush_write (struct smsc9420_pdata*) ; 
 int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smsc_dbg (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void smsc9420_set_multicast_list(struct net_device *dev)
{
	struct smsc9420_pdata *pd = netdev_priv(dev);
	u32 mac_cr = smsc9420_reg_read(pd, MAC_CR);

	if (dev->flags & IFF_PROMISC) {
		smsc_dbg(HW, "Promiscuous Mode Enabled");
		mac_cr |= MAC_CR_PRMS_;
		mac_cr &= (~MAC_CR_MCPAS_);
		mac_cr &= (~MAC_CR_HPFILT_);
	} else if (dev->flags & IFF_ALLMULTI) {
		smsc_dbg(HW, "Receive all Multicast Enabled");
		mac_cr &= (~MAC_CR_PRMS_);
		mac_cr |= MAC_CR_MCPAS_;
		mac_cr &= (~MAC_CR_HPFILT_);
	} else if (dev->mc_count > 0) {
		struct dev_mc_list *mc_list = dev->mc_list;
		u32 hash_lo = 0, hash_hi = 0;

		smsc_dbg(HW, "Multicast filter enabled");
		while (mc_list) {
			u32 bit_num = smsc9420_hash(mc_list->dmi_addr);
			u32 mask = 1 << (bit_num & 0x1F);

			if (bit_num & 0x20)
				hash_hi |= mask;
			else
				hash_lo |= mask;

			mc_list = mc_list->next;
		}
		smsc9420_reg_write(pd, HASHH, hash_hi);
		smsc9420_reg_write(pd, HASHL, hash_lo);

		mac_cr &= (~MAC_CR_PRMS_);
		mac_cr &= (~MAC_CR_MCPAS_);
		mac_cr |= MAC_CR_HPFILT_;
	} else {
		smsc_dbg(HW, "Receive own packets only.");
		smsc9420_reg_write(pd, HASHH, 0);
		smsc9420_reg_write(pd, HASHL, 0);

		mac_cr &= (~MAC_CR_PRMS_);
		mac_cr &= (~MAC_CR_MCPAS_);
		mac_cr &= (~MAC_CR_HPFILT_);
	}

	smsc9420_reg_write(pd, MAC_CR, mac_cr);
	smsc9420_pci_flush_write(pd);
}