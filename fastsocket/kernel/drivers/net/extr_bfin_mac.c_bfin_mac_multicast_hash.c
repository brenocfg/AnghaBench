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
struct net_device {int mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {char* dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  bfin_write_EMAC_HASHHI (int) ; 
 int /*<<< orphan*/  bfin_write_EMAC_HASHLO (int) ; 
 int ether_crc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void bfin_mac_multicast_hash(struct net_device *dev)
{
	u32 emac_hashhi, emac_hashlo;
	struct dev_mc_list *dmi = dev->mc_list;
	char *addrs;
	int i;
	u32 crc;

	emac_hashhi = emac_hashlo = 0;

	for (i = 0; i < dev->mc_count; i++) {
		addrs = dmi->dmi_addr;
		dmi = dmi->next;

		/* skip non-multicast addresses */
		if (!(*addrs & 1))
			continue;

		crc = ether_crc(ETH_ALEN, addrs);
		crc >>= 26;

		if (crc & 0x20)
			emac_hashhi |= 1 << (crc & 0x1f);
		else
			emac_hashlo |= 1 << (crc & 0x1f);
	}

	bfin_write_EMAC_HASHHI(emac_hashhi);
	bfin_write_EMAC_HASHLO(emac_hashlo);

	return;
}