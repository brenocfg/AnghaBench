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
typedef  int u8 ;
typedef  int u16 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;
typedef  enum ht_rssi_type { ____Placeholder_ht_rssi_type } ht_rssi_type ;

/* Variables and functions */
#define  B43_PHY_HT_AFE_C1 137 
#define  B43_PHY_HT_AFE_C1_OVER 136 
#define  B43_PHY_HT_AFE_C2 135 
#define  B43_PHY_HT_AFE_C2_OVER 134 
#define  B43_PHY_HT_AFE_C3 133 
#define  B43_PHY_HT_AFE_C3_OVER 132 
#define  HT_RSSI_TSSI_2G 131 
#define  R2059_C1 130 
#define  R2059_C2 129 
#define  R2059_C3 128 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int const,int) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void b43_phy_ht_rssi_select(struct b43_wldev *dev, u8 core_sel,
				   enum ht_rssi_type rssi_type)
{
	static const u16 ctl_regs[3][2] = {
		{ B43_PHY_HT_AFE_C1, B43_PHY_HT_AFE_C1_OVER, },
		{ B43_PHY_HT_AFE_C2, B43_PHY_HT_AFE_C2_OVER, },
		{ B43_PHY_HT_AFE_C3, B43_PHY_HT_AFE_C3_OVER, },
	};
	static const u16 radio_r[] = { R2059_C1, R2059_C2, R2059_C3, };
	int core;

	if (core_sel == 0) {
		b43err(dev->wl, "RSSI selection for core off not implemented yet\n");
	} else {
		for (core = 0; core < 3; core++) {
			/* Check if caller requested a one specific core */
			if ((core_sel == 1 && core != 0) ||
			    (core_sel == 2 && core != 1) ||
			    (core_sel == 3 && core != 2))
				continue;

			switch (rssi_type) {
			case HT_RSSI_TSSI_2G:
				b43_phy_set(dev, ctl_regs[core][0], 0x3 << 8);
				b43_phy_set(dev, ctl_regs[core][0], 0x3 << 10);
				b43_phy_set(dev, ctl_regs[core][1], 0x1 << 9);
				b43_phy_set(dev, ctl_regs[core][1], 0x1 << 10);

				b43_radio_set(dev, R2059_C3 | 0xbf, 0x1);
				b43_radio_write(dev, radio_r[core] | 0x159,
						0x11);
				break;
			default:
				b43err(dev->wl, "RSSI selection for type %d not implemented yet\n",
				       rssi_type);
			}
		}
	}
}