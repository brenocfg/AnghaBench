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
struct ath5k_rf_reg {int dummy; } ;
struct TYPE_2__ {size_t g_step_idx; int g_f_corr; } ;
struct ath5k_hw {scalar_t__ ah_radio; scalar_t__ ah_radio_5ghz_revision; int* ah_rf_banks; TYPE_1__ ah_gain; int /*<<< orphan*/  ah_rf_regs_count; } ;
struct ath5k_gain_opt_step {int* gos_param; } ;
struct ath5k_gain_opt {struct ath5k_gain_opt_step* go_step; } ;

/* Variables and functions */
 scalar_t__ AR5K_RF5112 ; 
 int /*<<< orphan*/  AR5K_RF_MIXGAIN_STEP ; 
 int /*<<< orphan*/  AR5K_RF_MIXVGA_OVR ; 
 scalar_t__ AR5K_SREV_RAD_5112A ; 
 int /*<<< orphan*/  ARRAY_SIZE (struct ath5k_rf_reg*) ; 
 int ath5k_hw_rfb_op (struct ath5k_hw*,struct ath5k_rf_reg const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ath5k_rf_reg* rf_regs_5112a ; 
 struct ath5k_gain_opt rfgain_opt_5112 ; 

__attribute__((used)) static u32
ath5k_hw_rf_gainf_corr(struct ath5k_hw *ah)
{
	u32 mix, step;
	u32 *rf;
	const struct ath5k_gain_opt *go;
	const struct ath5k_gain_opt_step *g_step;
	const struct ath5k_rf_reg *rf_regs;

	/* Only RF5112 Rev. 2 supports it */
	if ((ah->ah_radio != AR5K_RF5112) ||
	(ah->ah_radio_5ghz_revision <= AR5K_SREV_RAD_5112A))
		return 0;

	go = &rfgain_opt_5112;
	rf_regs = rf_regs_5112a;
	ah->ah_rf_regs_count = ARRAY_SIZE(rf_regs_5112a);

	g_step = &go->go_step[ah->ah_gain.g_step_idx];

	if (ah->ah_rf_banks == NULL)
		return 0;

	rf = ah->ah_rf_banks;
	ah->ah_gain.g_f_corr = 0;

	/* No VGA (Variable Gain Amplifier) override, skip */
	if (ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_MIXVGA_OVR, false) != 1)
		return 0;

	/* Mix gain stepping */
	step = ath5k_hw_rfb_op(ah, rf_regs, 0, AR5K_RF_MIXGAIN_STEP, false);

	/* Mix gain override */
	mix = g_step->gos_param[0];

	switch (mix) {
	case 3:
		ah->ah_gain.g_f_corr = step * 2;
		break;
	case 2:
		ah->ah_gain.g_f_corr = (step - 5) * 2;
		break;
	case 1:
		ah->ah_gain.g_f_corr = step;
		break;
	default:
		ah->ah_gain.g_f_corr = 0;
		break;
	}

	return ah->ah_gain.g_f_corr;
}