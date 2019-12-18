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
struct ath_hw {int /*<<< orphan*/  iniModesRxGain; } ;

/* Variables and functions */
 scalar_t__ AR_SREV_9462_20 (struct ath_hw*) ; 
 int /*<<< orphan*/  INIT_INI_ARRAY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9462_common_mixed_rx_gain_table_2p0 ; 

__attribute__((used)) static void ar9003_rx_gain_table_mode2(struct ath_hw *ah)
{
	if (AR_SREV_9462_20(ah))
		INIT_INI_ARRAY(&ah->iniModesRxGain,
			       ar9462_common_mixed_rx_gain_table_2p0);
}