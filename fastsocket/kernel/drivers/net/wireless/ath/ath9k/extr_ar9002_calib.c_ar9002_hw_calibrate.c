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
typedef  int /*<<< orphan*/  u8 ;
struct ath_hw {int /*<<< orphan*/  curchan; struct ath9k_cal_list* cal_list_curr; TYPE_1__* caldata; } ;
struct ath9k_channel {int dummy; } ;
struct ath9k_cal_list {scalar_t__ calState; struct ath9k_cal_list* calNext; } ;
struct TYPE_2__ {int nfcal_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int AR_PHY_AGC_CONTROL_NF ; 
 scalar_t__ CAL_RUNNING ; 
 scalar_t__ CAL_WAITING ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9002_hw_olc_temp_compensation (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9002_hw_pa_cal (struct ath_hw*,int) ; 
 int ar9002_hw_per_calibration (struct ath_hw*,struct ath9k_channel*,int /*<<< orphan*/ ,struct ath9k_cal_list*) ; 
 scalar_t__ ath9k_hw_getnf (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ath9k_hw_loadnf (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_reset_calibration (struct ath_hw*,struct ath9k_cal_list*) ; 
 int /*<<< orphan*/  ath9k_hw_start_nfcal (struct ath_hw*,int) ; 

__attribute__((used)) static bool ar9002_hw_calibrate(struct ath_hw *ah,
				struct ath9k_channel *chan,
				u8 rxchainmask,
				bool longcal)
{
	bool iscaldone = true;
	struct ath9k_cal_list *currCal = ah->cal_list_curr;
	bool nfcal, nfcal_pending = false;

	nfcal = !!(REG_READ(ah, AR_PHY_AGC_CONTROL) & AR_PHY_AGC_CONTROL_NF);
	if (ah->caldata)
		nfcal_pending = ah->caldata->nfcal_pending;

	if (currCal && !nfcal &&
	    (currCal->calState == CAL_RUNNING ||
	     currCal->calState == CAL_WAITING)) {
		iscaldone = ar9002_hw_per_calibration(ah, chan,
						      rxchainmask, currCal);
		if (iscaldone) {
			ah->cal_list_curr = currCal = currCal->calNext;

			if (currCal->calState == CAL_WAITING) {
				iscaldone = false;
				ath9k_hw_reset_calibration(ah, currCal);
			}
		}
	}

	/* Do NF cal only at longer intervals */
	if (longcal || nfcal_pending) {
		/*
		 * Get the value from the previous NF cal and update
		 * history buffer.
		 */
		if (ath9k_hw_getnf(ah, chan)) {
			/*
			 * Load the NF from history buffer of the current
			 * channel.
			 * NF is slow time-variant, so it is OK to use a
			 * historical value.
			 */
			ath9k_hw_loadnf(ah, ah->curchan);
		}

		if (longcal) {
			ath9k_hw_start_nfcal(ah, false);
			/* Do periodic PAOffset Cal */
			ar9002_hw_pa_cal(ah, false);
			ar9002_hw_olc_temp_compensation(ah);
		}
	}

	return iscaldone;
}