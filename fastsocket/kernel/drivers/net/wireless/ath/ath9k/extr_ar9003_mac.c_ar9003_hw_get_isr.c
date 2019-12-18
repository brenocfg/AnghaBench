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
struct TYPE_2__ {scalar_t__ tx_intr_mitigation; scalar_t__ rx_intr_mitigation; } ;
struct ath9k_hw_capabilities {int hw_caps; } ;
struct ath_hw {void* intr_gen_timer_trigger; void* intr_gen_timer_thresh; TYPE_1__ config; struct ath9k_hw_capabilities caps; } ;
struct ath_common {int dummy; } ;
typedef  enum ath9k_int { ____Placeholder_ath9k_int } ath9k_int ;

/* Variables and functions */
 int /*<<< orphan*/  ANY ; 
 int /*<<< orphan*/  AR_INTR_ASYNC_CAUSE ; 
 int AR_INTR_ASYNC_MASK_MCI ; 
 int AR_INTR_MAC_IRQ ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE_CLR ; 
 int AR_INTR_SYNC_DEFAULT ; 
 int AR_INTR_SYNC_HOST1_FATAL ; 
 int AR_INTR_SYNC_HOST1_PERR ; 
 int AR_INTR_SYNC_LOCAL_TIMEOUT ; 
 int AR_INTR_SYNC_RADM_CPL_TIMEOUT ; 
 int /*<<< orphan*/  AR_ISR ; 
 int AR_ISR_BCNMISC ; 
 int AR_ISR_GENTMR ; 
 int AR_ISR_HP_RXOK ; 
 int AR_ISR_LP_RXOK ; 
 int /*<<< orphan*/  AR_ISR_RAC ; 
 int AR_ISR_RXERR ; 
 int AR_ISR_RXINTM ; 
 int AR_ISR_RXMINTR ; 
 int /*<<< orphan*/  AR_ISR_S0 ; 
 int /*<<< orphan*/  AR_ISR_S1 ; 
 int /*<<< orphan*/  AR_ISR_S2 ; 
 int AR_ISR_S2_BB_WATCHDOG ; 
 int AR_ISR_S2_CABEND ; 
 int AR_ISR_S2_CST ; 
 int AR_ISR_S2_DTIM ; 
 int AR_ISR_S2_DTIMSYNC ; 
 int AR_ISR_S2_GTT ; 
 int AR_ISR_S2_TIM ; 
 int AR_ISR_S2_TSFOOR ; 
 int /*<<< orphan*/  AR_ISR_S5 ; 
 int /*<<< orphan*/  AR_ISR_S5_GENTIMER_THRESH ; 
 int /*<<< orphan*/  AR_ISR_S5_GENTIMER_TRIG ; 
 int /*<<< orphan*/  AR_ISR_S5_S ; 
 int AR_ISR_TXEOL ; 
 int AR_ISR_TXERR ; 
 int AR_ISR_TXINTM ; 
 int AR_ISR_TXMINTR ; 
 int AR_ISR_TXOK ; 
 int /*<<< orphan*/  AR_RC ; 
 int AR_RC_HOSTIF ; 
 int /*<<< orphan*/  AR_RTC_STATUS ; 
 int AR_RTC_STATUS_M ; 
 int AR_RTC_STATUS_ON ; 
 int ATH9K_HW_CAP_RAC_SUPPORTED ; 
 int ATH9K_INT_BB_WATCHDOG ; 
 int ATH9K_INT_COMMON ; 
 int ATH9K_INT_FATAL ; 
 int ATH9K_INT_GENTIMER ; 
 int ATH9K_INT_RXHP ; 
 int ATH9K_INT_RXLP ; 
 int ATH9K_INT_TX ; 
 int /*<<< orphan*/  INTERRUPT ; 
 int MAP_ISR_S2_BB_WATCHDOG ; 
 int MAP_ISR_S2_CABEND ; 
 int MAP_ISR_S2_CST ; 
 int MAP_ISR_S2_DTIM ; 
 int MAP_ISR_S2_DTIMSYNC ; 
 int MAP_ISR_S2_GTT ; 
 int MAP_ISR_S2_TIM ; 
 int MAP_ISR_S2_TSFOOR ; 
 void* MS (int,int /*<<< orphan*/ ) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9003_hw_bb_watchdog_read (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_mci_get_isr (struct ath_hw*,int*) ; 
 int /*<<< orphan*/  ath9k_debug_sync_cause (struct ath_common*,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 scalar_t__ ath9k_hw_mci_is_enabled (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool ar9003_hw_get_isr(struct ath_hw *ah, enum ath9k_int *masked)
{
	u32 isr = 0;
	u32 mask2 = 0;
	struct ath9k_hw_capabilities *pCap = &ah->caps;
	struct ath_common *common = ath9k_hw_common(ah);
	u32 sync_cause = 0, async_cause, async_mask = AR_INTR_MAC_IRQ;
	bool fatal_int;

	if (ath9k_hw_mci_is_enabled(ah))
		async_mask |= AR_INTR_ASYNC_MASK_MCI;

	async_cause = REG_READ(ah, AR_INTR_ASYNC_CAUSE);

	if (async_cause & async_mask) {
		if ((REG_READ(ah, AR_RTC_STATUS) & AR_RTC_STATUS_M)
				== AR_RTC_STATUS_ON)
			isr = REG_READ(ah, AR_ISR);
	}


	sync_cause = REG_READ(ah, AR_INTR_SYNC_CAUSE) & AR_INTR_SYNC_DEFAULT;

	*masked = 0;

	if (!isr && !sync_cause && !async_cause)
		return false;

	if (isr) {
		if (isr & AR_ISR_BCNMISC) {
			u32 isr2;
			isr2 = REG_READ(ah, AR_ISR_S2);

			mask2 |= ((isr2 & AR_ISR_S2_TIM) >>
				  MAP_ISR_S2_TIM);
			mask2 |= ((isr2 & AR_ISR_S2_DTIM) >>
				  MAP_ISR_S2_DTIM);
			mask2 |= ((isr2 & AR_ISR_S2_DTIMSYNC) >>
				  MAP_ISR_S2_DTIMSYNC);
			mask2 |= ((isr2 & AR_ISR_S2_CABEND) >>
				  MAP_ISR_S2_CABEND);
			mask2 |= ((isr2 & AR_ISR_S2_GTT) <<
				  MAP_ISR_S2_GTT);
			mask2 |= ((isr2 & AR_ISR_S2_CST) <<
				  MAP_ISR_S2_CST);
			mask2 |= ((isr2 & AR_ISR_S2_TSFOOR) >>
				  MAP_ISR_S2_TSFOOR);
			mask2 |= ((isr2 & AR_ISR_S2_BB_WATCHDOG) >>
				  MAP_ISR_S2_BB_WATCHDOG);

			if (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) {
				REG_WRITE(ah, AR_ISR_S2, isr2);
				isr &= ~AR_ISR_BCNMISC;
			}
		}

		if ((pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED))
			isr = REG_READ(ah, AR_ISR_RAC);

		if (isr == 0xffffffff) {
			*masked = 0;
			return false;
		}

		*masked = isr & ATH9K_INT_COMMON;

		if (ah->config.rx_intr_mitigation)
			if (isr & (AR_ISR_RXMINTR | AR_ISR_RXINTM))
				*masked |= ATH9K_INT_RXLP;

		if (ah->config.tx_intr_mitigation)
			if (isr & (AR_ISR_TXMINTR | AR_ISR_TXINTM))
				*masked |= ATH9K_INT_TX;

		if (isr & (AR_ISR_LP_RXOK | AR_ISR_RXERR))
			*masked |= ATH9K_INT_RXLP;

		if (isr & AR_ISR_HP_RXOK)
			*masked |= ATH9K_INT_RXHP;

		if (isr & (AR_ISR_TXOK | AR_ISR_TXERR | AR_ISR_TXEOL)) {
			*masked |= ATH9K_INT_TX;

			if (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) {
				u32 s0, s1;
				s0 = REG_READ(ah, AR_ISR_S0);
				REG_WRITE(ah, AR_ISR_S0, s0);
				s1 = REG_READ(ah, AR_ISR_S1);
				REG_WRITE(ah, AR_ISR_S1, s1);

				isr &= ~(AR_ISR_TXOK | AR_ISR_TXERR |
					 AR_ISR_TXEOL);
			}
		}

		if (isr & AR_ISR_GENTMR) {
			u32 s5;

			if (pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)
				s5 = REG_READ(ah, AR_ISR_S5_S);
			else
				s5 = REG_READ(ah, AR_ISR_S5);

			ah->intr_gen_timer_trigger =
				MS(s5, AR_ISR_S5_GENTIMER_TRIG);

			ah->intr_gen_timer_thresh =
				MS(s5, AR_ISR_S5_GENTIMER_THRESH);

			if (ah->intr_gen_timer_trigger)
				*masked |= ATH9K_INT_GENTIMER;

			if (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) {
				REG_WRITE(ah, AR_ISR_S5, s5);
				isr &= ~AR_ISR_GENTMR;
			}

		}

		*masked |= mask2;

		if (!(pCap->hw_caps & ATH9K_HW_CAP_RAC_SUPPORTED)) {
			REG_WRITE(ah, AR_ISR, isr);

			(void) REG_READ(ah, AR_ISR);
		}

		if (*masked & ATH9K_INT_BB_WATCHDOG)
			ar9003_hw_bb_watchdog_read(ah);
	}

	if (async_cause & AR_INTR_ASYNC_MASK_MCI)
		ar9003_mci_get_isr(ah, masked);

	if (sync_cause) {
		ath9k_debug_sync_cause(common, sync_cause);
		fatal_int =
			(sync_cause &
			 (AR_INTR_SYNC_HOST1_FATAL | AR_INTR_SYNC_HOST1_PERR))
			? true : false;

		if (fatal_int) {
			if (sync_cause & AR_INTR_SYNC_HOST1_FATAL) {
				ath_dbg(common, ANY,
					"received PCI FATAL interrupt\n");
			}
			if (sync_cause & AR_INTR_SYNC_HOST1_PERR) {
				ath_dbg(common, ANY,
					"received PCI PERR interrupt\n");
			}
			*masked |= ATH9K_INT_FATAL;
		}

		if (sync_cause & AR_INTR_SYNC_RADM_CPL_TIMEOUT) {
			REG_WRITE(ah, AR_RC, AR_RC_HOSTIF);
			REG_WRITE(ah, AR_RC, 0);
			*masked |= ATH9K_INT_FATAL;
		}

		if (sync_cause & AR_INTR_SYNC_LOCAL_TIMEOUT)
			ath_dbg(common, INTERRUPT,
				"AR_INTR_SYNC_LOCAL_TIMEOUT\n");

		REG_WRITE(ah, AR_INTR_SYNC_CAUSE_CLR, sync_cause);
		(void) REG_READ(ah, AR_INTR_SYNC_CAUSE_CLR);

	}
	return true;
}