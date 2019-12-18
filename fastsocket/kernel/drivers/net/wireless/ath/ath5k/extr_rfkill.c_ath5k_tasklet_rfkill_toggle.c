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
struct ath5k_hw {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int ath5k_is_rfkill_set (struct ath5k_hw*) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ath5k_tasklet_rfkill_toggle(unsigned long data)
{
	struct ath5k_hw *ah = (void *)data;
	bool blocked;

	blocked = ath5k_is_rfkill_set(ah);
	wiphy_rfkill_set_hw_state(ah->hw->wiphy, blocked);
}