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
typedef  int u16 ;
struct net_device {int flags; int mc_count; struct dev_mc_list* mc_list; } ;
struct lance_private {struct lance_init_block* init_block; } ;
struct lance_init_block {int* filter; } ;
struct dev_mc_list {char* dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int ether_crc_le (int,char*) ; 
 struct lance_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void lance_load_multicast (struct net_device *dev)
{
        struct lance_private *lp = netdev_priv(dev);
        volatile struct lance_init_block *ib = lp->init_block;
        volatile u16 *mcast_table = (u16 *)&ib->filter;
        struct dev_mc_list *dmi=dev->mc_list;
        char *addrs;
        int i;
        u32 crc;

        /* set all multicast bits */
        if (dev->flags & IFF_ALLMULTI){
                ib->filter [0] = 0xffffffff;
                ib->filter [1] = 0xffffffff;
                return;
        }
        /* clear the multicast filter */
        ib->filter [0] = 0;
        ib->filter [1] = 0;

        /* Add addresses */
        for (i = 0; i < dev->mc_count; i++){
                addrs = dmi->dmi_addr;
                dmi   = dmi->next;

                /* multicast address? */
                if (!(*addrs & 1))
                        continue;

		crc = ether_crc_le(6, addrs);
                crc = crc >> 26;
                mcast_table [crc >> 4] |= 1 << (crc & 0xf);
        }
        return;
}