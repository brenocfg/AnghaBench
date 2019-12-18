#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct ssb_sprom {int boardflags_lo; int boardflags_hi; } ;
struct ssb_bus {int /*<<< orphan*/  chipco; } ;
struct TYPE_6__ {int rev; struct b43_phy_lp* lp; } ;
struct b43_wldev {TYPE_3__ phy; int /*<<< orphan*/  wl; TYPE_2__* dev; } ;
struct b43_phy_lp {int rx_pwr_offset; int rssi_vf; int rssi_vc; int bx_arch; } ;
struct TYPE_5__ {scalar_t__ board_type; int chip_id; scalar_t__ chip_pkg; struct ssb_sprom* bus_sprom; TYPE_1__* sdev; } ;
struct TYPE_4__ {struct ssb_bus* bus; } ;

/* Variables and functions */
 int B43_BFH_FEM_BT ; 
 int B43_BFH_PAREF ; 
 int B43_BFH_RSSIINV ; 
 int B43_BFL_FEM ; 
 int B43_HF_PR45960W ; 
 int /*<<< orphan*/  B43_LPPHY_4C3 ; 
 int /*<<< orphan*/  B43_LPPHY_4C4 ; 
 int /*<<< orphan*/  B43_LPPHY_4C5 ; 
 int /*<<< orphan*/  B43_LPPHY_ADC_COMPENSATION_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_ADC_CTL_0 ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_DAC_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_RSSI_CTL_0 ; 
 int /*<<< orphan*/  B43_LPPHY_AFE_RSSI_CTL_1 ; 
 int /*<<< orphan*/  B43_LPPHY_CLIPCTRTHRESH ; 
 int /*<<< orphan*/  B43_LPPHY_CRSGAIN_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_CRS_ED_THRESH ; 
 int /*<<< orphan*/  B43_LPPHY_DSSS_CONFIRM_CNT ; 
 int /*<<< orphan*/  B43_LPPHY_GAINDIRECTMISMATCH ; 
 int /*<<< orphan*/  B43_LPPHY_GAIN_MISMATCH_LIMIT ; 
 int /*<<< orphan*/  B43_LPPHY_GPIO_OUTEN ; 
 int /*<<< orphan*/  B43_LPPHY_GPIO_SELECT ; 
 int /*<<< orphan*/  B43_LPPHY_HIGAINDB ; 
 int /*<<< orphan*/  B43_LPPHY_IDLEAFTERPKTRXTO ; 
 int /*<<< orphan*/  B43_LPPHY_INPUT_PWRDB ; 
 int /*<<< orphan*/  B43_LPPHY_LOWGAINDB ; 
 int /*<<< orphan*/  B43_LPPHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_LP_RF_SIGNAL_LUT ; 
 int /*<<< orphan*/  B43_LPPHY_MINPWR_LEVEL ; 
 int /*<<< orphan*/  B43_LPPHY_OFDMSYNCTHRESH0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_0 ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  B43_LPPHY_RX_RADIO_CTL ; 
 int /*<<< orphan*/  B43_LPPHY_SYNCPEAKCNT ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_1 ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_2 ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_3 ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_4 ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_5 ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_6 ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_7 ; 
 int /*<<< orphan*/  B43_LPPHY_TR_LOOKUP_8 ; 
 int /*<<< orphan*/  B43_LPPHY_VERYLOWGAINDB ; 
 int /*<<< orphan*/  B43_LPTAB16 (int,int) ; 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 int /*<<< orphan*/  LDO_PAREF ; 
 scalar_t__ SSB_BOARD_BU4312 ; 
 scalar_t__ SSB_CHIPPACK_BCM4712S ; 
 scalar_t__ b43_current_band (int /*<<< orphan*/ ) ; 
 int b43_hf_read (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_hf_write (struct b43_wldev*,int) ; 
 int /*<<< orphan*/  b43_lptab_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_copy (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_maskset (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 
 int b43_phy_read (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43_phy_write (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ssb_pmu_set_ldo_paref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ssb_pmu_set_ldo_voltage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpphy_baseband_rev0_1_init(struct b43_wldev *dev)
{
	struct ssb_bus *bus = dev->dev->sdev->bus;
	struct ssb_sprom *sprom = dev->dev->bus_sprom;
	struct b43_phy_lp *lpphy = dev->phy.lp;
	u16 tmp, tmp2;

	b43_phy_mask(dev, B43_LPPHY_AFE_DAC_CTL, 0xF7FF);
	b43_phy_write(dev, B43_LPPHY_AFE_CTL, 0);
	b43_phy_write(dev, B43_LPPHY_AFE_CTL_OVR, 0);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_0, 0);
	b43_phy_write(dev, B43_LPPHY_RF_OVERRIDE_2, 0);
	b43_phy_set(dev, B43_LPPHY_AFE_DAC_CTL, 0x0004);
	b43_phy_maskset(dev, B43_LPPHY_OFDMSYNCTHRESH0, 0xFF00, 0x0078);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0x83FF, 0x5800);
	b43_phy_write(dev, B43_LPPHY_ADC_COMPENSATION_CTL, 0x0016);
	b43_phy_maskset(dev, B43_LPPHY_AFE_ADC_CTL_0, 0xFFF8, 0x0004);
	b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0x00FF, 0x5400);
	b43_phy_maskset(dev, B43_LPPHY_HIGAINDB, 0x00FF, 0x2400);
	b43_phy_maskset(dev, B43_LPPHY_LOWGAINDB, 0x00FF, 0x2100);
	b43_phy_maskset(dev, B43_LPPHY_VERYLOWGAINDB, 0xFF00, 0x0006);
	b43_phy_mask(dev, B43_LPPHY_RX_RADIO_CTL, 0xFFFE);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFFE0, 0x0005);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0xFC1F, 0x0180);
	b43_phy_maskset(dev, B43_LPPHY_CLIPCTRTHRESH, 0x83FF, 0x3C00);
	b43_phy_maskset(dev, B43_LPPHY_GAINDIRECTMISMATCH, 0xFFF0, 0x0005);
	b43_phy_maskset(dev, B43_LPPHY_GAIN_MISMATCH_LIMIT, 0xFFC0, 0x001A);
	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0xFF00, 0x00B3);
	b43_phy_maskset(dev, B43_LPPHY_CRS_ED_THRESH, 0x00FF, 0xAD00);
	b43_phy_maskset(dev, B43_LPPHY_INPUT_PWRDB,
			0xFF00, lpphy->rx_pwr_offset);
	if ((sprom->boardflags_lo & B43_BFL_FEM) &&
	   ((b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ) ||
	   (sprom->boardflags_hi & B43_BFH_PAREF))) {
		ssb_pmu_set_ldo_voltage(&bus->chipco, LDO_PAREF, 0x28);
		ssb_pmu_set_ldo_paref(&bus->chipco, true);
		if (dev->phy.rev == 0) {
			b43_phy_maskset(dev, B43_LPPHY_LP_RF_SIGNAL_LUT,
					0xFFCF, 0x0010);
		}
		b43_lptab_write(dev, B43_LPTAB16(11, 7), 60);
	} else {
		ssb_pmu_set_ldo_paref(&bus->chipco, false);
		b43_phy_maskset(dev, B43_LPPHY_LP_RF_SIGNAL_LUT,
				0xFFCF, 0x0020);
		b43_lptab_write(dev, B43_LPTAB16(11, 7), 100);
	}
	tmp = lpphy->rssi_vf | lpphy->rssi_vc << 4 | 0xA000;
	b43_phy_write(dev, B43_LPPHY_AFE_RSSI_CTL_0, tmp);
	if (sprom->boardflags_hi & B43_BFH_RSSIINV)
		b43_phy_maskset(dev, B43_LPPHY_AFE_RSSI_CTL_1, 0xF000, 0x0AAA);
	else
		b43_phy_maskset(dev, B43_LPPHY_AFE_RSSI_CTL_1, 0xF000, 0x02AA);
	b43_lptab_write(dev, B43_LPTAB16(11, 1), 24);
	b43_phy_maskset(dev, B43_LPPHY_RX_RADIO_CTL,
			0xFFF9, (lpphy->bx_arch << 1));
	if (dev->phy.rev == 1 &&
	   (sprom->boardflags_hi & B43_BFH_FEM_BT)) {
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0x3F00, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0400);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_5, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_5, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_6, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_6, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_7, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_7, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_8, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_8, 0xC0FF, 0x0B00);
	} else if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ ||
#if 0 /* Not in RHEL */
		   (dev->dev->board_type == SSB_BOARD_BU4312) ||
#endif
		   (dev->phy.rev == 0 && (sprom->boardflags_lo & B43_BFL_FEM))) {
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x0001);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xC0FF, 0x0400);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x0001);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0500);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0800);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0A00);
	} else if (dev->phy.rev == 1 ||
		  (sprom->boardflags_lo & B43_BFL_FEM)) {
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x0004);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xC0FF, 0x0800);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x0004);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0C00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0100);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x0002);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0300);
	} else {
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_1, 0xC0FF, 0x0900);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xFFC0, 0x000A);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_2, 0xC0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xFFC0, 0x0006);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_3, 0xC0FF, 0x0500);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xFFC0, 0x0006);
		b43_phy_maskset(dev, B43_LPPHY_TR_LOOKUP_4, 0xC0FF, 0x0700);
	}
	if (dev->phy.rev == 1 && (sprom->boardflags_hi & B43_BFH_PAREF)) {
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_5, B43_LPPHY_TR_LOOKUP_1);
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_6, B43_LPPHY_TR_LOOKUP_2);
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_7, B43_LPPHY_TR_LOOKUP_3);
		b43_phy_copy(dev, B43_LPPHY_TR_LOOKUP_8, B43_LPPHY_TR_LOOKUP_4);
	}
	if ((sprom->boardflags_hi & B43_BFH_FEM_BT) &&
	    (dev->dev->chip_id == 0x5354) &&
	    (dev->dev->chip_pkg == SSB_CHIPPACK_BCM4712S)) {
		b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x0006);
		b43_phy_write(dev, B43_LPPHY_GPIO_SELECT, 0x0005);
		b43_phy_write(dev, B43_LPPHY_GPIO_OUTEN, 0xFFFF);
		//FIXME the Broadcom driver caches & delays this HF write!
		b43_hf_write(dev, b43_hf_read(dev) | B43_HF_PR45960W);
	}
	if (b43_current_band(dev->wl) == IEEE80211_BAND_2GHZ) {
		b43_phy_set(dev, B43_LPPHY_LP_PHY_CTL, 0x8000);
		b43_phy_set(dev, B43_LPPHY_CRSGAIN_CTL, 0x0040);
		b43_phy_maskset(dev, B43_LPPHY_MINPWR_LEVEL, 0x00FF, 0xA400);
		b43_phy_maskset(dev, B43_LPPHY_CRSGAIN_CTL, 0xF0FF, 0x0B00);
		b43_phy_maskset(dev, B43_LPPHY_SYNCPEAKCNT, 0xFFF8, 0x0007);
		b43_phy_maskset(dev, B43_LPPHY_DSSS_CONFIRM_CNT, 0xFFF8, 0x0003);
		b43_phy_maskset(dev, B43_LPPHY_DSSS_CONFIRM_CNT, 0xFFC7, 0x0020);
		b43_phy_mask(dev, B43_LPPHY_IDLEAFTERPKTRXTO, 0x00FF);
	} else { /* 5GHz */
		b43_phy_mask(dev, B43_LPPHY_LP_PHY_CTL, 0x7FFF);
		b43_phy_mask(dev, B43_LPPHY_CRSGAIN_CTL, 0xFFBF);
	}
	if (dev->phy.rev == 1) {
		tmp = b43_phy_read(dev, B43_LPPHY_CLIPCTRTHRESH);
		tmp2 = (tmp & 0x03E0) >> 5;
		tmp2 |= tmp2 << 5;
		b43_phy_write(dev, B43_LPPHY_4C3, tmp2);
		tmp = b43_phy_read(dev, B43_LPPHY_GAINDIRECTMISMATCH);
		tmp2 = (tmp & 0x1F00) >> 8;
		tmp2 |= tmp2 << 5;
		b43_phy_write(dev, B43_LPPHY_4C4, tmp2);
		tmp = b43_phy_read(dev, B43_LPPHY_VERYLOWGAINDB);
		tmp2 = tmp & 0x00FF;
		tmp2 |= tmp << 8;
		b43_phy_write(dev, B43_LPPHY_4C5, tmp2);
	}
}