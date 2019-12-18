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
typedef  size_t u8 ;
typedef  int u32 ;
struct b43_phy {int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct TYPE_2__ {int gmval; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_NTAB32 (int,int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int* b43_nphy_get_tx_gain_table (struct b43_wldev*) ; 
 int* b43_ntab_papd_pga_gain_delta_ipa_2g ; 
 int /*<<< orphan*/  b43_ntab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_ntab_write_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int const*) ; 
 TYPE_1__* nphy ; 

__attribute__((used)) static void b43_nphy_tx_gain_table_upload(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	const u32 *table = NULL;
	u32 rfpwr_offset;
	u8 pga_gain;
	int i;

	table = b43_nphy_get_tx_gain_table(dev);
	b43_ntab_write_bulk(dev, B43_NTAB32(26, 192), 128, table);
	b43_ntab_write_bulk(dev, B43_NTAB32(27, 192), 128, table);

	if (phy->rev >= 3) {
#if 0
		nphy->gmval = (table[0] >> 16) & 0x7000;
#endif

		for (i = 0; i < 128; i++) {
			pga_gain = (table[i] >> 24) & 0xF;
			if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ)
				rfpwr_offset =
				 b43_ntab_papd_pga_gain_delta_ipa_2g[pga_gain];
			else
				rfpwr_offset =
				 0; /* FIXME */
			b43_ntab_write(dev, B43_NTAB32(26, 576 + i),
				       rfpwr_offset);
			b43_ntab_write(dev, B43_NTAB32(27, 576 + i),
				       rfpwr_offset);
		}
	}
}