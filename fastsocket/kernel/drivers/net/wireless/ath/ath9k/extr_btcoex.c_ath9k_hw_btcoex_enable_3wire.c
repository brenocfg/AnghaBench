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
typedef  int u32 ;
struct ath_btcoex_hw {int bt_coex_mode; int bt_coex_mode2; int* wlan_weight; int* bt_weight; int bt_coex_weights; int /*<<< orphan*/  wlanactive_gpio; } ;
struct ath_hw {struct ath_btcoex_hw btcoex_hw; } ;

/* Variables and functions */
 int AR9300_NUM_BT_WEIGHTS ; 
 int AR_BT_COEX_BT_WEIGHTS (int) ; 
 int AR_BT_COEX_MODE ; 
 int AR_BT_COEX_MODE2 ; 
 int AR_BT_COEX_WEIGHT ; 
 int AR_BT_COEX_WL_WEIGHTS0 ; 
 int AR_BT_COEX_WL_WEIGHTS1 ; 
 int /*<<< orphan*/  AR_GPIO_OUTPUT_MUX_AS_RX_CLEAR_EXTERNAL ; 
 int /*<<< orphan*/  AR_PCU_BT_ANT_PREVENT_RX ; 
 int /*<<< orphan*/  AR_PCU_MISC ; 
 int /*<<< orphan*/  AR_QUIET1 ; 
 int /*<<< orphan*/  AR_QUIET1_QUIET_ACK_CTS_ENABLE ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300_20_OR_LATER (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int) ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int,int) ; 
 int /*<<< orphan*/  ath9k_hw_cfg_output (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hw_btcoex_enable_3wire(struct ath_hw *ah)
{
	struct ath_btcoex_hw *btcoex = &ah->btcoex_hw;
	u32  val;
	int i;

	/*
	 * Program coex mode and weight registers to
	 * enable coex 3-wire
	 */
	REG_WRITE(ah, AR_BT_COEX_MODE, btcoex->bt_coex_mode);
	REG_WRITE(ah, AR_BT_COEX_MODE2, btcoex->bt_coex_mode2);


	if (AR_SREV_9300_20_OR_LATER(ah)) {
		REG_WRITE(ah, AR_BT_COEX_WL_WEIGHTS0, btcoex->wlan_weight[0]);
		REG_WRITE(ah, AR_BT_COEX_WL_WEIGHTS1, btcoex->wlan_weight[1]);
		for (i = 0; i < AR9300_NUM_BT_WEIGHTS; i++)
			REG_WRITE(ah, AR_BT_COEX_BT_WEIGHTS(i),
				  btcoex->bt_weight[i]);
	} else
		REG_WRITE(ah, AR_BT_COEX_WEIGHT, btcoex->bt_coex_weights);



	if (AR_SREV_9271(ah)) {
		val = REG_READ(ah, 0x50040);
		val &= 0xFFFFFEFF;
		REG_WRITE(ah, 0x50040, val);
	}

	REG_RMW_FIELD(ah, AR_QUIET1, AR_QUIET1_QUIET_ACK_CTS_ENABLE, 1);
	REG_RMW_FIELD(ah, AR_PCU_MISC, AR_PCU_BT_ANT_PREVENT_RX, 0);

	ath9k_hw_cfg_output(ah, btcoex->wlanactive_gpio,
			    AR_GPIO_OUTPUT_MUX_AS_RX_CLEAR_EXTERNAL);
}