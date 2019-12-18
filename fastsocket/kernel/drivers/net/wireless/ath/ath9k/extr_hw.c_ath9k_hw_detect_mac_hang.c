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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_DMADBG_4 ; 
 scalar_t__ AR_DMADBG_5 ; 
 scalar_t__ AR_DMADBG_6 ; 
 scalar_t__ DCU_COMPLETE_STATE ; 
 scalar_t__ DCU_COMPLETE_STATE_MASK ; 
 scalar_t__ NUM_STATUS_READS ; 
 scalar_t__ REG_READ (struct ath_hw*,scalar_t__) ; 
 int /*<<< orphan*/  RESET ; 
 scalar_t__ ath9k_hw_check_dcs (scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static bool ath9k_hw_detect_mac_hang(struct ath_hw *ah)
{
	u32 chain_state, comp_state, dcs_reg = AR_DMADBG_4;
	u32 i, hang_pos, hang_state, num_state = 6;

	comp_state = REG_READ(ah, AR_DMADBG_6);

	if ((comp_state & DCU_COMPLETE_STATE_MASK) != DCU_COMPLETE_STATE) {
		ath_dbg(ath9k_hw_common(ah), RESET,
			"MAC Hang signature not found at DCU complete\n");
		return false;
	}

	chain_state = REG_READ(ah, dcs_reg);
	if (ath9k_hw_check_dcs(chain_state, num_state, &hang_state, &hang_pos))
		goto hang_check_iter;

	dcs_reg = AR_DMADBG_5;
	num_state = 4;
	chain_state = REG_READ(ah, dcs_reg);
	if (ath9k_hw_check_dcs(chain_state, num_state, &hang_state, &hang_pos))
		goto hang_check_iter;

	ath_dbg(ath9k_hw_common(ah), RESET,
		"MAC Hang signature 1 not found\n");
	return false;

hang_check_iter:
	ath_dbg(ath9k_hw_common(ah), RESET,
		"DCU registers: chain %08x complete %08x Hang: state %d pos %d\n",
		chain_state, comp_state, hang_state, hang_pos);

	for (i = 0; i < NUM_STATUS_READS; i++) {
		chain_state = REG_READ(ah, dcs_reg);
		chain_state = (chain_state >> (5 * hang_pos)) & 0x1f;
		comp_state = REG_READ(ah, AR_DMADBG_6);

		if (((comp_state & DCU_COMPLETE_STATE_MASK) !=
					DCU_COMPLETE_STATE) ||
		    (chain_state != hang_state))
			return false;
	}

	ath_dbg(ath9k_hw_common(ah), RESET, "MAC Hang signature 1 found\n");

	return true;
}