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
struct TYPE_2__ {scalar_t__ rx_intr_mitigation; scalar_t__ tx_intr_mitigation; } ;
struct ath9k_hw_capabilities {int hw_caps; } ;
struct ath_hw {int imask; int imrs2_reg; TYPE_1__ config; scalar_t__ txeol_interrupt_mask; scalar_t__ txerr_interrupt_mask; scalar_t__ txdesc_interrupt_mask; scalar_t__ txok_interrupt_mask; struct ath9k_hw_capabilities caps; } ;
struct ath_common {int dummy; } ;
typedef  enum ath9k_int { ____Placeholder_ath9k_int } ath9k_int ;

/* Variables and functions */
 int /*<<< orphan*/  AR_IMR ; 
 int AR_IMR_BCNMISC ; 
 int AR_IMR_GENTMR ; 
 int AR_IMR_RXDESC ; 
 int AR_IMR_RXERR ; 
 int AR_IMR_RXINTM ; 
 int AR_IMR_RXMINTR ; 
 int AR_IMR_RXOK ; 
 int AR_IMR_RXOK_HP ; 
 int AR_IMR_RXOK_LP ; 
 int /*<<< orphan*/  AR_IMR_S2 ; 
 int AR_IMR_S2_CABEND ; 
 int AR_IMR_S2_CABTO ; 
 int AR_IMR_S2_CST ; 
 int AR_IMR_S2_DTIM ; 
 int AR_IMR_S2_DTIMSYNC ; 
 int AR_IMR_S2_GTT ; 
 int AR_IMR_S2_TIM ; 
 int AR_IMR_S2_TSFOOR ; 
 int /*<<< orphan*/  AR_IMR_S5 ; 
 int /*<<< orphan*/  AR_IMR_S5_TIM_TIMER ; 
 int AR_IMR_TXDESC ; 
 int AR_IMR_TXEOL ; 
 int AR_IMR_TXERR ; 
 int AR_IMR_TXINTM ; 
 int AR_IMR_TXMINTR ; 
 int AR_IMR_TXOK ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int ATH9K_HW_CAP_AUTOSLEEP ; 
 int ATH9K_INT_BMISC ; 
 int ATH9K_INT_CABEND ; 
 int ATH9K_INT_COMMON ; 
 int ATH9K_INT_CST ; 
 int ATH9K_INT_DTIM ; 
 int ATH9K_INT_DTIMSYNC ; 
 int ATH9K_INT_GENTIMER ; 
 int ATH9K_INT_GLOBAL ; 
 int ATH9K_INT_GTT ; 
 int ATH9K_INT_RX ; 
 int ATH9K_INT_TIM ; 
 int ATH9K_INT_TIM_TIMER ; 
 int ATH9K_INT_TSFOOR ; 
 int ATH9K_INT_TX ; 
 int /*<<< orphan*/  INTERRUPT ; 
 int /*<<< orphan*/  REG_CLR_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_disable_interrupts (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,int) ; 

void ath9k_hw_set_interrupts(struct ath_hw *ah)
{
	enum ath9k_int ints = ah->imask;
	u32 mask, mask2;
	struct ath9k_hw_capabilities *pCap = &ah->caps;
	struct ath_common *common = ath9k_hw_common(ah);

	if (!(ints & ATH9K_INT_GLOBAL))
		ath9k_hw_disable_interrupts(ah);

	ath_dbg(common, INTERRUPT, "New interrupt mask 0x%x\n", ints);

	mask = ints & ATH9K_INT_COMMON;
	mask2 = 0;

	if (ints & ATH9K_INT_TX) {
		if (ah->config.tx_intr_mitigation)
			mask |= AR_IMR_TXMINTR | AR_IMR_TXINTM;
		else {
			if (ah->txok_interrupt_mask)
				mask |= AR_IMR_TXOK;
			if (ah->txdesc_interrupt_mask)
				mask |= AR_IMR_TXDESC;
		}
		if (ah->txerr_interrupt_mask)
			mask |= AR_IMR_TXERR;
		if (ah->txeol_interrupt_mask)
			mask |= AR_IMR_TXEOL;
	}
	if (ints & ATH9K_INT_RX) {
		if (AR_SREV_9300_20_OR_LATER(ah)) {
			mask |= AR_IMR_RXERR | AR_IMR_RXOK_HP;
			if (ah->config.rx_intr_mitigation) {
				mask &= ~AR_IMR_RXOK_LP;
				mask |=  AR_IMR_RXMINTR | AR_IMR_RXINTM;
			} else {
				mask |= AR_IMR_RXOK_LP;
			}
		} else {
			if (ah->config.rx_intr_mitigation)
				mask |= AR_IMR_RXMINTR | AR_IMR_RXINTM;
			else
				mask |= AR_IMR_RXOK | AR_IMR_RXDESC;
		}
		if (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP))
			mask |= AR_IMR_GENTMR;
	}

	if (ints & ATH9K_INT_GENTIMER)
		mask |= AR_IMR_GENTMR;

	if (ints & (ATH9K_INT_BMISC)) {
		mask |= AR_IMR_BCNMISC;
		if (ints & ATH9K_INT_TIM)
			mask2 |= AR_IMR_S2_TIM;
		if (ints & ATH9K_INT_DTIM)
			mask2 |= AR_IMR_S2_DTIM;
		if (ints & ATH9K_INT_DTIMSYNC)
			mask2 |= AR_IMR_S2_DTIMSYNC;
		if (ints & ATH9K_INT_CABEND)
			mask2 |= AR_IMR_S2_CABEND;
		if (ints & ATH9K_INT_TSFOOR)
			mask2 |= AR_IMR_S2_TSFOOR;
	}

	if (ints & (ATH9K_INT_GTT | ATH9K_INT_CST)) {
		mask |= AR_IMR_BCNMISC;
		if (ints & ATH9K_INT_GTT)
			mask2 |= AR_IMR_S2_GTT;
		if (ints & ATH9K_INT_CST)
			mask2 |= AR_IMR_S2_CST;
	}

	ath_dbg(common, INTERRUPT, "new IMR 0x%x\n", mask);
	REG_WRITE(ah, AR_IMR, mask);
	ah->imrs2_reg &= ~(AR_IMR_S2_TIM | AR_IMR_S2_DTIM | AR_IMR_S2_DTIMSYNC |
			   AR_IMR_S2_CABEND | AR_IMR_S2_CABTO |
			   AR_IMR_S2_TSFOOR | AR_IMR_S2_GTT | AR_IMR_S2_CST);
	ah->imrs2_reg |= mask2;
	REG_WRITE(ah, AR_IMR_S2, ah->imrs2_reg);

	if (!(pCap->hw_caps & ATH9K_HW_CAP_AUTOSLEEP)) {
		if (ints & ATH9K_INT_TIM_TIMER)
			REG_SET_BIT(ah, AR_IMR_S5, AR_IMR_S5_TIM_TIMER);
		else
			REG_CLR_BIT(ah, AR_IMR_S5, AR_IMR_S5_TIM_TIMER);
	}

	return;
}