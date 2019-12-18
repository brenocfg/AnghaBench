#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int q_tx_num; } ;
struct TYPE_4__ {TYPE_1__ cap_queues; } ;
struct ath5k_hw {scalar_t__ ah_version; scalar_t__ ah_bwmode; int /*<<< orphan*/  ah_coverage_class; TYPE_2__ ah_capabilities; } ;

/* Variables and functions */
 scalar_t__ AR5K_AR5210 ; 
 scalar_t__ AR5K_BWMODE_40MHZ ; 
 int /*<<< orphan*/  AR5K_DCU_GBL_IFS_MISC ; 
 int /*<<< orphan*/  AR5K_DCU_GBL_IFS_MISC_TURBO_MODE ; 
 int /*<<< orphan*/  AR5K_REG_ENABLE_BITS (struct ath5k_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH5K_ERR (struct ath5k_hw*,char*,int) ; 
 unsigned int ath5k_hw_get_default_slottime (struct ath5k_hw*) ; 
 int ath5k_hw_reset_tx_queue (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_hw_set_ifs_intervals (struct ath5k_hw*,unsigned int) ; 
 int /*<<< orphan*/  ath5k_hw_set_tx_retry_limits (struct ath5k_hw*,int /*<<< orphan*/ ) ; 

int
ath5k_hw_init_queues(struct ath5k_hw *ah)
{
	int i, ret;

	/* TODO: HW Compression support for data queues */
	/* TODO: Burst prefetch for data queues */

	/*
	 * Reset queues and start beacon timers at the end of the reset routine
	 * This also sets QCU mask on each DCU for 1:1 qcu to dcu mapping
	 * Note: If we want we can assign multiple qcus on one dcu.
	 */
	if (ah->ah_version != AR5K_AR5210)
		for (i = 0; i < ah->ah_capabilities.cap_queues.q_tx_num; i++) {
			ret = ath5k_hw_reset_tx_queue(ah, i);
			if (ret) {
				ATH5K_ERR(ah,
					"failed to reset TX queue #%d\n", i);
				return ret;
			}
		}
	else
		/* No QCU/DCU on AR5210, just set tx
		 * retry limits. We set IFS parameters
		 * on ath5k_hw_set_ifs_intervals */
		ath5k_hw_set_tx_retry_limits(ah, 0);

	/* Set the turbo flag when operating on 40MHz */
	if (ah->ah_bwmode == AR5K_BWMODE_40MHZ)
		AR5K_REG_ENABLE_BITS(ah, AR5K_DCU_GBL_IFS_MISC,
				AR5K_DCU_GBL_IFS_MISC_TURBO_MODE);

	/* If we didn't set IFS timings through
	 * ath5k_hw_set_coverage_class make sure
	 * we set them here */
	if (!ah->ah_coverage_class) {
		unsigned int slot_time = ath5k_hw_get_default_slottime(ah);
		ath5k_hw_set_ifs_intervals(ah, slot_time);
	}

	return 0;
}