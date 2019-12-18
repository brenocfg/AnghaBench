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
struct b43_phy {int rev; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;

/* Variables and functions */
 int B2056_SYN_GPIO_MASTER1 ; 
 int B2056_SYN_RESERVED_ADDR30 ; 
 int B2056_SYN_RESERVED_ADDR31 ; 
 int B2056_TX0 ; 
 int B2056_TX1 ; 
 int B2056_TX_IQCAL_IDAC ; 
 int B2056_TX_IQCAL_VCM_HG ; 
 int B2056_TX_TSSIA ; 
 int B2056_TX_TSSIG ; 
 int B2056_TX_TSSI_MISC1 ; 
 int B2056_TX_TSSI_MISC2 ; 
 int B2056_TX_TSSI_MISC3 ; 
 int B2056_TX_TSSI_VCM ; 
 int B2056_TX_TX_AMP_DET ; 
 int B2056_TX_TX_SSI_MASTER ; 
 int B2056_TX_TX_SSI_MUX ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,int) ; 

__attribute__((used)) static void b43_nphy_ipa_internal_tssi_setup(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	u8 core;
	u16 r; /* routing */

	if (phy->rev >= 7) {
		for (core = 0; core < 2; core++) {
			r = core ? 0x190 : 0x170;
			if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
				b43_radio_write(dev, r + 0x5, 0x5);
				b43_radio_write(dev, r + 0x9, 0xE);
				if (phy->rev != 5)
					b43_radio_write(dev, r + 0xA, 0);
				if (phy->rev != 7)
					b43_radio_write(dev, r + 0xB, 1);
				else
					b43_radio_write(dev, r + 0xB, 0x31);
			} else {
				b43_radio_write(dev, r + 0x5, 0x9);
				b43_radio_write(dev, r + 0x9, 0xC);
				b43_radio_write(dev, r + 0xB, 0x0);
				if (phy->rev != 5)
					b43_radio_write(dev, r + 0xA, 1);
				else
					b43_radio_write(dev, r + 0xA, 0x31);
			}
			b43_radio_write(dev, r + 0x6, 0);
			b43_radio_write(dev, r + 0x7, 0);
			b43_radio_write(dev, r + 0x8, 3);
			b43_radio_write(dev, r + 0xC, 0);
		}
	} else {
		if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ)
			b43_radio_write(dev, B2056_SYN_RESERVED_ADDR31, 0x128);
		else
			b43_radio_write(dev, B2056_SYN_RESERVED_ADDR31, 0x80);
		b43_radio_write(dev, B2056_SYN_RESERVED_ADDR30, 0);
		b43_radio_write(dev, B2056_SYN_GPIO_MASTER1, 0x29);

		for (core = 0; core < 2; core++) {
			r = core ? B2056_TX1 : B2056_TX0;

			b43_radio_write(dev, r | B2056_TX_IQCAL_VCM_HG, 0);
			b43_radio_write(dev, r | B2056_TX_IQCAL_IDAC, 0);
			b43_radio_write(dev, r | B2056_TX_TSSI_VCM, 3);
			b43_radio_write(dev, r | B2056_TX_TX_AMP_DET, 0);
			b43_radio_write(dev, r | B2056_TX_TSSI_MISC1, 8);
			b43_radio_write(dev, r | B2056_TX_TSSI_MISC2, 0);
			b43_radio_write(dev, r | B2056_TX_TSSI_MISC3, 0);
			if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
				b43_radio_write(dev, r | B2056_TX_TX_SSI_MASTER,
						0x5);
				if (phy->rev != 5)
					b43_radio_write(dev, r | B2056_TX_TSSIA,
							0x00);
				if (phy->rev >= 5)
					b43_radio_write(dev, r | B2056_TX_TSSIG,
							0x31);
				else
					b43_radio_write(dev, r | B2056_TX_TSSIG,
							0x11);
				b43_radio_write(dev, r | B2056_TX_TX_SSI_MUX,
						0xE);
			} else {
				b43_radio_write(dev, r | B2056_TX_TX_SSI_MASTER,
						0x9);
				b43_radio_write(dev, r | B2056_TX_TSSIA, 0x31);
				b43_radio_write(dev, r | B2056_TX_TSSIG, 0x0);
				b43_radio_write(dev, r | B2056_TX_TX_SSI_MUX,
						0xC);
			}
		}
	}
}