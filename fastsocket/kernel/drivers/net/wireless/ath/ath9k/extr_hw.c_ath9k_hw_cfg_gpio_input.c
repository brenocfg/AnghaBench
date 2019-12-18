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
struct TYPE_2__ {int num_gpio_pins; } ;
struct ath_hw {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7010_GPIO_OE ; 
 int AR7010_GPIO_OE_AS_INPUT ; 
 int AR7010_GPIO_OE_MASK ; 
 scalar_t__ AR_DEVID_7010 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_GPIO_OE_OUT ; 
 int AR_GPIO_OE_OUT_DRV ; 
 int AR_GPIO_OE_OUT_DRV_NO ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int) ; 

void ath9k_hw_cfg_gpio_input(struct ath_hw *ah, u32 gpio)
{
	u32 gpio_shift;

	BUG_ON(gpio >= ah->caps.num_gpio_pins);

	if (AR_DEVID_7010(ah)) {
		gpio_shift = gpio;
		REG_RMW(ah, AR7010_GPIO_OE,
			(AR7010_GPIO_OE_AS_INPUT << gpio_shift),
			(AR7010_GPIO_OE_MASK << gpio_shift));
		return;
	}

	gpio_shift = gpio << 1;
	REG_RMW(ah,
		AR_GPIO_OE_OUT,
		(AR_GPIO_OE_OUT_DRV_NO << gpio_shift),
		(AR_GPIO_OE_OUT_DRV << gpio_shift));
}