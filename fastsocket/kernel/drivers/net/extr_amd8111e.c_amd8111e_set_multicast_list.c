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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct net_device {int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct amd8111e_priv {scalar_t__ mmio; struct dev_mc_list* mc_list; int /*<<< orphan*/  options; } ;

/* Variables and functions */
 scalar_t__ CMD2 ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 scalar_t__ LADRF ; 
 int MAX_FILTER_SIZE ; 
 int /*<<< orphan*/  OPTION_MULTICAST_ENABLE ; 
 int PROM ; 
 int VAL2 ; 
 int /*<<< orphan*/  amd8111e_writeq (int /*<<< orphan*/ ,scalar_t__) ; 
 int ether_crc_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct amd8111e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void amd8111e_set_multicast_list(struct net_device *dev)
{
	struct dev_mc_list* mc_ptr;
	struct amd8111e_priv *lp = netdev_priv(dev);
	u32 mc_filter[2] ;
	int i,bit_num;
	if(dev->flags & IFF_PROMISC){
		writel( VAL2 | PROM, lp->mmio + CMD2);
		return;
	}
	else
		writel( PROM, lp->mmio + CMD2);
	if(dev->flags & IFF_ALLMULTI || dev->mc_count > MAX_FILTER_SIZE){
		/* get all multicast packet */
		mc_filter[1] = mc_filter[0] = 0xffffffff;
		lp->mc_list = dev->mc_list;
		lp->options |= OPTION_MULTICAST_ENABLE;
		amd8111e_writeq(*(u64*)mc_filter,lp->mmio + LADRF);
		return;
	}
	if( dev->mc_count == 0 ){
		/* get only own packets */
		mc_filter[1] = mc_filter[0] = 0;
		lp->mc_list = NULL;
		lp->options &= ~OPTION_MULTICAST_ENABLE;
		amd8111e_writeq(*(u64*)mc_filter,lp->mmio + LADRF);
		/* disable promiscous mode */
		writel(PROM, lp->mmio + CMD2);
		return;
	}
	/* load all the multicast addresses in the logic filter */
	lp->options |= OPTION_MULTICAST_ENABLE;
	lp->mc_list = dev->mc_list;
	mc_filter[1] = mc_filter[0] = 0;
	for (i = 0, mc_ptr = dev->mc_list; mc_ptr && i < dev->mc_count;
		     i++, mc_ptr = mc_ptr->next) {
		bit_num = (ether_crc_le(ETH_ALEN, mc_ptr->dmi_addr) >> 26) & 0x3f;
		mc_filter[bit_num >> 5] |= 1 << (bit_num & 31);
	}
	amd8111e_writeq(*(u64*)mc_filter,lp->mmio+ LADRF);

	/* To eliminate PCI posting bug */
	readl(lp->mmio + CMD2);

}