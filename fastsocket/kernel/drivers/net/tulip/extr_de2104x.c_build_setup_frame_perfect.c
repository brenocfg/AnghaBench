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
typedef  void* u16 ;
struct net_device {int mc_count; scalar_t__ dev_addr; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {scalar_t__ dmi_addr; struct dev_mc_list* next; } ;
struct de_private {void** setup_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (void**,int,int) ; 
 struct de_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void build_setup_frame_perfect(u16 *setup_frm, struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);
	struct dev_mc_list *mclist;
	int i;
	u16 *eaddrs;

	/* We have <= 14 addresses so we can use the wonderful
	   16 address perfect filtering of the Tulip. */
	for (i = 0, mclist = dev->mc_list; i < dev->mc_count;
	     i++, mclist = mclist->next) {
		eaddrs = (u16 *)mclist->dmi_addr;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
		*setup_frm++ = *eaddrs; *setup_frm++ = *eaddrs++;
	}
	/* Fill the unused entries with the broadcast address. */
	memset(setup_frm, 0xff, (15-i)*12);
	setup_frm = &de->setup_frame[15*6];

	/* Fill the final entry with our physical address. */
	eaddrs = (u16 *)dev->dev_addr;
	*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
	*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
	*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];
}