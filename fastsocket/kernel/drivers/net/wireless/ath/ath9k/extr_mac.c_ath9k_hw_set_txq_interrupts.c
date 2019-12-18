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
struct ath_hw {int txurn_interrupt_mask; int imrs2_reg; int /*<<< orphan*/  txeol_interrupt_mask; int /*<<< orphan*/  txerr_interrupt_mask; int /*<<< orphan*/  txdesc_interrupt_mask; int /*<<< orphan*/  txok_interrupt_mask; } ;
struct ath9k_tx_queue_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_IMR_S0 ; 
 int /*<<< orphan*/  AR_IMR_S0_QCU_TXDESC ; 
 int /*<<< orphan*/  AR_IMR_S0_QCU_TXOK ; 
 int /*<<< orphan*/  AR_IMR_S1 ; 
 int /*<<< orphan*/  AR_IMR_S1_QCU_TXEOL ; 
 int /*<<< orphan*/  AR_IMR_S1_QCU_TXERR ; 
 int /*<<< orphan*/  AR_IMR_S2 ; 
 int AR_IMR_S2_QCU_TXURN ; 
 int /*<<< orphan*/  ENABLE_REGWRITE_BUFFER (struct ath_hw*) ; 
 int /*<<< orphan*/  INTERRUPT ; 
 int /*<<< orphan*/  REGWRITE_BUFFER_FLUSH (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath9k_hw_set_txq_interrupts(struct ath_hw *ah,
					struct ath9k_tx_queue_info *qi)
{
	ath_dbg(ath9k_hw_common(ah), INTERRUPT,
		"tx ok 0x%x err 0x%x desc 0x%x eol 0x%x urn 0x%x\n",
		ah->txok_interrupt_mask, ah->txerr_interrupt_mask,
		ah->txdesc_interrupt_mask, ah->txeol_interrupt_mask,
		ah->txurn_interrupt_mask);

	ENABLE_REGWRITE_BUFFER(ah);

	REG_WRITE(ah, AR_IMR_S0,
		  SM(ah->txok_interrupt_mask, AR_IMR_S0_QCU_TXOK)
		  | SM(ah->txdesc_interrupt_mask, AR_IMR_S0_QCU_TXDESC));
	REG_WRITE(ah, AR_IMR_S1,
		  SM(ah->txerr_interrupt_mask, AR_IMR_S1_QCU_TXERR)
		  | SM(ah->txeol_interrupt_mask, AR_IMR_S1_QCU_TXEOL));

	ah->imrs2_reg &= ~AR_IMR_S2_QCU_TXURN;
	ah->imrs2_reg |= (ah->txurn_interrupt_mask & AR_IMR_S2_QCU_TXURN);
	REG_WRITE(ah, AR_IMR_S2, ah->imrs2_reg);

	REGWRITE_BUFFER_FLUSH(ah);
}