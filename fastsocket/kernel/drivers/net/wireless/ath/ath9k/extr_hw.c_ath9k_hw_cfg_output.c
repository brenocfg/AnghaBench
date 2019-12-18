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
struct ath_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7010_GPIO_OE ; 
 int AR7010_GPIO_OE_AS_OUTPUT ; 
 int AR7010_GPIO_OE_MASK ; 
 scalar_t__ AR_DEVID_7010 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_GPIO_OE_OUT ; 
 int AR_GPIO_OE_OUT_DRV ; 
 int AR_GPIO_OE_OUT_DRV_ALL ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ath9k_hw_gpio_cfg_output_mux (struct ath_hw*,int,int) ; 

void ath9k_hw_cfg_output(struct ath_hw *ah, u32 gpio,
			 u32 ah_signal_type)
{
	u32 gpio_shift;

	if (AR_DEVID_7010(ah)) {
		gpio_shift = gpio;
		REG_RMW(ah, AR7010_GPIO_OE,
			(AR7010_GPIO_OE_AS_OUTPUT << gpio_shift),
			(AR7010_GPIO_OE_MASK << gpio_shift));
		return;
	}

	ath9k_hw_gpio_cfg_output_mux(ah, gpio, ah_signal_type);
	gpio_shift = 2 * gpio;
	REG_RMW(ah,
		AR_GPIO_OE_OUT,
		(AR_GPIO_OE_OUT_DRV_ALL << gpio_shift),
		(AR_GPIO_OE_OUT_DRV << gpio_shift));
}