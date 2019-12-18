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
struct iwl_tt_mgmt {scalar_t__ tt_previous_temp; int state; scalar_t__ tt_power_mode; int /*<<< orphan*/  ct_kill_waiting_tm; } ;
struct iwl_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  status; struct iwl_tt_mgmt thermal_throttle; } ;
typedef  scalar_t__ s32 ;
typedef  enum iwl_tt_state { ____Placeholder_iwl_tt_state } iwl_tt_state ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_DEBUG_TEMP (struct iwl_priv*,char*,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_priv*,char*) ; 
 scalar_t__ IWL_MINIMAL_POWER_THRESHOLD ; 
 scalar_t__ IWL_POWER_INDEX_3 ; 
 scalar_t__ IWL_POWER_INDEX_4 ; 
 scalar_t__ IWL_POWER_INDEX_5 ; 
 scalar_t__ IWL_REDUCED_PERFORMANCE_THRESHOLD_1 ; 
 scalar_t__ IWL_REDUCED_PERFORMANCE_THRESHOLD_2 ; 
#define  IWL_TI_0 130 
#define  IWL_TI_1 129 
#define  IWL_TI_2 128 
 int IWL_TI_CT_KILL ; 
 scalar_t__ IWL_TT_INCREASE_MARGIN ; 
 int /*<<< orphan*/  STATUS_CT_KILL ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_perform_ct_kill_task (struct iwl_priv*,int) ; 
 scalar_t__ iwl_power_update_mode (struct iwl_priv*,int) ; 
 int /*<<< orphan*/  iwl_prepare_ct_kill_task (struct iwl_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_legacy_tt_handler(struct iwl_priv *priv, s32 temp, bool force)
{
	struct iwl_tt_mgmt *tt = &priv->thermal_throttle;
	enum iwl_tt_state old_state;

#ifdef CONFIG_IWLWIFI_DEBUG
	if ((tt->tt_previous_temp) &&
	    (temp > tt->tt_previous_temp) &&
	    ((temp - tt->tt_previous_temp) >
	    IWL_TT_INCREASE_MARGIN)) {
		IWL_DEBUG_TEMP(priv,
			"Temperature increase %d degree Celsius\n",
			(temp - tt->tt_previous_temp));
	}
#endif
	old_state = tt->state;
	/* in Celsius */
	if (temp >= IWL_MINIMAL_POWER_THRESHOLD)
		tt->state = IWL_TI_CT_KILL;
	else if (temp >= IWL_REDUCED_PERFORMANCE_THRESHOLD_2)
		tt->state = IWL_TI_2;
	else if (temp >= IWL_REDUCED_PERFORMANCE_THRESHOLD_1)
		tt->state = IWL_TI_1;
	else
		tt->state = IWL_TI_0;

#ifdef CONFIG_IWLWIFI_DEBUG
	tt->tt_previous_temp = temp;
#endif
	/* stop ct_kill_waiting_tm timer */
	del_timer_sync(&priv->thermal_throttle.ct_kill_waiting_tm);
	if (tt->state != old_state) {
		switch (tt->state) {
		case IWL_TI_0:
			/*
			 * When the system is ready to go back to IWL_TI_0
			 * we only have to call iwl_power_update_mode() to
			 * do so.
			 */
			break;
		case IWL_TI_1:
			tt->tt_power_mode = IWL_POWER_INDEX_3;
			break;
		case IWL_TI_2:
			tt->tt_power_mode = IWL_POWER_INDEX_4;
			break;
		default:
			tt->tt_power_mode = IWL_POWER_INDEX_5;
			break;
		}
		mutex_lock(&priv->mutex);
		if (old_state == IWL_TI_CT_KILL)
			clear_bit(STATUS_CT_KILL, &priv->status);
		if (tt->state != IWL_TI_CT_KILL &&
		    iwl_power_update_mode(priv, true)) {
			/* TT state not updated
			 * try again during next temperature read
			 */
			if (old_state == IWL_TI_CT_KILL)
				set_bit(STATUS_CT_KILL, &priv->status);
			tt->state = old_state;
			IWL_ERR(priv, "Cannot update power mode, "
					"TT state not updated\n");
		} else {
			if (tt->state == IWL_TI_CT_KILL) {
				if (force) {
					set_bit(STATUS_CT_KILL, &priv->status);
					iwl_perform_ct_kill_task(priv, true);
				} else {
					iwl_prepare_ct_kill_task(priv);
					tt->state = old_state;
				}
			} else if (old_state == IWL_TI_CT_KILL &&
				 tt->state != IWL_TI_CT_KILL)
				iwl_perform_ct_kill_task(priv, false);
			IWL_DEBUG_TEMP(priv, "Temperature state changed %u\n",
					tt->state);
			IWL_DEBUG_TEMP(priv, "Power Index change to %u\n",
					tt->tt_power_mode);
		}
		mutex_unlock(&priv->mutex);
	}
}