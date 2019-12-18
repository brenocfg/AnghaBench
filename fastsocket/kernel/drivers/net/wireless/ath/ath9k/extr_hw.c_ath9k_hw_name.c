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
struct TYPE_2__ {int macRev; int analog5GhzRev; int phyRev; int /*<<< orphan*/  macVersion; } ;
struct ath_hw {TYPE_1__ hw_version; } ;

/* Variables and functions */
 int AR_RADIO_SREV_MAJOR ; 
 scalar_t__ AR_SREV_9280_20_OR_LATER (struct ath_hw*) ; 
 char* ath9k_hw_mac_bb_name (int /*<<< orphan*/ ) ; 
 char* ath9k_hw_rf_name (int) ; 
 int snprintf (char*,size_t,char*,char*,int,...) ; 

void ath9k_hw_name(struct ath_hw *ah, char *hw_name, size_t len)
{
	int used;

	/* chipsets >= AR9280 are single-chip */
	if (AR_SREV_9280_20_OR_LATER(ah)) {
		used = snprintf(hw_name, len,
			       "Atheros AR%s Rev:%x",
			       ath9k_hw_mac_bb_name(ah->hw_version.macVersion),
			       ah->hw_version.macRev);
	}
	else {
		used = snprintf(hw_name, len,
			       "Atheros AR%s MAC/BB Rev:%x AR%s RF Rev:%x",
			       ath9k_hw_mac_bb_name(ah->hw_version.macVersion),
			       ah->hw_version.macRev,
			       ath9k_hw_rf_name((ah->hw_version.analog5GhzRev &
						AR_RADIO_SREV_MAJOR)),
			       ah->hw_version.phyRev);
	}

	hw_name[used] = '\0';
}