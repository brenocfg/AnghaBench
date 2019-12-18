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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct ieee80211_channel {int /*<<< orphan*/  center_freq; } ;
struct ath5k_pdgain_info {int pd_points; int /*<<< orphan*/  pd_step; int /*<<< orphan*/ * pd_pwr; } ;
struct TYPE_4__ {size_t** tmpL; size_t** tmpR; int txp_offset; int txp_setup; int /*<<< orphan*/  txp_min_idx; void* txp_max_pwr; void* txp_min_pwr; } ;
struct ath5k_eeprom_info {size_t** ee_pdc_to_idx; int* ee_pd_gains; } ;
struct TYPE_3__ {struct ath5k_eeprom_info cap_eeprom; } ;
struct ath5k_hw {TYPE_2__ ah_txpower; TYPE_1__ ah_capabilities; } ;
struct ath5k_chan_pcal_info {int min_pwr; int max_pwr; scalar_t__ freq; struct ath5k_pdgain_info* pd_curves; } ;
typedef  int s16 ;

/* Variables and functions */
 int AR5K_EEPROM_N_PD_GAINS ; 
 int AR5K_EEPROM_POWER_TABLE_SIZE ; 
#define  AR5K_PWRTABLE_LINEAR_PCDAC 130 
#define  AR5K_PWRTABLE_PWR_TO_PCDAC 129 
#define  AR5K_PWRTABLE_PWR_TO_PDADC 128 
 int EINVAL ; 
 int /*<<< orphan*/  ath5k_combine_linear_pcdac_curves (struct ath5k_hw*,int*,int*,int) ; 
 int /*<<< orphan*/  ath5k_combine_pwr_to_pdadc_curves (struct ath5k_hw*,int*,int*,int) ; 
 int /*<<< orphan*/  ath5k_create_power_curve (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,size_t*,size_t) ; 
 int /*<<< orphan*/  ath5k_fill_pwr_to_pcdac_table (struct ath5k_hw*,int*,int*) ; 
 int /*<<< orphan*/  ath5k_get_chan_pcal_surrounding_piers (struct ath5k_hw*,struct ieee80211_channel*,struct ath5k_chan_pcal_info**,struct ath5k_chan_pcal_info**) ; 
 void* ath5k_get_interpolated_value (int /*<<< orphan*/ ,int,int,int,int) ; 
 int ath5k_get_linear_pcdac_min (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath5k_setup_channel_powertable(struct ath5k_hw *ah,
			struct ieee80211_channel *channel,
			u8 ee_mode, u8 type)
{
	struct ath5k_pdgain_info *pdg_L, *pdg_R;
	struct ath5k_chan_pcal_info *pcinfo_L;
	struct ath5k_chan_pcal_info *pcinfo_R;
	struct ath5k_eeprom_info *ee = &ah->ah_capabilities.cap_eeprom;
	u8 *pdg_curve_to_idx = ee->ee_pdc_to_idx[ee_mode];
	s16 table_min[AR5K_EEPROM_N_PD_GAINS];
	s16 table_max[AR5K_EEPROM_N_PD_GAINS];
	u8 *tmpL;
	u8 *tmpR;
	u32 target = channel->center_freq;
	int pdg, i;

	/* Get surrounding freq piers for this channel */
	ath5k_get_chan_pcal_surrounding_piers(ah, channel,
						&pcinfo_L,
						&pcinfo_R);

	/* Loop over pd gain curves on
	 * surrounding freq piers by index */
	for (pdg = 0; pdg < ee->ee_pd_gains[ee_mode]; pdg++) {

		/* Fill curves in reverse order
		 * from lower power (max gain)
		 * to higher power. Use curve -> idx
		 * backmapping we did on eeprom init */
		u8 idx = pdg_curve_to_idx[pdg];

		/* Grab the needed curves by index */
		pdg_L = &pcinfo_L->pd_curves[idx];
		pdg_R = &pcinfo_R->pd_curves[idx];

		/* Initialize the temp tables */
		tmpL = ah->ah_txpower.tmpL[pdg];
		tmpR = ah->ah_txpower.tmpR[pdg];

		/* Set curve's x boundaries and create
		 * curves so that they cover the same
		 * range (if we don't do that one table
		 * will have values on some range and the
		 * other one won't have any so interpolation
		 * will fail) */
		table_min[pdg] = min(pdg_L->pd_pwr[0],
					pdg_R->pd_pwr[0]) / 2;

		table_max[pdg] = max(pdg_L->pd_pwr[pdg_L->pd_points - 1],
				pdg_R->pd_pwr[pdg_R->pd_points - 1]) / 2;

		/* Now create the curves on surrounding channels
		 * and interpolate if needed to get the final
		 * curve for this gain on this channel */
		switch (type) {
		case AR5K_PWRTABLE_LINEAR_PCDAC:
			/* Override min/max so that we don't loose
			 * accuracy (don't divide by 2) */
			table_min[pdg] = min(pdg_L->pd_pwr[0],
						pdg_R->pd_pwr[0]);

			table_max[pdg] =
				max(pdg_L->pd_pwr[pdg_L->pd_points - 1],
					pdg_R->pd_pwr[pdg_R->pd_points - 1]);

			/* Override minimum so that we don't get
			 * out of bounds while extrapolating
			 * below. Don't do this when we have 2
			 * curves and we are on the high power curve
			 * because table_min is ok in this case */
			if (!(ee->ee_pd_gains[ee_mode] > 1 && pdg == 0)) {

				table_min[pdg] =
					ath5k_get_linear_pcdac_min(pdg_L->pd_step,
								pdg_R->pd_step,
								pdg_L->pd_pwr,
								pdg_R->pd_pwr);

				/* Don't go too low because we will
				 * miss the upper part of the curve.
				 * Note: 126 = 31.5dB (max power supported)
				 * in 0.25dB units */
				if (table_max[pdg] - table_min[pdg] > 126)
					table_min[pdg] = table_max[pdg] - 126;
			}

			/* Fall through */
		case AR5K_PWRTABLE_PWR_TO_PCDAC:
		case AR5K_PWRTABLE_PWR_TO_PDADC:

			ath5k_create_power_curve(table_min[pdg],
						table_max[pdg],
						pdg_L->pd_pwr,
						pdg_L->pd_step,
						pdg_L->pd_points, tmpL, type);

			/* We are in a calibration
			 * pier, no need to interpolate
			 * between freq piers */
			if (pcinfo_L == pcinfo_R)
				continue;

			ath5k_create_power_curve(table_min[pdg],
						table_max[pdg],
						pdg_R->pd_pwr,
						pdg_R->pd_step,
						pdg_R->pd_points, tmpR, type);
			break;
		default:
			return -EINVAL;
		}

		/* Interpolate between curves
		 * of surrounding freq piers to
		 * get the final curve for this
		 * pd gain. Re-use tmpL for interpolation
		 * output */
		for (i = 0; (i < (u16) (table_max[pdg] - table_min[pdg])) &&
		(i < AR5K_EEPROM_POWER_TABLE_SIZE); i++) {
			tmpL[i] = (u8) ath5k_get_interpolated_value(target,
							(s16) pcinfo_L->freq,
							(s16) pcinfo_R->freq,
							(s16) tmpL[i],
							(s16) tmpR[i]);
		}
	}

	/* Now we have a set of curves for this
	 * channel on tmpL (x range is table_max - table_min
	 * and y values are tmpL[pdg][]) sorted in the same
	 * order as EEPROM (because we've used the backmapping).
	 * So for RF5112 it's from higher power to lower power
	 * and for RF2413 it's from lower power to higher power.
	 * For RF5111 we only have one curve. */

	/* Fill min and max power levels for this
	 * channel by interpolating the values on
	 * surrounding channels to complete the dataset */
	ah->ah_txpower.txp_min_pwr = ath5k_get_interpolated_value(target,
					(s16) pcinfo_L->freq,
					(s16) pcinfo_R->freq,
					pcinfo_L->min_pwr, pcinfo_R->min_pwr);

	ah->ah_txpower.txp_max_pwr = ath5k_get_interpolated_value(target,
					(s16) pcinfo_L->freq,
					(s16) pcinfo_R->freq,
					pcinfo_L->max_pwr, pcinfo_R->max_pwr);

	/* Fill PCDAC/PDADC table */
	switch (type) {
	case AR5K_PWRTABLE_LINEAR_PCDAC:
		/* For RF5112 we can have one or two curves
		 * and each curve covers a certain power lvl
		 * range so we need to do some more processing */
		ath5k_combine_linear_pcdac_curves(ah, table_min, table_max,
						ee->ee_pd_gains[ee_mode]);

		/* Set txp.offset so that we can
		 * match max power value with max
		 * table index */
		ah->ah_txpower.txp_offset = 64 - (table_max[0] / 2);
		break;
	case AR5K_PWRTABLE_PWR_TO_PCDAC:
		/* We are done for RF5111 since it has only
		 * one curve, just fit the curve on the table */
		ath5k_fill_pwr_to_pcdac_table(ah, table_min, table_max);

		/* No rate powertable adjustment for RF5111 */
		ah->ah_txpower.txp_min_idx = 0;
		ah->ah_txpower.txp_offset = 0;
		break;
	case AR5K_PWRTABLE_PWR_TO_PDADC:
		/* Set PDADC boundaries and fill
		 * final PDADC table */
		ath5k_combine_pwr_to_pdadc_curves(ah, table_min, table_max,
						ee->ee_pd_gains[ee_mode]);

		/* Set txp.offset, note that table_min
		 * can be negative */
		ah->ah_txpower.txp_offset = table_min[0];
		break;
	default:
		return -EINVAL;
	}

	ah->ah_txpower.txp_setup = true;

	return 0;
}