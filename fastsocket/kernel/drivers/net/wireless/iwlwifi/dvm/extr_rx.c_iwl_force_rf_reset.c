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
struct iwl_rf_reset {scalar_t__ last_reset_jiffies; int /*<<< orphan*/  reset_success_count; int /*<<< orphan*/  reset_reject_count; int /*<<< orphan*/  reset_request_count; } ;
struct iwl_priv {struct iwl_rf_reset rf_reset; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOLINK ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_priv*,char*) ; 
 int /*<<< orphan*/  IWL_DEBUG_SCAN (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_DELAY_NEXT_FORCE_RF_RESET ; 
 int /*<<< orphan*/  STATUS_EXIT_PENDING ; 
 int /*<<< orphan*/  iwl_internal_short_hw_scan (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwl_is_any_associated (struct iwl_priv*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

int iwl_force_rf_reset(struct iwl_priv *priv, bool external)
{
	struct iwl_rf_reset *rf_reset;

	if (test_bit(STATUS_EXIT_PENDING, &priv->status))
		return -EAGAIN;

	if (!iwl_is_any_associated(priv)) {
		IWL_DEBUG_SCAN(priv, "force reset rejected: not associated\n");
		return -ENOLINK;
	}

	rf_reset = &priv->rf_reset;
	rf_reset->reset_request_count++;
	if (!external && rf_reset->last_reset_jiffies &&
	    time_after(rf_reset->last_reset_jiffies +
		       IWL_DELAY_NEXT_FORCE_RF_RESET, jiffies)) {
		IWL_DEBUG_INFO(priv, "RF reset rejected\n");
		rf_reset->reset_reject_count++;
		return -EAGAIN;
	}
	rf_reset->reset_success_count++;
	rf_reset->last_reset_jiffies = jiffies;

	/*
	 * There is no easy and better way to force reset the radio,
	 * the only known method is switching channel which will force to
	 * reset and tune the radio.
	 * Use internal short scan (single channel) operation to should
	 * achieve this objective.
	 * Driver should reset the radio when number of consecutive missed
	 * beacon, or any other uCode error condition detected.
	 */
	IWL_DEBUG_INFO(priv, "perform radio reset.\n");
	iwl_internal_short_hw_scan(priv);
	return 0;
}