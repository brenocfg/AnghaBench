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
 int /*<<< orphan*/  AR_OBS_BUS_1 ; 
 scalar_t__ AR_SREV_9285_12_OR_LATER (struct ath_hw*) ; 
 scalar_t__ AR_SREV_9300 (struct ath_hw*) ; 
 int REG_READ (struct ath_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath9k_hw_detect_mac_hang (struct ath_hw*) ; 

bool ath9k_hw_check_alive(struct ath_hw *ah)
{
	int count = 50;
	u32 reg;

	if (AR_SREV_9300(ah))
		return !ath9k_hw_detect_mac_hang(ah);

	if (AR_SREV_9285_12_OR_LATER(ah))
		return true;

	do {
		reg = REG_READ(ah, AR_OBS_BUS_1);

		if ((reg & 0x7E7FFFEF) == 0x00702400)
			continue;

		switch (reg & 0x7E000B00) {
		case 0x1E000000:
		case 0x52000B00:
		case 0x18000B00:
			continue;
		default:
			return true;
		}
	} while (count-- > 0);

	return false;
}