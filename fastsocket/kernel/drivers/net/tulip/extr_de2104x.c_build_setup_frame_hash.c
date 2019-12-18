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
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct de_private {void** setup_frame; } ;
typedef  int /*<<< orphan*/  hash_table ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int ether_crc_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 struct de_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit_le (int,void**) ; 

__attribute__((used)) static void build_setup_frame_hash(u16 *setup_frm, struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);
	u16 hash_table[32];
	struct dev_mc_list *mclist;
	int i;
	u16 *eaddrs;

	memset(hash_table, 0, sizeof(hash_table));
	set_bit_le(255, hash_table); 			/* Broadcast entry */
	/* This should work on big-endian machines as well. */
	for (i = 0, mclist = dev->mc_list; mclist && i < dev->mc_count;
	     i++, mclist = mclist->next) {
		int index = ether_crc_le(ETH_ALEN, mclist->dmi_addr) & 0x1ff;

		set_bit_le(index, hash_table);

		for (i = 0; i < 32; i++) {
			*setup_frm++ = hash_table[i];
			*setup_frm++ = hash_table[i];
		}
		setup_frm = &de->setup_frame[13*6];
	}

	/* Fill the final entry with our physical address. */
	eaddrs = (u16 *)dev->dev_addr;
	*setup_frm++ = eaddrs[0]; *setup_frm++ = eaddrs[0];
	*setup_frm++ = eaddrs[1]; *setup_frm++ = eaddrs[1];
	*setup_frm++ = eaddrs[2]; *setup_frm++ = eaddrs[2];
}