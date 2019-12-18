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
struct ath_hw {int rxchainmask; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int AR9300_MAX_CHAINS ; 
 int /*<<< orphan*/  AR_SREV_9462 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9485 (struct ath_hw*) ; 
 int /*<<< orphan*/  AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  IS_CHAN_2GHZ (struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_manual_peak_cal (struct ath_hw*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar9003_hw_do_manual_peak_cal(struct ath_hw *ah,
					 struct ath9k_channel *chan)
{
	int i;

	if (!AR_SREV_9462(ah) && !AR_SREV_9565(ah) && !AR_SREV_9485(ah))
		return;

	for (i = 0; i < AR9300_MAX_CHAINS; i++) {
		if (!(ah->rxchainmask & (1 << i)))
			continue;
		ar9003_hw_manual_peak_cal(ah, i, IS_CHAN_2GHZ(chan));
	}
}