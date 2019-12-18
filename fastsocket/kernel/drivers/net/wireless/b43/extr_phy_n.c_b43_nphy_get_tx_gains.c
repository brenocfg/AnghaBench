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
struct nphy_txgains {int* ipa; int* pad; int* pga; int* txgm; } ;
struct TYPE_2__ {int rev; struct b43_phy_n* n; } ;
struct b43_wldev {TYPE_1__ phy; } ;
struct b43_phy_n {scalar_t__ hang_avoid; int /*<<< orphan*/  txpwrctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NPHY_C1_TXPCTL_STAT ; 
 int /*<<< orphan*/  B43_NPHY_C2_TXPCTL_STAT ; 
 int B43_NPHY_TXPCTL_STAT_BIDX ; 
 int B43_NPHY_TXPCTL_STAT_BIDX_SHIFT ; 
 int /*<<< orphan*/  B43_NTAB16 (int,int) ; 
 int* b43_nphy_get_tx_gain_table (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_nphy_stay_in_carrier_search (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_ntab_read_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int*) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nphy_txgains b43_nphy_get_tx_gains(struct b43_wldev *dev)
{
	struct b43_phy_n *nphy = dev->phy.n;

	u16 curr_gain[2];
	struct nphy_txgains target;
	const u32 *table = NULL;

	if (!nphy->txpwrctrl) {
		int i;

		if (nphy->hang_avoid)
			b43_nphy_stay_in_carrier_search(dev, true);
		b43_ntab_read_bulk(dev, B43_NTAB16(7, 0x110), 2, curr_gain);
		if (nphy->hang_avoid)
			b43_nphy_stay_in_carrier_search(dev, false);

		for (i = 0; i < 2; ++i) {
			if (dev->phy.rev >= 3) {
				target.ipa[i] = curr_gain[i] & 0x000F;
				target.pad[i] = (curr_gain[i] & 0x00F0) >> 4;
				target.pga[i] = (curr_gain[i] & 0x0F00) >> 8;
				target.txgm[i] = (curr_gain[i] & 0x7000) >> 12;
			} else {
				target.ipa[i] = curr_gain[i] & 0x0003;
				target.pad[i] = (curr_gain[i] & 0x000C) >> 2;
				target.pga[i] = (curr_gain[i] & 0x0070) >> 4;
				target.txgm[i] = (curr_gain[i] & 0x0380) >> 7;
			}
		}
	} else {
		int i;
		u16 index[2];
		index[0] = (b43_phy_read(dev, B43_NPHY_C1_TXPCTL_STAT) &
			B43_NPHY_TXPCTL_STAT_BIDX) >>
			B43_NPHY_TXPCTL_STAT_BIDX_SHIFT;
		index[1] = (b43_phy_read(dev, B43_NPHY_C2_TXPCTL_STAT) &
			B43_NPHY_TXPCTL_STAT_BIDX) >>
			B43_NPHY_TXPCTL_STAT_BIDX_SHIFT;

		for (i = 0; i < 2; ++i) {
			table = b43_nphy_get_tx_gain_table(dev);
			if (dev->phy.rev >= 3) {
				target.ipa[i] = (table[index[i]] >> 16) & 0xF;
				target.pad[i] = (table[index[i]] >> 20) & 0xF;
				target.pga[i] = (table[index[i]] >> 24) & 0xF;
				target.txgm[i] = (table[index[i]] >> 28) & 0xF;
			} else {
				target.ipa[i] = (table[index[i]] >> 16) & 0x3;
				target.pad[i] = (table[index[i]] >> 18) & 0x3;
				target.pga[i] = (table[index[i]] >> 20) & 0x7;
				target.txgm[i] = (table[index[i]] >> 23) & 0x7;
			}
		}
	}

	return target;
}