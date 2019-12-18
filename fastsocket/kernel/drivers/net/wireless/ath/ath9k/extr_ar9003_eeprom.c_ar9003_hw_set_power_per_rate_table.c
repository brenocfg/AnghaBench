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
typedef  int u8 ;
typedef  size_t u16 ;
struct chan_centers {size_t synth_center; size_t ext_center; size_t ctl_center; } ;
struct ar9300_eeprom {int* ctlIndex_2G; int* ctlIndex_5G; } ;
struct TYPE_2__ {struct ar9300_eeprom ar9300_eep; } ;
struct ath_hw {TYPE_1__ eeprom; } ;
struct ath_common {int dummy; } ;
struct ath9k_channel {size_t channel; } ;

/* Variables and functions */
 int ALL_TARGET_HT20_0_8_16 ; 
 int ALL_TARGET_HT20_23 ; 
 int ALL_TARGET_HT40_0_8_16 ; 
 int ALL_TARGET_HT40_23 ; 
 int ALL_TARGET_LEGACY_11S ; 
 int ALL_TARGET_LEGACY_1L_5L ; 
 int ALL_TARGET_LEGACY_54 ; 
 int ALL_TARGET_LEGACY_6_24 ; 
 int AR9300_NUM_CTLS_2G ; 
 int AR9300_NUM_CTLS_5G ; 
 size_t ARRAY_SIZE (size_t const*) ; 
#define  CTL_11A 137 
#define  CTL_11A_EXT 136 
#define  CTL_11B 135 
#define  CTL_11B_EXT 134 
#define  CTL_11G 133 
#define  CTL_11G_EXT 132 
#define  CTL_2GHT20 131 
#define  CTL_2GHT40 130 
#define  CTL_5GHT20 129 
#define  CTL_5GHT40 128 
 size_t CTL_MODE_M ; 
 size_t const EXT_ADDITIVE ; 
 int IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 scalar_t__ IS_CHAN_HT40 (struct ath9k_channel*) ; 
 size_t MAX_RATE_POWER ; 
 int /*<<< orphan*/  REGULATORY ; 
 int SD_NO_CTL ; 
 size_t SUB_NUM_CTL_MODES_AT_2G_40 ; 
 size_t SUB_NUM_CTL_MODES_AT_5G_40 ; 
 size_t ar9003_hw_get_max_edge_power (struct ar9300_eeprom*,size_t,int,int) ; 
 size_t ar9003_mci_get_max_txpower (struct ath_hw*,size_t const) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_get_channel_centers (struct ath_hw*,struct ath9k_channel*,struct chan_centers*) ; 
 size_t ath9k_hw_get_scaled_power (struct ath_hw*,size_t,int) ; 
 int /*<<< orphan*/  ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t,size_t const,size_t const,size_t const,...) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static void ar9003_hw_set_power_per_rate_table(struct ath_hw *ah,
					       struct ath9k_channel *chan,
					       u8 *pPwrArray, u16 cfgCtl,
					       u8 antenna_reduction,
					       u16 powerLimit)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ar9300_eeprom *pEepData = &ah->eeprom.ar9300_eep;
	u16 twiceMaxEdgePower;
	int i;
	u16 scaledPower = 0, minCtlPower;
	static const u16 ctlModesFor11a[] = {
		CTL_11A, CTL_5GHT20, CTL_11A_EXT, CTL_5GHT40
	};
	static const u16 ctlModesFor11g[] = {
		CTL_11B, CTL_11G, CTL_2GHT20, CTL_11B_EXT,
		CTL_11G_EXT, CTL_2GHT40
	};
	u16 numCtlModes;
	const u16 *pCtlMode;
	u16 ctlMode, freq;
	struct chan_centers centers;
	u8 *ctlIndex;
	u8 ctlNum;
	u16 twiceMinEdgePower;
	bool is2ghz = IS_CHAN_2GHZ(chan);

	ath9k_hw_get_channel_centers(ah, chan, &centers);
	scaledPower = ath9k_hw_get_scaled_power(ah, powerLimit,
						antenna_reduction);

	if (is2ghz) {
		/* Setup for CTL modes */
		/* CTL_11B, CTL_11G, CTL_2GHT20 */
		numCtlModes =
			ARRAY_SIZE(ctlModesFor11g) -
				   SUB_NUM_CTL_MODES_AT_2G_40;
		pCtlMode = ctlModesFor11g;
		if (IS_CHAN_HT40(chan))
			/* All 2G CTL's */
			numCtlModes = ARRAY_SIZE(ctlModesFor11g);
	} else {
		/* Setup for CTL modes */
		/* CTL_11A, CTL_5GHT20 */
		numCtlModes = ARRAY_SIZE(ctlModesFor11a) -
					 SUB_NUM_CTL_MODES_AT_5G_40;
		pCtlMode = ctlModesFor11a;
		if (IS_CHAN_HT40(chan))
			/* All 5G CTL's */
			numCtlModes = ARRAY_SIZE(ctlModesFor11a);
	}

	/*
	 * For MIMO, need to apply regulatory caps individually across
	 * dynamically running modes: CCK, OFDM, HT20, HT40
	 *
	 * The outer loop walks through each possible applicable runtime mode.
	 * The inner loop walks through each ctlIndex entry in EEPROM.
	 * The ctl value is encoded as [7:4] == test group, [3:0] == test mode.
	 */
	for (ctlMode = 0; ctlMode < numCtlModes; ctlMode++) {
		bool isHt40CtlMode = (pCtlMode[ctlMode] == CTL_5GHT40) ||
			(pCtlMode[ctlMode] == CTL_2GHT40);
		if (isHt40CtlMode)
			freq = centers.synth_center;
		else if (pCtlMode[ctlMode] & EXT_ADDITIVE)
			freq = centers.ext_center;
		else
			freq = centers.ctl_center;

		ath_dbg(common, REGULATORY,
			"LOOP-Mode ctlMode %d < %d, isHt40CtlMode %d, EXT_ADDITIVE %d\n",
			ctlMode, numCtlModes, isHt40CtlMode,
			(pCtlMode[ctlMode] & EXT_ADDITIVE));

		/* walk through each CTL index stored in EEPROM */
		if (is2ghz) {
			ctlIndex = pEepData->ctlIndex_2G;
			ctlNum = AR9300_NUM_CTLS_2G;
		} else {
			ctlIndex = pEepData->ctlIndex_5G;
			ctlNum = AR9300_NUM_CTLS_5G;
		}

		twiceMaxEdgePower = MAX_RATE_POWER;
		for (i = 0; (i < ctlNum) && ctlIndex[i]; i++) {
			ath_dbg(common, REGULATORY,
				"LOOP-Ctlidx %d: cfgCtl 0x%2.2x pCtlMode 0x%2.2x ctlIndex 0x%2.2x chan %d\n",
				i, cfgCtl, pCtlMode[ctlMode], ctlIndex[i],
				chan->channel);

			/*
			 * compare test group from regulatory
			 * channel list with test mode from pCtlMode
			 * list
			 */
			if ((((cfgCtl & ~CTL_MODE_M) |
			       (pCtlMode[ctlMode] & CTL_MODE_M)) ==
				ctlIndex[i]) ||
			    (((cfgCtl & ~CTL_MODE_M) |
			       (pCtlMode[ctlMode] & CTL_MODE_M)) ==
			     ((ctlIndex[i] & CTL_MODE_M) |
			       SD_NO_CTL))) {
				twiceMinEdgePower =
				  ar9003_hw_get_max_edge_power(pEepData,
							       freq, i,
							       is2ghz);

				if ((cfgCtl & ~CTL_MODE_M) == SD_NO_CTL)
					/*
					 * Find the minimum of all CTL
					 * edge powers that apply to
					 * this channel
					 */
					twiceMaxEdgePower =
						min(twiceMaxEdgePower,
						    twiceMinEdgePower);
				else {
					/* specific */
					twiceMaxEdgePower = twiceMinEdgePower;
					break;
				}
			}
		}

		minCtlPower = (u8)min(twiceMaxEdgePower, scaledPower);

		ath_dbg(common, REGULATORY,
			"SEL-Min ctlMode %d pCtlMode %d 2xMaxEdge %d sP %d minCtlPwr %d\n",
			ctlMode, pCtlMode[ctlMode], twiceMaxEdgePower,
			scaledPower, minCtlPower);

		/* Apply ctl mode to correct target power set */
		switch (pCtlMode[ctlMode]) {
		case CTL_11B:
			for (i = ALL_TARGET_LEGACY_1L_5L;
			     i <= ALL_TARGET_LEGACY_11S; i++)
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
			break;
		case CTL_11A:
		case CTL_11G:
			for (i = ALL_TARGET_LEGACY_6_24;
			     i <= ALL_TARGET_LEGACY_54; i++)
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
			break;
		case CTL_5GHT20:
		case CTL_2GHT20:
			for (i = ALL_TARGET_HT20_0_8_16;
			     i <= ALL_TARGET_HT20_23; i++) {
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
				if (ath9k_hw_mci_is_enabled(ah))
					pPwrArray[i] =
						(u8)min((u16)pPwrArray[i],
						ar9003_mci_get_max_txpower(ah,
							pCtlMode[ctlMode]));
			}
			break;
		case CTL_5GHT40:
		case CTL_2GHT40:
			for (i = ALL_TARGET_HT40_0_8_16;
			     i <= ALL_TARGET_HT40_23; i++) {
				pPwrArray[i] = (u8)min((u16)pPwrArray[i],
						       minCtlPower);
				if (ath9k_hw_mci_is_enabled(ah))
					pPwrArray[i] =
						(u8)min((u16)pPwrArray[i],
						ar9003_mci_get_max_txpower(ah,
							pCtlMode[ctlMode]));
			}
			break;
		default:
			break;
		}
	} /* end ctl mode checking */
}