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
typedef  int u64 ;
typedef  int u32 ;
struct ieee80211_hw {int dummy; } ;
struct dev_addr_list {struct dev_addr_list* next; int /*<<< orphan*/  dmi_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 adm8211_prepare_multicast(struct ieee80211_hw *hw,
				     int mc_count, struct dev_addr_list *ha)
{
	unsigned int bit_nr, i;
	u32 mc_filter[2];

	mc_filter[1] = mc_filter[0] = 0;

	for (i = 0; i < mc_count; i++) {
		if (!ha)
			break;
		bit_nr = ether_crc(ETH_ALEN, ha->dmi_addr) >> 26;

		bit_nr &= 0x3F;
		mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 31);
		ha = ha->next;
	}

	return mc_filter[0] | ((u64)(mc_filter[1]) << 32);
}