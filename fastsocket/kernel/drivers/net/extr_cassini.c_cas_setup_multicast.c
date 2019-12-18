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
struct dev_mc_list {int* dmi_addr; struct dev_mc_list* next; } ;
struct cas {scalar_t__ regs; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  hash_table ;
struct TYPE_2__ {int flags; struct dev_mc_list* mc_list; } ;

/* Variables and functions */
 int CAS_MC_EXACT_MATCH_SIZE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int MAC_RX_CFG_HASH_FILTER_EN ; 
 int MAC_RX_CFG_PROMISC_EN ; 
 scalar_t__ REG_MAC_ADDRN (int) ; 
 scalar_t__ REG_MAC_HASH_TABLEN (int) ; 
 int ether_crc_le (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static u32 cas_setup_multicast(struct cas *cp)
{
	u32 rxcfg = 0;
	int i;

	if (cp->dev->flags & IFF_PROMISC) {
		rxcfg |= MAC_RX_CFG_PROMISC_EN;

	} else if (cp->dev->flags & IFF_ALLMULTI) {
	    	for (i=0; i < 16; i++)
			writel(0xFFFF, cp->regs + REG_MAC_HASH_TABLEN(i));
		rxcfg |= MAC_RX_CFG_HASH_FILTER_EN;

	} else {
		u16 hash_table[16];
		u32 crc;
		struct dev_mc_list *dmi = cp->dev->mc_list;
		int i;

		/* use the alternate mac address registers for the
		 * first 15 multicast addresses
		 */
		for (i = 1; i <= CAS_MC_EXACT_MATCH_SIZE; i++) {
			if (!dmi) {
				writel(0x0, cp->regs + REG_MAC_ADDRN(i*3 + 0));
				writel(0x0, cp->regs + REG_MAC_ADDRN(i*3 + 1));
				writel(0x0, cp->regs + REG_MAC_ADDRN(i*3 + 2));
				continue;
			}
			writel((dmi->dmi_addr[4] << 8) | dmi->dmi_addr[5],
			       cp->regs + REG_MAC_ADDRN(i*3 + 0));
			writel((dmi->dmi_addr[2] << 8) | dmi->dmi_addr[3],
			       cp->regs + REG_MAC_ADDRN(i*3 + 1));
			writel((dmi->dmi_addr[0] << 8) | dmi->dmi_addr[1],
			       cp->regs + REG_MAC_ADDRN(i*3 + 2));
			dmi = dmi->next;
		}

		/* use hw hash table for the next series of
		 * multicast addresses
		 */
		memset(hash_table, 0, sizeof(hash_table));
		while (dmi) {
 			crc = ether_crc_le(ETH_ALEN, dmi->dmi_addr);
			crc >>= 24;
			hash_table[crc >> 4] |= 1 << (15 - (crc & 0xf));
			dmi = dmi->next;
		}
	    	for (i=0; i < 16; i++)
			writel(hash_table[i], cp->regs +
			       REG_MAC_HASH_TABLEN(i));
		rxcfg |= MAC_RX_CFG_HASH_FILTER_EN;
	}

	return rxcfg;
}