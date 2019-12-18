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
typedef  int uint ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  phy_rev; } ;
struct brcms_phy {scalar_t__ phyhang_avoid; TYPE_2__* sh; int /*<<< orphan*/  radio_chanspec; scalar_t__ nphy_aband_spurwar_en; scalar_t__ nphy_gband_spurwar2_en; scalar_t__ nphy_gband_spurwar_en; TYPE_1__ pubpi; } ;
struct TYPE_4__ {int /*<<< orphan*/  chippkg; int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BCMA_CHIP_ID_BCM4716 ; 
 int /*<<< orphan*/  BCMA_PKG_ID_BCM4717 ; 
 int CHSPEC_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS2G (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS40 (int /*<<< orphan*/ ) ; 
 scalar_t__ CHSPEC_IS5G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPHY_ADJUSTED_MINCRSPOWER ; 
 int /*<<< orphan*/  NPHY_ANARXLPFBW_REDUCTIONFACT ; 
 scalar_t__ NREV_GE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wlc_phy_adjust_crsminpwr_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_adjust_min_noisevar_nphy (struct brcms_phy*,int,int*,int*) ; 
 int /*<<< orphan*/  wlc_phy_adjust_rx_analpfbw_nphy (struct brcms_phy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_phy_stay_in_carriersearch_nphy (struct brcms_phy*,int) ; 

__attribute__((used)) static void wlc_phy_spurwar_nphy(struct brcms_phy *pi)
{
	u16 cur_channel = 0;
	int nphy_adj_tone_id_buf[] = { 57, 58 };
	u32 nphy_adj_noise_var_buf[] = { 0x3ff, 0x3ff };
	bool isAdjustNoiseVar = false;
	uint numTonesAdjust = 0;
	u32 tempval = 0;

	if (NREV_GE(pi->pubpi.phy_rev, 3)) {
		if (pi->phyhang_avoid)
			wlc_phy_stay_in_carriersearch_nphy(pi, true);

		cur_channel = CHSPEC_CHANNEL(pi->radio_chanspec);

		if (pi->nphy_gband_spurwar_en) {

			wlc_phy_adjust_rx_analpfbw_nphy(
				pi,
				NPHY_ANARXLPFBW_REDUCTIONFACT);

			if (CHSPEC_IS2G(pi->radio_chanspec)) {
				if ((cur_channel == 11)
				    && CHSPEC_IS40(pi->radio_chanspec))
					wlc_phy_adjust_min_noisevar_nphy(
						pi, 2,
						nphy_adj_tone_id_buf,
						nphy_adj_noise_var_buf);
				else
					wlc_phy_adjust_min_noisevar_nphy(pi, 0,
									 NULL,
									 NULL);
			}

			wlc_phy_adjust_crsminpwr_nphy(pi,
						     NPHY_ADJUSTED_MINCRSPOWER);
		}

		if ((pi->nphy_gband_spurwar2_en)
		    && CHSPEC_IS2G(pi->radio_chanspec)) {

			if (CHSPEC_IS40(pi->radio_chanspec)) {
				switch (cur_channel) {
				case 3:
					nphy_adj_tone_id_buf[0] = 57;
					nphy_adj_tone_id_buf[1] = 58;
					nphy_adj_noise_var_buf[0] = 0x22f;
					nphy_adj_noise_var_buf[1] = 0x25f;
					isAdjustNoiseVar = true;
					break;
				case 4:
					nphy_adj_tone_id_buf[0] = 41;
					nphy_adj_tone_id_buf[1] = 42;
					nphy_adj_noise_var_buf[0] = 0x22f;
					nphy_adj_noise_var_buf[1] = 0x25f;
					isAdjustNoiseVar = true;
					break;
				case 5:
					nphy_adj_tone_id_buf[0] = 25;
					nphy_adj_tone_id_buf[1] = 26;
					nphy_adj_noise_var_buf[0] = 0x24f;
					nphy_adj_noise_var_buf[1] = 0x25f;
					isAdjustNoiseVar = true;
					break;
				case 6:
					nphy_adj_tone_id_buf[0] = 9;
					nphy_adj_tone_id_buf[1] = 10;
					nphy_adj_noise_var_buf[0] = 0x22f;
					nphy_adj_noise_var_buf[1] = 0x24f;
					isAdjustNoiseVar = true;
					break;
				case 7:
					nphy_adj_tone_id_buf[0] = 121;
					nphy_adj_tone_id_buf[1] = 122;
					nphy_adj_noise_var_buf[0] = 0x18f;
					nphy_adj_noise_var_buf[1] = 0x24f;
					isAdjustNoiseVar = true;
					break;
				case 8:
					nphy_adj_tone_id_buf[0] = 105;
					nphy_adj_tone_id_buf[1] = 106;
					nphy_adj_noise_var_buf[0] = 0x22f;
					nphy_adj_noise_var_buf[1] = 0x25f;
					isAdjustNoiseVar = true;
					break;
				case 9:
					nphy_adj_tone_id_buf[0] = 89;
					nphy_adj_tone_id_buf[1] = 90;
					nphy_adj_noise_var_buf[0] = 0x22f;
					nphy_adj_noise_var_buf[1] = 0x24f;
					isAdjustNoiseVar = true;
					break;
				case 10:
					nphy_adj_tone_id_buf[0] = 73;
					nphy_adj_tone_id_buf[1] = 74;
					nphy_adj_noise_var_buf[0] = 0x22f;
					nphy_adj_noise_var_buf[1] = 0x24f;
					isAdjustNoiseVar = true;
					break;
				default:
					isAdjustNoiseVar = false;
					break;
				}
			}

			if (isAdjustNoiseVar) {
				numTonesAdjust = ARRAY_SIZE(nphy_adj_tone_id_buf);

				wlc_phy_adjust_min_noisevar_nphy(
					pi,
					numTonesAdjust,
					nphy_adj_tone_id_buf,
					nphy_adj_noise_var_buf);

				tempval = 0;

			} else {
				wlc_phy_adjust_min_noisevar_nphy(pi, 0, NULL,
								 NULL);
			}
		}

		if ((pi->nphy_aband_spurwar_en) &&
		    (CHSPEC_IS5G(pi->radio_chanspec))) {
			switch (cur_channel) {
			case 54:
				nphy_adj_tone_id_buf[0] = 32;
				nphy_adj_noise_var_buf[0] = 0x25f;
				break;
			case 38:
			case 102:
			case 118:
				if ((pi->sh->chip == BCMA_CHIP_ID_BCM4716) &&
				    (pi->sh->chippkg == BCMA_PKG_ID_BCM4717)) {
					nphy_adj_tone_id_buf[0] = 32;
					nphy_adj_noise_var_buf[0] = 0x21f;
				} else {
					nphy_adj_tone_id_buf[0] = 0;
					nphy_adj_noise_var_buf[0] = 0x0;
				}
				break;
			case 134:
				nphy_adj_tone_id_buf[0] = 32;
				nphy_adj_noise_var_buf[0] = 0x21f;
				break;
			case 151:
				nphy_adj_tone_id_buf[0] = 16;
				nphy_adj_noise_var_buf[0] = 0x23f;
				break;
			case 153:
			case 161:
				nphy_adj_tone_id_buf[0] = 48;
				nphy_adj_noise_var_buf[0] = 0x23f;
				break;
			default:
				nphy_adj_tone_id_buf[0] = 0;
				nphy_adj_noise_var_buf[0] = 0x0;
				break;
			}

			if (nphy_adj_tone_id_buf[0]
			    && nphy_adj_noise_var_buf[0])
				wlc_phy_adjust_min_noisevar_nphy(
					pi, 1,
					nphy_adj_tone_id_buf,
					nphy_adj_noise_var_buf);
			else
				wlc_phy_adjust_min_noisevar_nphy(pi, 0, NULL,
								 NULL);
		}

		if (pi->phyhang_avoid)
			wlc_phy_stay_in_carriersearch_nphy(pi, false);
	}
}