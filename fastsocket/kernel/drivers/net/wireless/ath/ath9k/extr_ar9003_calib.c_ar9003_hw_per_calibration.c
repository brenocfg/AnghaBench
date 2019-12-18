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
struct ath_hw {scalar_t__ cal_samples; struct ath9k_hw_cal_data* caldata; } ;
struct ath9k_hw_cal_data {int CalValid; } ;
struct ath9k_channel {int dummy; } ;
struct ath9k_cal_list {scalar_t__ calState; TYPE_1__* calData; } ;
struct TYPE_2__ {scalar_t__ calNumSamples; int calType; int /*<<< orphan*/  (* calPostProc ) (struct ath_hw*,unsigned int) ;int /*<<< orphan*/  (* calCollect ) (struct ath_hw*) ;} ;

/* Variables and functions */
 unsigned int AR9300_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_PHY_TIMING4 ; 
 int AR_PHY_TIMING4_DO_CAL ; 
 scalar_t__ CAL_DONE ; 
 scalar_t__ CAL_RUNNING ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9003_hw_setup_calibration (struct ath_hw*,struct ath9k_cal_list*) ; 
 int /*<<< orphan*/  ath9k_hw_reset_calibration (struct ath_hw*,struct ath9k_cal_list*) ; 
 int /*<<< orphan*/  stub1 (struct ath_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ath_hw*,unsigned int) ; 

__attribute__((used)) static bool ar9003_hw_per_calibration(struct ath_hw *ah,
				      struct ath9k_channel *ichan,
				      u8 rxchainmask,
				      struct ath9k_cal_list *currCal)
{
	struct ath9k_hw_cal_data *caldata = ah->caldata;
	/* Cal is assumed not done until explicitly set below */
	bool iscaldone = false;

	/* Calibration in progress. */
	if (currCal->calState == CAL_RUNNING) {
		/* Check to see if it has finished. */
		if (!(REG_READ(ah, AR_PHY_TIMING4) & AR_PHY_TIMING4_DO_CAL)) {
			/*
			* Accumulate cal measures for active chains
			*/
			currCal->calData->calCollect(ah);
			ah->cal_samples++;

			if (ah->cal_samples >=
			    currCal->calData->calNumSamples) {
				unsigned int i, numChains = 0;
				for (i = 0; i < AR9300_MAX_CHAINS; i++) {
					if (rxchainmask & (1 << i))
						numChains++;
				}

				/*
				* Process accumulated data
				*/
				currCal->calData->calPostProc(ah, numChains);

				/* Calibration has finished. */
				caldata->CalValid |= currCal->calData->calType;
				currCal->calState = CAL_DONE;
				iscaldone = true;
			} else {
			/*
			 * Set-up collection of another sub-sample until we
			 * get desired number
			 */
			ar9003_hw_setup_calibration(ah, currCal);
			}
		}
	} else if (!(caldata->CalValid & currCal->calData->calType)) {
		/* If current cal is marked invalid in channel, kick it off */
		ath9k_hw_reset_calibration(ah, currCal);
	}

	return iscaldone;
}