#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_10__ {int /*<<< orphan*/  tr_iso; } ;
struct TYPE_11__ {TYPE_4__ ghz2; } ;
struct ssb_sprom {int cck2gpo; int ofdm2gpo; int* mcs2gpo; int ant_available_bg; int /*<<< orphan*/  freqoffset_corr; int /*<<< orphan*/  tempsense_option; int /*<<< orphan*/  tempcorrx; int /*<<< orphan*/  iqcal_swp_dis; int /*<<< orphan*/  hw_iqcal_en; int /*<<< orphan*/  tempsense_slope; int /*<<< orphan*/  measpower; int /*<<< orphan*/  rawtempsense; int /*<<< orphan*/  opo; TYPE_6__* core_pwr_info; int /*<<< orphan*/  rssisav2g; int /*<<< orphan*/  rssismc2g; int /*<<< orphan*/  rssismf2g; int /*<<< orphan*/  pa0b2; int /*<<< orphan*/  pa0b1; int /*<<< orphan*/  pa0b0; int /*<<< orphan*/  rxpo2g; TYPE_5__ fem; } ;
struct brcms_phy_pub {int dummy; } ;
struct brcms_phy_lcnphy {int lcnphy_mcs20_po; int lcnphy_cck_dig_filt_type; int /*<<< orphan*/  lcnphy_freqoffset_corr; int /*<<< orphan*/  lcnphy_tempsense_option; int /*<<< orphan*/  lcnphy_tempcorrx; int /*<<< orphan*/  lcnphy_iqcal_swp_dis; int /*<<< orphan*/  lcnphy_hw_iqcal_en; int /*<<< orphan*/  lcnphy_tempsense_slope; int /*<<< orphan*/  lcnphy_measPower; int /*<<< orphan*/  lcnphy_rawtempsense; int /*<<< orphan*/  lcnphy_rssi_gs; int /*<<< orphan*/  lcnphy_rssi_gs_hightemp; int /*<<< orphan*/  lcnphy_rssi_vc; int /*<<< orphan*/  lcnphy_rssi_vc_hightemp; int /*<<< orphan*/  lcnphy_rssi_vf; int /*<<< orphan*/  lcnphy_rssi_vf_hightemp; int /*<<< orphan*/  lcnphy_rssi_gs_lowtemp; int /*<<< orphan*/  lcnphy_rssi_vc_lowtemp; int /*<<< orphan*/  lcnphy_rssi_vf_lowtemp; int /*<<< orphan*/  lcnphy_rx_power_offset; int /*<<< orphan*/  lcnphy_tr_isolation_mid; } ;
struct TYPE_7__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {void** tx_srom_max_rate_2g; int /*<<< orphan*/ * txpa_2g; int /*<<< orphan*/ * txpa_2g_high_temp; int /*<<< orphan*/ * txpa_2g_low_temp; void* tx_srom_max_2g; int /*<<< orphan*/  radio_chanspec; TYPE_3__* d11core; TYPE_1__ u; } ;
typedef  void* s8 ;
struct TYPE_12__ {void* maxpwr_2g; } ;
struct TYPE_9__ {TYPE_2__* bus; } ;
struct TYPE_8__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 int PWRTBL_NUM_COEFF ; 
 int TXP_FIRST_CCK ; 
 int TXP_FIRST_OFDM ; 
 int TXP_FIRST_SISO_MCS_20 ; 
 int TXP_LAST_CCK ; 
 int TXP_LAST_OFDM ; 
 int TXP_LAST_SISO_MCS_20 ; 
 int /*<<< orphan*/  wlc_phy_ant_rxdiv_set (struct brcms_phy_pub*,int) ; 

__attribute__((used)) static bool wlc_phy_txpwr_srom_read_lcnphy(struct brcms_phy *pi)
{
	s8 txpwr = 0;
	int i;
	struct brcms_phy_lcnphy *pi_lcn = pi->u.pi_lcnphy;
	struct ssb_sprom *sprom = &pi->d11core->bus->sprom;

	if (CHSPEC_IS2G(pi->radio_chanspec)) {
		u16 cckpo = 0;
		u32 offset_ofdm, offset_mcs;

		pi_lcn->lcnphy_tr_isolation_mid = sprom->fem.ghz2.tr_iso;

		pi_lcn->lcnphy_rx_power_offset = sprom->rxpo2g;

		pi->txpa_2g[0] = sprom->pa0b0;
		pi->txpa_2g[1] = sprom->pa0b1;
		pi->txpa_2g[2] = sprom->pa0b2;

		pi_lcn->lcnphy_rssi_vf = sprom->rssismf2g;
		pi_lcn->lcnphy_rssi_vc = sprom->rssismc2g;
		pi_lcn->lcnphy_rssi_gs = sprom->rssisav2g;

		pi_lcn->lcnphy_rssi_vf_lowtemp = pi_lcn->lcnphy_rssi_vf;
		pi_lcn->lcnphy_rssi_vc_lowtemp = pi_lcn->lcnphy_rssi_vc;
		pi_lcn->lcnphy_rssi_gs_lowtemp = pi_lcn->lcnphy_rssi_gs;

		pi_lcn->lcnphy_rssi_vf_hightemp = pi_lcn->lcnphy_rssi_vf;
		pi_lcn->lcnphy_rssi_vc_hightemp = pi_lcn->lcnphy_rssi_vc;
		pi_lcn->lcnphy_rssi_gs_hightemp = pi_lcn->lcnphy_rssi_gs;

		txpwr = sprom->core_pwr_info[0].maxpwr_2g;
		pi->tx_srom_max_2g = txpwr;

		for (i = 0; i < PWRTBL_NUM_COEFF; i++) {
			pi->txpa_2g_low_temp[i] = pi->txpa_2g[i];
			pi->txpa_2g_high_temp[i] = pi->txpa_2g[i];
		}

		cckpo = sprom->cck2gpo;
		offset_ofdm = sprom->ofdm2gpo;
		if (cckpo) {
			uint max_pwr_chan = txpwr;

			for (i = TXP_FIRST_CCK; i <= TXP_LAST_CCK; i++) {
				pi->tx_srom_max_rate_2g[i] =
					max_pwr_chan - ((cckpo & 0xf) * 2);
				cckpo >>= 4;
			}

			for (i = TXP_FIRST_OFDM; i <= TXP_LAST_OFDM; i++) {
				pi->tx_srom_max_rate_2g[i] =
					max_pwr_chan -
					((offset_ofdm & 0xf) * 2);
				offset_ofdm >>= 4;
			}
		} else {
			u8 opo = 0;

			opo = sprom->opo;

			for (i = TXP_FIRST_CCK; i <= TXP_LAST_CCK; i++)
				pi->tx_srom_max_rate_2g[i] = txpwr;

			for (i = TXP_FIRST_OFDM; i <= TXP_LAST_OFDM; i++) {
				pi->tx_srom_max_rate_2g[i] = txpwr -
						((offset_ofdm & 0xf) * 2);
				offset_ofdm >>= 4;
			}
			offset_mcs = sprom->mcs2gpo[1] << 16;
			offset_mcs |= sprom->mcs2gpo[0];
			pi_lcn->lcnphy_mcs20_po = offset_mcs;
			for (i = TXP_FIRST_SISO_MCS_20;
			     i <= TXP_LAST_SISO_MCS_20; i++) {
				pi->tx_srom_max_rate_2g[i] =
					txpwr - ((offset_mcs & 0xf) * 2);
				offset_mcs >>= 4;
			}
		}

		pi_lcn->lcnphy_rawtempsense = sprom->rawtempsense;
		pi_lcn->lcnphy_measPower = sprom->measpower;
		pi_lcn->lcnphy_tempsense_slope = sprom->tempsense_slope;
		pi_lcn->lcnphy_hw_iqcal_en = sprom->hw_iqcal_en;
		pi_lcn->lcnphy_iqcal_swp_dis = sprom->iqcal_swp_dis;
		pi_lcn->lcnphy_tempcorrx = sprom->tempcorrx;
		pi_lcn->lcnphy_tempsense_option = sprom->tempsense_option;
		pi_lcn->lcnphy_freqoffset_corr = sprom->freqoffset_corr;
		if (sprom->ant_available_bg > 1)
			wlc_phy_ant_rxdiv_set((struct brcms_phy_pub *) pi,
				sprom->ant_available_bg);
	}
	pi_lcn->lcnphy_cck_dig_filt_type = -1;

	return true;
}