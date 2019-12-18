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
struct ath5k_hw {scalar_t__ ah_version; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
#define  AR5K_LED_ASSOC 132 
#define  AR5K_LED_AUTH 131 
#define  AR5K_LED_INIT 130 
#define  AR5K_LED_RUN 129 
#define  AR5K_LED_SCAN 128 
 int /*<<< orphan*/  AR5K_PCICFG ; 
 int AR5K_PCICFG_LED ; 
 int AR5K_PCICFG_LEDMODE ; 
 int AR5K_PCICFG_LEDMODE_PROM ; 
 int AR5K_PCICFG_LEDMODE_PROP ; 
 int AR5K_PCICFG_LED_ASSOC ; 
 int AR5K_PCICFG_LED_BCTL ; 
 int AR5K_PCICFG_LED_NONE ; 
 int AR5K_PCICFG_LED_PEND ; 
 int /*<<< orphan*/  AR5K_REG_DISABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int) ; 

void
ath5k_hw_set_ledstate(struct ath5k_hw *ah, unsigned int state)
{
	u32 led;
	/*5210 has different led mode handling*/
	u32 led_5210;

	/*Reset led status*/
	if (ah->ah_version != AR5K_AR5210)
		AR5K_REG_DISABLE_BITS(ah, AR5K_PCICFG,
			AR5K_PCICFG_LEDMODE |  AR5K_PCICFG_LED);
	else
		AR5K_REG_DISABLE_BITS(ah, AR5K_PCICFG, AR5K_PCICFG_LED);

	/*
	 * Some blinking values, define at your wish
	 */
	switch (state) {
	case AR5K_LED_SCAN:
	case AR5K_LED_AUTH:
		led = AR5K_PCICFG_LEDMODE_PROP | AR5K_PCICFG_LED_PEND;
		led_5210 = AR5K_PCICFG_LED_PEND | AR5K_PCICFG_LED_BCTL;
		break;

	case AR5K_LED_INIT:
		led = AR5K_PCICFG_LEDMODE_PROP | AR5K_PCICFG_LED_NONE;
		led_5210 = AR5K_PCICFG_LED_PEND;
		break;

	case AR5K_LED_ASSOC:
	case AR5K_LED_RUN:
		led = AR5K_PCICFG_LEDMODE_PROP | AR5K_PCICFG_LED_ASSOC;
		led_5210 = AR5K_PCICFG_LED_ASSOC;
		break;

	default:
		led = AR5K_PCICFG_LEDMODE_PROM | AR5K_PCICFG_LED_NONE;
		led_5210 = AR5K_PCICFG_LED_PEND;
		break;
	}

	/*Write new status to the register*/
	if (ah->ah_version != AR5K_AR5210)
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, led);
	else
		AR5K_REG_ENABLE_BITS(ah, AR5K_PCICFG, led_5210);
}