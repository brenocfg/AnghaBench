#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int g_low; int g_high; void* g_state; int /*<<< orphan*/  g_step_idx; } ;
struct ath5k_hw {int ah_radio; TYPE_1__ ah_gain; } ;
struct TYPE_6__ {int /*<<< orphan*/  go_default; } ;
struct TYPE_5__ {int /*<<< orphan*/  go_default; } ;

/* Variables and functions */
#define  AR5K_RF5111 129 
#define  AR5K_RF5112 128 
 void* AR5K_RFGAIN_ACTIVE ; 
 int EINVAL ; 
 TYPE_3__ rfgain_opt_5111 ; 
 TYPE_2__ rfgain_opt_5112 ; 

int ath5k_hw_rfgain_opt_init(struct ath5k_hw *ah)
{
	/* Initialize the gain optimization values */
	switch (ah->ah_radio) {
	case AR5K_RF5111:
		ah->ah_gain.g_step_idx = rfgain_opt_5111.go_default;
		ah->ah_gain.g_low = 20;
		ah->ah_gain.g_high = 35;
		ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		break;
	case AR5K_RF5112:
		ah->ah_gain.g_step_idx = rfgain_opt_5112.go_default;
		ah->ah_gain.g_low = 20;
		ah->ah_gain.g_high = 85;
		ah->ah_gain.g_state = AR5K_RFGAIN_ACTIVE;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}