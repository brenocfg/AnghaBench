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
struct ath_hw {int imrs2_reg; TYPE_1__ config; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  AR_IMR ; 
 int AR_IMR_BCNMISC ; 
 int AR_IMR_RXERR ; 
 int AR_IMR_RXINTM ; 
 int AR_IMR_RXMINTR ; 
 int AR_IMR_RXOK ; 
 int AR_IMR_RXOK_HP ; 
 int AR_IMR_RXOK_LP ; 
 int AR_IMR_RXORN ; 
 int /*<<< orphan*/  AR_IMR_S2 ; 
 int AR_IMR_S2_GTT ; 
 int AR_IMR_TXERR ; 
 int AR_IMR_TXINTM ; 
 int AR_IMR_TXMINTR ; 
 int AR_IMR_TXOK ; 
 int AR_IMR_TXURN ; 
 int /*<<< orphan*/  AR_INTR_PRIO_ASYNC_ENABLE ; 
 int /*<<< orphan*/  AR_INTR_PRIO_ASYNC_MASK ; 
 int /*<<< orphan*/  AR_INTR_PRIO_SYNC_ENABLE ; 
 int /*<<< orphan*/  AR_INTR_PRIO_SYNC_MASK ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE ; 
 int AR_INTR_SYNC_DEFAULT ; 
 int /*<<< orphan*/  AR_INTR_SYNC_ENABLE ; 
 int AR_INTR_SYNC_HOST1_FATAL ; 
 int /*<<< orphan*/  AR_INTR_SYNC_MASK ; 
 int /*<<< orphan*/  AR_SREV_9100 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9340 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9550 (struct ath_hw*) ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath9k_hw_init_interrupt_masks(struct ath_hw *ah,
					  enum nl80211_iftype opmode)
{
	u32 sync_default = AR_INTR_SYNC_DEFAULT;
	u32 imr_reg = AR_IMR_TXERR |
		AR_IMR_TXURN |
		AR_IMR_RXERR |
		AR_IMR_RXORN |
		AR_IMR_BCNMISC;

	if (AR_SREV_9340(ah) || AR_SREV_9550(ah))
		sync_default &= ~AR_INTR_SYNC_HOST1_FATAL;

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		imr_reg |= AR_IMR_RXOK_HP;
		if (ah->config.rx_intr_mitigation)
			imr_reg |= AR_IMR_RXINTM | AR_IMR_RXMINTR;
		else
			imr_reg |= AR_IMR_RXOK_LP;

	} else {
		if (ah->config.rx_intr_mitigation)
			imr_reg |= AR_IMR_RXINTM | AR_IMR_RXMINTR;
		else
			imr_reg |= AR_IMR_RXOK;
	}

	if (ah->config.tx_intr_mitigation)
		imr_reg |= AR_IMR_TXINTM | AR_IMR_TXMINTR;
	else
		imr_reg |= AR_IMR_TXOK;

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_IMR, imr_reg);
	ah->imrs2_reg |= AR_IMR_S2_GTT;
	REG_WRITE(ah, AR_IMR_S2, ah->imrs2_reg);

	if (!AR_SREV_9100(ah)) {
		REG_WRITE(ah, AR_INTR_SYNC_CAUSE, 0xFFFFFFFF);
		REG_WRITE(ah, AR_INTR_SYNC_ENABLE, sync_default);
		REG_WRITE(ah, AR_INTR_SYNC_MASK, 0);
	}

	REGWRITE_BUFFER_FLUSH(ah);

	if (AR_SREV_9300_20_OR_LATER(ah)) {
		REG_WRITE(ah, AR_INTR_PRIO_ASYNC_ENABLE, 0);
		REG_WRITE(ah, AR_INTR_PRIO_ASYNC_MASK, 0);
		REG_WRITE(ah, AR_INTR_PRIO_SYNC_ENABLE, 0);
		REG_WRITE(ah, AR_INTR_PRIO_SYNC_MASK, 0);
	}
}