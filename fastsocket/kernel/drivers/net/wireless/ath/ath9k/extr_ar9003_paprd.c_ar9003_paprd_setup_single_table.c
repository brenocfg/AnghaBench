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
typedef  int u32 ;
struct TYPE_2__ {int max_txchains; } ;
struct ath_hw {int paprd_ratemask; int paprd_target_power; int paprd_training_power; int paprd_ratemask_ht40; int /*<<< orphan*/  curchan; TYPE_1__ caps; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int const AR_PHY_PAPRD_AM2AM ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_AM2AM_MASK ; 
 int const AR_PHY_PAPRD_AM2PM ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_AM2PM_MASK ; 
#define  AR_PHY_PAPRD_CTRL0_B0 133 
#define  AR_PHY_PAPRD_CTRL0_B1 132 
#define  AR_PHY_PAPRD_CTRL0_B2 131 
 int /*<<< orphan*/  AR_PHY_PAPRD_CTRL0_PAPRD_MAG_THRSH ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_CTRL0_USE_SINGLE_TABLE_MASK ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_CTRL1_ADAPTIVE_AM2AM_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_CTRL1_ADAPTIVE_AM2PM_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_CTRL1_ADAPTIVE_SCALING_ENA ; 
#define  AR_PHY_PAPRD_CTRL1_B0 130 
#define  AR_PHY_PAPRD_CTRL1_B1 129 
#define  AR_PHY_PAPRD_CTRL1_B2 128 
 int /*<<< orphan*/  AR_PHY_PAPRD_CTRL1_PAPRD_MAG_SCALE_FACT ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_CTRL1_PA_GAIN_SCALE_FACT_MASK ; 
 int const AR_PHY_PAPRD_HT40 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_HT40_MASK ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_0_B0 ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_1_B0 ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_2_B0 ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_3_B0 ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_4_B0 ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_5_B0 ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_6_B0 ; 
 int const AR_PHY_PAPRD_PRE_POST_SCALE_7_B0 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_PRE_POST_SCALING ; 
 int const AR_PHY_PAPRD_TRAINER_CNTL1 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL1_CF_CF_PAPRD_TRAIN_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_AGC2_SETTLING ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_IQCORR_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_LB_ENABLE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_LB_SKIP ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_RX_BB_GAIN_FORCE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_TX_GAIN_FORCE ; 
 int const AR_PHY_PAPRD_TRAINER_CNTL2 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL2_CF_PAPRD_INIT_RX_BB_GAIN ; 
 int const AR_PHY_PAPRD_TRAINER_CNTL3 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_ADC_DESIRED_SIZE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_BBTXMIX_DISABLE ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_COARSE_CORR_LEN ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_FINE_CORR_LEN ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_MIN_LOOPBACK_DEL ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_NUM_CORR_STAGES ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP ; 
 int const AR_PHY_PAPRD_TRAINER_CNTL4 ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_MIN_CORR ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_NUM_TRAIN_SAMPLES ; 
 int /*<<< orphan*/  AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_SAFETY_DELTA ; 
 scalar_t__ AR_SREV_9330 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9462 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9485 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  CALIBRATE ; 
 int ERANGE ; 
 scalar_t__ IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int const,int /*<<< orphan*/ ,int) ; 
 int ar9003_get_training_power_2g (struct ath_hw*) ; 
 int ar9003_get_training_power_5g (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_paprd_enable (struct ath_hw*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ar9003_paprd_setup_single_table(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);
	static const u32 ctrl0[3] = {
		AR_PHY_PAPRD_CTRL0_B0,
		AR_PHY_PAPRD_CTRL0_B1,
		AR_PHY_PAPRD_CTRL0_B2
	};
	static const u32 ctrl1[3] = {
		AR_PHY_PAPRD_CTRL1_B0,
		AR_PHY_PAPRD_CTRL1_B1,
		AR_PHY_PAPRD_CTRL1_B2
	};
	int training_power;
	int i, val;
	u32 am2pm_mask = ah->paprd_ratemask;

	if (IS_CHAN_2GHZ(ah->curchan))
		training_power = ar9003_get_training_power_2g(ah);
	else
		training_power = ar9003_get_training_power_5g(ah);

	ath_dbg(common, CALIBRATE, "Training power: %d, Target power: %d\n",
		training_power, ah->paprd_target_power);

	if (training_power < 0) {
		ath_dbg(common, CALIBRATE,
			"PAPRD target power delta out of range\n");
		return -ERANGE;
	}
	ah->paprd_training_power = training_power;

	if (AR_SREV_9330(ah))
		am2pm_mask = 0;

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_AM2AM, AR_PHY_PAPRD_AM2AM_MASK,
		      ah->paprd_ratemask);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_AM2PM, AR_PHY_PAPRD_AM2PM_MASK,
		      am2pm_mask);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_HT40, AR_PHY_PAPRD_HT40_MASK,
		      ah->paprd_ratemask_ht40);

	ath_dbg(common, CALIBRATE, "PAPRD HT20 mask: 0x%x, HT40 mask: 0x%x\n",
		ah->paprd_ratemask, ah->paprd_ratemask_ht40);

	for (i = 0; i < ah->caps.max_txchains; i++) {
		REG_RMW_FIELD(ah, ctrl0[i],
			      AR_PHY_PAPRD_CTRL0_USE_SINGLE_TABLE_MASK, 1);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_AM2PM_ENABLE, 1);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_AM2AM_ENABLE, 1);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_SCALING_ENA, 0);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_PA_GAIN_SCALE_FACT_MASK, 181);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_PAPRD_MAG_SCALE_FACT, 361);
		REG_RMW_FIELD(ah, ctrl1[i],
			      AR_PHY_PAPRD_CTRL1_ADAPTIVE_SCALING_ENA, 0);
		REG_RMW_FIELD(ah, ctrl0[i],
			      AR_PHY_PAPRD_CTRL0_PAPRD_MAG_THRSH, 3);
	}

	ar9003_paprd_enable(ah, false);

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_LB_SKIP, 0x30);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_LB_ENABLE, 1);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_TX_GAIN_FORCE, 1);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_RX_BB_GAIN_FORCE, 0);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_IQCORR_ENABLE, 0);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_PAPRD_AGC2_SETTLING, 28);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL1,
		      AR_PHY_PAPRD_TRAINER_CNTL1_CF_CF_PAPRD_TRAIN_ENABLE, 1);

	if (AR_SREV_9485(ah)) {
		val = 148;
	} else {
		if (IS_CHAN_2GHZ(ah->curchan)) {
			if (AR_SREV_9462(ah) || AR_SREV_9565(ah))
				val = 145;
			else
				val = 147;
		} else {
			val = 137;
		}
	}

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL2,
		      AR_PHY_PAPRD_TRAINER_CNTL2_CF_PAPRD_INIT_RX_BB_GAIN, val);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_FINE_CORR_LEN, 4);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_COARSE_CORR_LEN, 4);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_NUM_CORR_STAGES, 7);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_MIN_LOOPBACK_DEL, 1);

	if (AR_SREV_9485(ah) ||
	    AR_SREV_9462(ah) ||
	    AR_SREV_9565(ah) ||
	    AR_SREV_9550(ah) ||
	    AR_SREV_9330(ah) ||
	    AR_SREV_9340(ah))
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
			      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, -3);
	else
		REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
			      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_QUICK_DROP, -6);

	val = -10;

	if (IS_CHAN_2GHZ(ah->curchan) && !AR_SREV_9462(ah) && !AR_SREV_9565(ah))
		val = -15;

	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_ADC_DESIRED_SIZE,
		      val);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL3,
		      AR_PHY_PAPRD_TRAINER_CNTL3_CF_PAPRD_BBTXMIX_DISABLE, 1);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL4,
		      AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_SAFETY_DELTA, 0);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL4,
		      AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_MIN_CORR, 400);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_TRAINER_CNTL4,
		      AR_PHY_PAPRD_TRAINER_CNTL4_CF_PAPRD_NUM_TRAIN_SAMPLES,
		      100);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_0_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 261376);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_1_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 248079);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_2_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 233759);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_3_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 220464);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_4_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 208194);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_5_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 196949);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_6_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 185706);
	REG_RMW_FIELD(ah, AR_PHY_PAPRD_PRE_POST_SCALE_7_B0,
		      AR_PHY_PAPRD_PRE_POST_SCALING, 175487);
	return 0;
}