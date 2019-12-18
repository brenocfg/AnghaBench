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
struct ath_hw {TYPE_1__* caldata; } ;
struct ath9k_channel {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rtt_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar9003_hw_rtt_disable (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_enable (struct ath_hw*) ; 
 int ar9003_hw_rtt_force_restore (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_load_hist (struct ath_hw*) ; 
 int /*<<< orphan*/  ar9003_hw_rtt_set_mask (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_rfbus_done (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_rfbus_req (struct ath_hw*) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*) ; 

bool ar9003_hw_rtt_restore(struct ath_hw *ah, struct ath9k_channel *chan)
{
	bool restore;

	if (!ah->caldata)
		return false;

	if (!ah->caldata->rtt_done)
		return false;

	ar9003_hw_rtt_enable(ah);
	ar9003_hw_rtt_set_mask(ah, 0x10);

	if (!ath9k_hw_rfbus_req(ah)) {
		ath_err(ath9k_hw_common(ah), "Could not stop baseband\n");
		restore = false;
		goto fail;
	}

	ar9003_hw_rtt_load_hist(ah);
	restore = ar9003_hw_rtt_force_restore(ah);

fail:
	ath9k_hw_rfbus_done(ah);
	ar9003_hw_rtt_disable(ah);
	return restore;
}