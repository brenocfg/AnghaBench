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
struct TYPE_2__ {int macVersion; } ;
struct ath_hw {TYPE_1__ hw_version; } ;

/* Variables and functions */
#define  AR_SREV_VERSION_9280 129 
#define  AR_SREV_VERSION_9580 128 

__attribute__((used)) static bool ath9k_hw_dfs_tested(struct ath_hw *ah)
{

	switch (ah->hw_version.macVersion) {
	/* for temporary testing DFS with 9280 */
	case AR_SREV_VERSION_9280:
	/* AR9580 will likely be our first target to get testing on */
	case AR_SREV_VERSION_9580:
		return true;
	default:
		return false;
	}
}