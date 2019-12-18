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
 int /*<<< orphan*/  AR7010_GPIO_OUT ; 
 scalar_t__ AR_DEVID_7010 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_GPIO_BIT (int) ; 
 int /*<<< orphan*/  AR_GPIO_IN_OUT ; 
 scalar_t__ AR_SREV_9271 (struct ath_hw*) ; 
 int /*<<< orphan*/  REG_RMW (struct ath_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void ath9k_hw_set_gpio(struct ath_hw *ah, u32 gpio, u32 val)
{
	if (AR_DEVID_7010(ah)) {
		val = val ? 0 : 1;
		REG_RMW(ah, AR7010_GPIO_OUT, ((val&1) << gpio),
			AR_GPIO_BIT(gpio));
		return;
	}

	if (AR_SREV_9271(ah))
		val = ~val;

	REG_RMW(ah, AR_GPIO_IN_OUT, ((val & 1) << gpio),
		AR_GPIO_BIT(gpio));
}