#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct gem {scalar_t__ regs; TYPE_1__* dev; } ;
struct dev_mc_list {char* dmi_addr; struct dev_mc_list* next; } ;
struct TYPE_2__ {int flags; int mc_count; struct dev_mc_list* mc_list; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ MAC_HASH0 ; 
 int MAC_RXCFG_HFE ; 
 int MAC_RXCFG_PROM ; 
 int ether_crc_le (int,char*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static u32 gem_setup_multicast(struct gem *gp)
{
	u32 rxcfg = 0;
	int i;

	if ((gp->dev->flags & IFF_ALLMULTI) ||
	    (gp->dev->mc_count > 256)) {
	    	for (i=0; i<16; i++)
			writel(0xffff, gp->regs + MAC_HASH0 + (i << 2));
		rxcfg |= MAC_RXCFG_HFE;
	} else if (gp->dev->flags & IFF_PROMISC) {
		rxcfg |= MAC_RXCFG_PROM;
	} else {
		u16 hash_table[16];
		u32 crc;
		struct dev_mc_list *dmi = gp->dev->mc_list;
		int i;

		for (i = 0; i < 16; i++)
			hash_table[i] = 0;

		for (i = 0; i < gp->dev->mc_count; i++) {
			char *addrs = dmi->dmi_addr;

			dmi = dmi->next;

			if (!(*addrs & 1))
				continue;

 			crc = ether_crc_le(6, addrs);
			crc >>= 24;
			hash_table[crc >> 4] |= 1 << (15 - (crc & 0xf));
		}
	    	for (i=0; i<16; i++)
			writel(hash_table[i], gp->regs + MAC_HASH0 + (i << 2));
		rxcfg |= MAC_RXCFG_HFE;
	}

	return rxcfg;
}