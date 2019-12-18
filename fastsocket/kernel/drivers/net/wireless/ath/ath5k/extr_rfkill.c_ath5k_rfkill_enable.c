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
struct TYPE_2__ {int /*<<< orphan*/  polarity; int /*<<< orphan*/  gpio; } ;
struct ath5k_hw {TYPE_1__ rf_kill; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_ANY ; 
 int /*<<< orphan*/  ath5k_hw_set_gpio (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath5k_hw_set_gpio_output (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ath5k_rfkill_enable(struct ath5k_hw *ah)
{
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "rfkill enable (gpio:%d polarity:%d)\n",
		ah->rf_kill.gpio, ah->rf_kill.polarity);
	ath5k_hw_set_gpio_output(ah, ah->rf_kill.gpio);
	ath5k_hw_set_gpio(ah, ah->rf_kill.gpio, ah->rf_kill.polarity);
}