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
typedef  scalar_t__ u16 ;
struct ath_regulatory {scalar_t__ power_limit; scalar_t__ max_power_level; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */
 struct ath_regulatory* ath9k_hw_regulatory (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_set_txpowerlimit (struct ath_hw*,scalar_t__,int) ; 

void ath9k_cmn_update_txpow(struct ath_hw *ah, u16 cur_txpow,
			    u16 new_txpow, u16 *txpower)
{
	struct ath_regulatory *reg = ath9k_hw_regulatory(ah);

	if (reg->power_limit != new_txpow) {
		ath9k_hw_set_txpowerlimit(ah, new_txpow, false);
		/* read back in case value is clamped */
		*txpower = reg->max_power_level;
	}
}