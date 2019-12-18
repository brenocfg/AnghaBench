#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
struct ath9k_hw_capabilities {int hw_caps; } ;
struct ath_hw {struct ath9k_hw_capabilities caps; } ;
struct ath_common {int dummy; } ;
struct ath9k_beacon_state {scalar_t__ bs_nexttbtt; scalar_t__ bs_intval; scalar_t__ bs_sleepduration; scalar_t__ bs_dtimperiod; scalar_t__ bs_nextdtim; int bs_tsfoor_threshold; int /*<<< orphan*/  bs_bmissthreshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BEACON_PERIOD ; 
 int /*<<< orphan*/  AR_DMA_BEACON_PERIOD ; 
 int /*<<< orphan*/  AR_DTIM_PERIOD ; 
 int AR_DTIM_TIMER_EN ; 
 int /*<<< orphan*/  AR_NEXT_DTIM ; 
 int /*<<< orphan*/  AR_NEXT_TBTT_TIMER ; 
 int /*<<< orphan*/  AR_NEXT_TIM ; 
 int /*<<< orphan*/  AR_RSSI_THR ; 
 int /*<<< orphan*/  AR_RSSI_THR_BM_THR ; 
 int /*<<< orphan*/  AR_SLEEP1 ; 
 int AR_SLEEP1_ASSUME_DTIM ; 
 int /*<<< orphan*/  AR_SLEEP1_CAB_TIMEOUT ; 
 int /*<<< orphan*/  AR_SLEEP2 ; 
 int /*<<< orphan*/  AR_SLEEP2_BEACON_TIMEOUT ; 
 int AR_TBTT_TIMER_EN ; 
 int /*<<< orphan*/  AR_TIMER_MODE ; 
 int /*<<< orphan*/  AR_TIM_PERIOD ; 
 int AR_TIM_TIMER_EN ; 
 int /*<<< orphan*/  AR_TSFOOR_THRESHOLD ; 
 int ATH9K_HW_CAP_AUTOSLEEP ; 
 int /*<<< orphan*/  BEACON ; 
 int BEACON_TIMEOUT_VAL ; 
 int CAB_TIMEOUT_VAL ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 scalar_t__ MIN_BEACON_TIMEOUT_VAL ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SLEEP_SLOP ; 
 int SM (scalar_t__,int /*<<< orphan*/ ) ; 
 int TU_TO_USEC (scalar_t__) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

void ath9k_hw_set_sta_beacon_timers(struct ath_hw *ah,
				    const struct ath9k_beacon_state *bs)
{
	u32 nextTbtt, beaconintval, dtimperiod, beacontimeout;
	struct ath9k_hw_capabilities *pCap = &ah->caps;
	struct ath_common *common = ath9k_hw_common(ah);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_NEXT_TBTT_TIMER, TU_TO_USEC(bs->bs_nexttbtt));

	REG_WRITE(ah, AR_BEACON_PERIOD,
		  TU_TO_USEC(bs->bs_intval));
	REG_WRITE(ah, AR_DMA_BEACON_PERIOD,
		  TU_TO_USEC(bs->bs_intval));

	REGWRITE_BUFFER_FLUSH(ah);

	REG_RMW_FIELD(ah, AR_RSSI_THR,
		      AR_RSSI_THR_BM_THR, bs->bs_bmissthreshold);

	beaconintval = bs->bs_intval;

	if (bs->bs_sleepduration > beaconintval)
		beaconintval = bs->bs_sleepduration;

	dtimperiod = bs->bs_dtimperiod;
	if (bs->bs_sleepduration > dtimperiod)
		dtimperiod = bs->bs_sleepduration;

	if (beaconintval == dtimperiod)
		nextTbtt = bs->bs_nextdtim;
	else
		nextTbtt = bs->bs_nexttbtt;

	ath_dbg(common, BEACON, "next DTIM %d\n", bs->bs_nextdtim);
	ath_dbg(common, BEACON, "next beacon %d\n", nextTbtt);
	ath_dbg(common, BEACON, "beacon period %d\n", beaconintval);
	ath_dbg(common, BEACON, "DTIM period %d\n", dtimperiod);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_NEXT_DTIM,
		  TU_TO_USEC(bs->bs_nextdtim - SLEEP_SLOP));
	REG_WRITE(ah, AR_NEXT_TIM, TU_TO_USEC(nextTbtt - SLEEP_SLOP));

	REG_WRITE(ah, AR_SLEEP1,
		  SM((CAB_TIMEOUT_VAL << 3), AR_SLEEP1_CAB_TIMEOUT)
		  | AR_SLEEP1_ASSUME_DTIM);

	if (pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP)
		beacontimeout = (BEACON_TIMEOUT_VAL << 3);
	else
		beacontimeout = MIN_BEACON_TIMEOUT_VAL;

	REG_WRITE(ah, AR_SLEEP2,
		  SM(beacontimeout, AR_SLEEP2_BEACON_TIMEOUT));

	REG_WRITE(ah, AR_TIM_PERIOD, TU_TO_USEC(beaconintval));
	REG_WRITE(ah, AR_DTIM_PERIOD, TU_TO_USEC(dtimperiod));

	REGWRITE_BUFFER_FLUSH(ah);

	REG_SET_BIT(ah, AR_TIMER_MODE,
		    AR_TBTT_TIMER_EN | AR_TIM_TIMER_EN |
		    AR_DTIM_TIMER_EN);

	/* TSF Out of Range Threshold */
	REG_WRITE(ah, AR_TSFOOR_THRESHOLD, bs->bs_tsfoor_threshold);
}