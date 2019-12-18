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
struct b43_phy {scalar_t__ type; int rev; } ;
struct b43_wldev {struct b43_phy phy; } ;

/* Variables and functions */
 scalar_t__ B43_PHYTYPE_A ; 
 scalar_t__ B43_PHYTYPE_G ; 
 int /*<<< orphan*/  B43_WARN_ON (int) ; 
 int /*<<< orphan*/  b43_wa_2060txlna_gain (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_afcdac (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_altagc (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_analog (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_art (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_auxclipthr (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_boards_a (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_boards_g (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_cck_shiftbits (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_cpll_nonpilot (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_crs_blank (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_crs_ed (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_crs_reset (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_crs_thr (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_dac (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_divider (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_fft (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_gt (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_initgains (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_iqadc (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_lms (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_mixedsignal (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_msst (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_nft (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_nst (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_papd (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_rssi_adc (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_rssi_lt (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_rt (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_tr_ltov (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_txdc_offset (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_txlna_gain (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_txpuoff_rxpuon (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_wa_wrssi_offset (struct b43_wldev*) ; 

void b43_wa_all(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;

	if (phy->type == B43_PHYTYPE_A) {
		switch (phy->rev) {
		case 2:
			b43_wa_papd(dev);
			b43_wa_auxclipthr(dev);
			b43_wa_afcdac(dev);
			b43_wa_txdc_offset(dev);
			b43_wa_initgains(dev);
			b43_wa_divider(dev);
			b43_wa_gt(dev);
			b43_wa_rssi_lt(dev);
			b43_wa_analog(dev);
			b43_wa_dac(dev);
			b43_wa_fft(dev);
			b43_wa_nft(dev);
			b43_wa_rt(dev);
			b43_wa_nst(dev);
			b43_wa_art(dev);
			b43_wa_txlna_gain(dev);
			b43_wa_crs_reset(dev);
			b43_wa_2060txlna_gain(dev);
			b43_wa_lms(dev);
			break;
		case 3:
			b43_wa_papd(dev);
			b43_wa_mixedsignal(dev);
			b43_wa_rssi_lt(dev);
			b43_wa_txdc_offset(dev);
			b43_wa_initgains(dev);
			b43_wa_dac(dev);
			b43_wa_nft(dev);
			b43_wa_nst(dev);
			b43_wa_msst(dev);
			b43_wa_analog(dev);
			b43_wa_gt(dev);
			b43_wa_txpuoff_rxpuon(dev);
			b43_wa_txlna_gain(dev);
			break;
		case 5:
			b43_wa_iqadc(dev);
		case 6:
			b43_wa_papd(dev);
			b43_wa_rssi_lt(dev);
			b43_wa_txdc_offset(dev);
			b43_wa_initgains(dev);
			b43_wa_dac(dev);
			b43_wa_nft(dev);
			b43_wa_nst(dev);
			b43_wa_msst(dev);
			b43_wa_analog(dev);
			b43_wa_gt(dev);
			b43_wa_txpuoff_rxpuon(dev);
			b43_wa_txlna_gain(dev);
			break;
		case 7:
			b43_wa_iqadc(dev);
			b43_wa_papd(dev);
			b43_wa_rssi_lt(dev);
			b43_wa_txdc_offset(dev);
			b43_wa_initgains(dev);
			b43_wa_dac(dev);
			b43_wa_nft(dev);
			b43_wa_nst(dev);
			b43_wa_msst(dev);
			b43_wa_analog(dev);
			b43_wa_gt(dev);
			b43_wa_txpuoff_rxpuon(dev);
			b43_wa_txlna_gain(dev);
			b43_wa_rssi_adc(dev);
		default:
			B43_WARN_ON(1);
		}
		b43_wa_boards_a(dev);
	} else if (phy->type == B43_PHYTYPE_G) {
		switch (phy->rev) {
		case 1://XXX review rev1
			b43_wa_crs_ed(dev);
			b43_wa_crs_thr(dev);
			b43_wa_crs_blank(dev);
			b43_wa_cck_shiftbits(dev);
			b43_wa_fft(dev);
			b43_wa_nft(dev);
			b43_wa_rt(dev);
			b43_wa_nst(dev);
			b43_wa_art(dev);
			b43_wa_wrssi_offset(dev);
			b43_wa_altagc(dev);
			break;
		case 2:
		case 6:
		case 7:
		case 8:
		case 9:
			b43_wa_tr_ltov(dev);
			b43_wa_crs_ed(dev);
			b43_wa_rssi_lt(dev);
			b43_wa_nft(dev);
			b43_wa_nst(dev);
			b43_wa_msst(dev);
			b43_wa_wrssi_offset(dev);
			b43_wa_altagc(dev);
			b43_wa_analog(dev);
			b43_wa_txpuoff_rxpuon(dev);
			break;
		default:
			B43_WARN_ON(1);
		}
		b43_wa_boards_g(dev);
	} else { /* No N PHY support so far, LP PHY is in phy_lp.c */
		B43_WARN_ON(1);
	}

	b43_wa_cpll_nonpilot(dev);
}