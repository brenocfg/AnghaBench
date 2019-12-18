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
struct ath_hw {int /*<<< orphan*/  misc_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PCU_TX_ADD_TSF ; 

void ath9k_hw_set_tsfadjust(struct ath_hw *ah, bool set)
{
	if (set)
		ah->misc_mode |= AR_PCU_TX_ADD_TSF;
	else
		ah->misc_mode &= ~AR_PCU_TX_ADD_TSF;
}