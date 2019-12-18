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
struct ath_btcoex_hw {int /*<<< orphan*/  btpriority_gpio; int /*<<< orphan*/  btactive_gpio; } ;
struct ath_hw {struct ath_btcoex_hw btcoex_hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_GPIO_INPUT_EN_VAL ; 
 int AR_GPIO_INPUT_EN_VAL_BT_ACTIVE_BB ; 
 int AR_GPIO_INPUT_EN_VAL_BT_PRIORITY_BB ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_MUX1 ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_MUX1_BT_ACTIVE ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_MUX1_BT_PRIORITY ; 
 int /*<<< orphan*/  REG_RMW_FIELD (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (struct ath_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath9k_hw_cfg_gpio_input (struct ath_hw*,int /*<<< orphan*/ ) ; 

void ath9k_hw_btcoex_init_3wire(struct ath_hw *ah)
{
	struct ath_btcoex_hw *btcoex_hw = &ah->btcoex_hw;

	/* btcoex 3-wire */
	REG_SET_BIT(ah, AR_GPIO_INPUT_EN_VAL,
			(AR_GPIO_INPUT_EN_VAL_BT_PRIORITY_BB |
			 AR_GPIO_INPUT_EN_VAL_BT_ACTIVE_BB));

	/* Set input mux for bt_prority_async and
	 *                  bt_active_async to GPIO pins */
	REG_RMW_FIELD(ah, AR_GPIO_INPUT_MUX1,
			AR_GPIO_INPUT_MUX1_BT_ACTIVE,
			btcoex_hw->btactive_gpio);

	REG_RMW_FIELD(ah, AR_GPIO_INPUT_MUX1,
			AR_GPIO_INPUT_MUX1_BT_PRIORITY,
			btcoex_hw->btpriority_gpio);

	/* Configure the desired GPIO ports for input */

	ath9k_hw_cfg_gpio_input(ah, btcoex_hw->btactive_gpio);
	ath9k_hw_cfg_gpio_input(ah, btcoex_hw->btpriority_gpio);
}