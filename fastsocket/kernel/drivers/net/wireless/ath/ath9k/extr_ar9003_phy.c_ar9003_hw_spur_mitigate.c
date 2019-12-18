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
struct ath_hw {int dummy; } ;
struct ath9k_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_SREV_9565 (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_spur_mitigate_mrc_cck (struct ath_hw*,struct ath9k_channel*) ; 
 int /*<<< orphan*/  ar9003_hw_spur_mitigate_ofdm (struct ath_hw*,struct ath9k_channel*) ; 

__attribute__((used)) static void ar9003_hw_spur_mitigate(struct ath_hw *ah,
				    struct ath9k_channel *chan)
{
	if (!AR_SREV_9565(ah))
		ar9003_hw_spur_mitigate_mrc_cck(ah, chan);
	ar9003_hw_spur_mitigate_ofdm(ah, chan);
}