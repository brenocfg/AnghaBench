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
struct ath5k_hw {int /*<<< orphan*/  ah_cal_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR5K_CALIBRATION_ANI ; 
 int /*<<< orphan*/  ath5k_ani_calibration (struct ath5k_hw*) ; 

__attribute__((used)) static void
ath5k_tasklet_ani(unsigned long data)
{
	struct ath5k_hw *ah = (void *)data;

	ah->ah_cal_mask |= AR5K_CALIBRATION_ANI;
	ath5k_ani_calibration(ah);
	ah->ah_cal_mask &= ~AR5K_CALIBRATION_ANI;
}