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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  ast_ani_spurdown; int /*<<< orphan*/  ast_ani_spurup; int /*<<< orphan*/  ast_ani_stepdown; int /*<<< orphan*/  ast_ani_stepup; int /*<<< orphan*/  ast_ani_ofdmoff; int /*<<< orphan*/  ast_ani_ofdmon; } ;
struct ath_hw {int ani_function; TYPE_1__ stats; struct ath9k_channel* curchan; } ;
struct ath_common {int dummy; } ;
struct TYPE_4__ {int m1ThreshLow; int m2ThreshLow; int m1Thresh; int m2Thresh; int m2CountThr; int m2CountThrLow; int m1ThreshLowExt; int m2ThreshLowExt; int m1ThreshExt; int m2ThreshExt; int firstep; int firstepLow; int cycpwrThr1; int cycpwrThr1Ext; } ;
struct ar5416AniState {size_t ofdmWeakSigDetect; size_t firstepLevel; size_t spurImmunityLevel; int /*<<< orphan*/  cckPhyErrCount; int /*<<< orphan*/  ofdmPhyErrCount; int /*<<< orphan*/  listenTime; scalar_t__ mrcCCK; TYPE_2__ iniDef; } ;
struct ath9k_channel {int /*<<< orphan*/  channel; struct ar5416AniState ani; } ;
typedef  int s32 ;
typedef  enum ath9k_ani_cmd { ____Placeholder_ath9k_ani_cmd } ath9k_ani_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 size_t ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  AR_PHY_EXT_CCA ; 
 int /*<<< orphan*/  AR_PHY_EXT_TIMING5_CYCPWR_THR1 ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_FIRSTEP ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_FIRSTEP_LOW ; 
 int /*<<< orphan*/  AR_PHY_FIND_SIG_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M1_THRESH ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M1_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M2_THRESH ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_EXT_M2_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW_M1_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW_M2_THRESH_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_LOW_USE_SELF_CORR_LOW ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_M1_THRESH ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_M2COUNT_THR ; 
 int /*<<< orphan*/  AR_PHY_SFCORR_M2_THRESH ; 
 int /*<<< orphan*/  AR_PHY_TIMING5 ; 
 int /*<<< orphan*/  AR_PHY_TIMING5_CYCPWR_THR1 ; 
#define  ATH9K_ANI_FIRSTEP_LEVEL 132 
 size_t ATH9K_ANI_FIRSTEP_LVL ; 
#define  ATH9K_ANI_MRC_CCK 131 
#define  ATH9K_ANI_OFDM_WEAK_SIGNAL_DETECTION 130 
#define  ATH9K_ANI_PRESENT 129 
 size_t ATH9K_ANI_SPUR_IMMUNE_LVL ; 
#define  ATH9K_ANI_SPUR_IMMUNITY_LEVEL 128 
 int ATH9K_SIG_FIRSTEP_SETTING_MAX ; 
 int ATH9K_SIG_FIRSTEP_SETTING_MIN ; 
 int ATH9K_SIG_SPUR_IMM_SETTING_MAX ; 
 int ATH9K_SIG_SPUR_IMM_SETTING_MIN ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,size_t,...) ; 
 int* cycpwrThr1_table ; 
 int* firstep_table ; 
 int m1ThreshExt_off ; 
 int m1ThreshLowExt_off ; 
 int m1ThreshLow_off ; 
 int m1Thresh_off ; 
 int m2CountThrLow_off ; 
 int m2CountThr_off ; 
 int m2ThreshExt_off ; 
 int m2ThreshLowExt_off ; 
 int m2ThreshLow_off ; 
 int m2Thresh_off ; 

__attribute__((used)) static bool ar5008_hw_ani_control_new(struct ath_hw *ah,
				      enum ath9k_ani_cmd cmd,
				      int param)
{
	struct ath_common *common = ath9k_hw_common(ah);
	struct ath9k_channel *chan = ah->curchan;
	struct ar5416AniState *aniState = &chan->ani;
	s32 value, value2;

	switch (cmd & ah->ani_function) {
	case ATH9K_ANI_OFDM_WEAK_SIGNAL_DETECTION:{
		/*
		 * on == 1 means ofdm weak signal detection is ON
		 * on == 1 is the default, for less noise immunity
		 *
		 * on == 0 means ofdm weak signal detection is OFF
		 * on == 0 means more noise imm
		 */
		u32 on = param ? 1 : 0;
		/*
		 * make register setting for default
		 * (weak sig detect ON) come from INI file
		 */
		int m1ThreshLow = on ?
			aniState->iniDef.m1ThreshLow : m1ThreshLow_off;
		int m2ThreshLow = on ?
			aniState->iniDef.m2ThreshLow : m2ThreshLow_off;
		int m1Thresh = on ?
			aniState->iniDef.m1Thresh : m1Thresh_off;
		int m2Thresh = on ?
			aniState->iniDef.m2Thresh : m2Thresh_off;
		int m2CountThr = on ?
			aniState->iniDef.m2CountThr : m2CountThr_off;
		int m2CountThrLow = on ?
			aniState->iniDef.m2CountThrLow : m2CountThrLow_off;
		int m1ThreshLowExt = on ?
			aniState->iniDef.m1ThreshLowExt : m1ThreshLowExt_off;
		int m2ThreshLowExt = on ?
			aniState->iniDef.m2ThreshLowExt : m2ThreshLowExt_off;
		int m1ThreshExt = on ?
			aniState->iniDef.m1ThreshExt : m1ThreshExt_off;
		int m2ThreshExt = on ?
			aniState->iniDef.m2ThreshExt : m2ThreshExt_off;

		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M1_THRESH_LOW,
			      m1ThreshLow);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M2_THRESH_LOW,
			      m2ThreshLow);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M1_THRESH, m1Thresh);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M2_THRESH, m2Thresh);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR,
			      AR_PHY_SFCORR_M2COUNT_THR, m2CountThr);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_LOW,
			      AR_PHY_SFCORR_LOW_M2COUNT_THR_LOW,
			      m2CountThrLow);

		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M1_THRESH_LOW, m1ThreshLowExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M2_THRESH_LOW, m2ThreshLowExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M1_THRESH, m1ThreshExt);
		REG_RMW_FIELD(ah, AR_PHY_SFCORR_EXT,
			      AR_PHY_SFCORR_EXT_M2_THRESH, m2ThreshExt);

		if (on)
			REG_SET_BIT(ah, AR_PHY_SFCORR_LOW,
				    AR_PHY_SFCORR_LOW_USE_SELF_CORR_LOW);
		else
			REG_CLR_BIT(ah, AR_PHY_SFCORR_LOW,
				    AR_PHY_SFCORR_LOW_USE_SELF_CORR_LOW);

		if (on != aniState->ofdmWeakSigDetect) {
			ath_dbg(common, ANI,
				"** ch %d: ofdm weak signal: %s=>%s\n",
				chan->channel,
				aniState->ofdmWeakSigDetect ?
				"on" : "off",
				on ? "on" : "off");
			if (on)
				ah->stats.ast_ani_ofdmon++;
			else
				ah->stats.ast_ani_ofdmoff++;
			aniState->ofdmWeakSigDetect = on;
		}
		break;
	}
	case ATH9K_ANI_FIRSTEP_LEVEL:{
		u32 level = param;

		if (level >= ARRAY_SIZE(firstep_table)) {
			ath_dbg(common, ANI,
				"ATH9K_ANI_FIRSTEP_LEVEL: level out of range (%u > %zu)\n",
				level, ARRAY_SIZE(firstep_table));
			return false;
		}

		/*
		 * make register setting relative to default
		 * from INI file & cap value
		 */
		value = firstep_table[level] -
			firstep_table[ATH9K_ANI_FIRSTEP_LVL] +
			aniState->iniDef.firstep;
		if (value < ATH9K_SIG_FIRSTEP_SETTING_MIN)
			value = ATH9K_SIG_FIRSTEP_SETTING_MIN;
		if (value > ATH9K_SIG_FIRSTEP_SETTING_MAX)
			value = ATH9K_SIG_FIRSTEP_SETTING_MAX;
		REG_RMW_FIELD(ah, AR_PHY_FIND_SIG,
			      AR_PHY_FIND_SIG_FIRSTEP,
			      value);
		/*
		 * we need to set first step low register too
		 * make register setting relative to default
		 * from INI file & cap value
		 */
		value2 = firstep_table[level] -
			 firstep_table[ATH9K_ANI_FIRSTEP_LVL] +
			 aniState->iniDef.firstepLow;
		if (value2 < ATH9K_SIG_FIRSTEP_SETTING_MIN)
			value2 = ATH9K_SIG_FIRSTEP_SETTING_MIN;
		if (value2 > ATH9K_SIG_FIRSTEP_SETTING_MAX)
			value2 = ATH9K_SIG_FIRSTEP_SETTING_MAX;

		REG_RMW_FIELD(ah, AR_PHY_FIND_SIG_LOW,
			      AR_PHY_FIND_SIG_FIRSTEP_LOW, value2);

		if (level != aniState->firstepLevel) {
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] firstep[level]=%d ini=%d\n",
				chan->channel,
				aniState->firstepLevel,
				level,
				ATH9K_ANI_FIRSTEP_LVL,
				value,
				aniState->iniDef.firstep);
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] firstep_low[level]=%d ini=%d\n",
				chan->channel,
				aniState->firstepLevel,
				level,
				ATH9K_ANI_FIRSTEP_LVL,
				value2,
				aniState->iniDef.firstepLow);
			if (level > aniState->firstepLevel)
				ah->stats.ast_ani_stepup++;
			else if (level < aniState->firstepLevel)
				ah->stats.ast_ani_stepdown++;
			aniState->firstepLevel = level;
		}
		break;
	}
	case ATH9K_ANI_SPUR_IMMUNITY_LEVEL:{
		u32 level = param;

		if (level >= ARRAY_SIZE(cycpwrThr1_table)) {
			ath_dbg(common, ANI,
				"ATH9K_ANI_SPUR_IMMUNITY_LEVEL: level out of range (%u > %zu)\n",
				level, ARRAY_SIZE(cycpwrThr1_table));
			return false;
		}
		/*
		 * make register setting relative to default
		 * from INI file & cap value
		 */
		value = cycpwrThr1_table[level] -
			cycpwrThr1_table[ATH9K_ANI_SPUR_IMMUNE_LVL] +
			aniState->iniDef.cycpwrThr1;
		if (value < ATH9K_SIG_SPUR_IMM_SETTING_MIN)
			value = ATH9K_SIG_SPUR_IMM_SETTING_MIN;
		if (value > ATH9K_SIG_SPUR_IMM_SETTING_MAX)
			value = ATH9K_SIG_SPUR_IMM_SETTING_MAX;
		REG_RMW_FIELD(ah, AR_PHY_TIMING5,
			      AR_PHY_TIMING5_CYCPWR_THR1,
			      value);

		/*
		 * set AR_PHY_EXT_CCA for extension channel
		 * make register setting relative to default
		 * from INI file & cap value
		 */
		value2 = cycpwrThr1_table[level] -
			 cycpwrThr1_table[ATH9K_ANI_SPUR_IMMUNE_LVL] +
			 aniState->iniDef.cycpwrThr1Ext;
		if (value2 < ATH9K_SIG_SPUR_IMM_SETTING_MIN)
			value2 = ATH9K_SIG_SPUR_IMM_SETTING_MIN;
		if (value2 > ATH9K_SIG_SPUR_IMM_SETTING_MAX)
			value2 = ATH9K_SIG_SPUR_IMM_SETTING_MAX;
		REG_RMW_FIELD(ah, AR_PHY_EXT_CCA,
			      AR_PHY_EXT_TIMING5_CYCPWR_THR1, value2);

		if (level != aniState->spurImmunityLevel) {
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] cycpwrThr1[level]=%d ini=%d\n",
				chan->channel,
				aniState->spurImmunityLevel,
				level,
				ATH9K_ANI_SPUR_IMMUNE_LVL,
				value,
				aniState->iniDef.cycpwrThr1);
			ath_dbg(common, ANI,
				"** ch %d: level %d=>%d[def:%d] cycpwrThr1Ext[level]=%d ini=%d\n",
				chan->channel,
				aniState->spurImmunityLevel,
				level,
				ATH9K_ANI_SPUR_IMMUNE_LVL,
				value2,
				aniState->iniDef.cycpwrThr1Ext);
			if (level > aniState->spurImmunityLevel)
				ah->stats.ast_ani_spurup++;
			else if (level < aniState->spurImmunityLevel)
				ah->stats.ast_ani_spurdown++;
			aniState->spurImmunityLevel = level;
		}
		break;
	}
	case ATH9K_ANI_MRC_CCK:
		/*
		 * You should not see this as AR5008, AR9001, AR9002
		 * does not have hardware support for MRC CCK.
		 */
		WARN_ON(1);
		break;
	case ATH9K_ANI_PRESENT:
		break;
	default:
		ath_dbg(common, ANI, "invalid cmd %u\n", cmd);
		return false;
	}

	ath_dbg(common, ANI,
		"ANI parameters: SI=%d, ofdmWS=%s FS=%d MRCcck=%s listenTime=%d ofdmErrs=%d cckErrs=%d\n",
		aniState->spurImmunityLevel,
		aniState->ofdmWeakSigDetect ? "on" : "off",
		aniState->firstepLevel,
		aniState->mrcCCK ? "on" : "off",
		aniState->listenTime,
		aniState->ofdmPhyErrCount,
		aniState->cckPhyErrCount);
	return true;
}