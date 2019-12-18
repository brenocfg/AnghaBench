#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssb_sprom {int boardflags_hi; int boardflags_lo; } ;
struct TYPE_4__ {int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; TYPE_2__ phy; TYPE_1__* dev; } ;
struct TYPE_3__ {struct ssb_sprom* bus_sprom; } ;

/* Variables and functions */
 int B43_BFH_NOPA ; 
 int B43_BFL_HGPA ; 
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpphy_rev0_2ghz_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev0_5ghz_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev0_nopa_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev1_2ghz_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev1_5ghz_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev1_nopa_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev2_2ghz_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev2_5ghz_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_rev2_nopa_tx_gain_table ; 
 int /*<<< orphan*/  lpphy_write_gain_table_bulk (struct b43_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void lpphy_init_tx_gain_table(struct b43_wldev *dev)
{
	struct ssb_sprom *sprom = dev->dev->bus_sprom;

	switch (dev->phy.rev) {
	case 0:
		if ((sprom->boardflags_hi & B43_BFH_NOPA) ||
		    (sprom->boardflags_lo & B43_BFL_HGPA))
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev0_nopa_tx_gain_table);
		else if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ)
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev0_2ghz_tx_gain_table);
		else
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev0_5ghz_tx_gain_table);
		break;
	case 1:
		if ((sprom->boardflags_hi & B43_BFH_NOPA) ||
		    (sprom->boardflags_lo & B43_BFL_HGPA))
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev1_nopa_tx_gain_table);
		else if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ)
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev1_2ghz_tx_gain_table);
		else
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev1_5ghz_tx_gain_table);
		break;
	default:
		if (sprom->boardflags_hi & B43_BFH_NOPA)
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev2_nopa_tx_gain_table);
		else if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ)
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev2_2ghz_tx_gain_table);
		else
			lpphy_write_gain_table_bulk(dev, 0, 128,
					lpphy_rev2_5ghz_tx_gain_table);
	}
}