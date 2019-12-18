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
struct ath_hw {int /*<<< orphan*/  ah_mibStats; } ;
struct ath_common {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANI ; 
 int /*<<< orphan*/  AR_FILT_CCK ; 
 int /*<<< orphan*/  AR_FILT_OFDM ; 
 int /*<<< orphan*/  AR_MIBC ; 
 int /*<<< orphan*/  AR_MIBC_CMC ; 
 int /*<<< orphan*/  AR_MIBC_FMC ; 
 int /*<<< orphan*/  REG_WRITE (struct ath_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_common* ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_update_mibstats (struct ath_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

void ath9k_hw_disable_mib_counters(struct ath_hw *ah)
{
	struct ath_common *common = ath9k_hw_common(ah);

	ath_dbg(common, ANI, "Disable MIB counters\n");

	REG_WRITE(ah, AR_MIBC, AR_MIBC_FMC);
	ath9k_hw_update_mibstats(ah, &ah->ah_mibStats);
	REG_WRITE(ah, AR_MIBC, AR_MIBC_CMC);
	REG_WRITE(ah, AR_FILT_OFDM, 0);
	REG_WRITE(ah, AR_FILT_CCK, 0);
}