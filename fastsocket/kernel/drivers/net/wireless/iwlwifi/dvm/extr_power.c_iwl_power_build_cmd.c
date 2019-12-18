#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ debug_sleep_level_override; } ;
struct iwl_priv {TYPE_5__ power_data; TYPE_4__* hw; TYPE_2__* cfg; scalar_t__ wowlan; } ;
struct iwl_powertable_cmd {int dummy; } ;
struct TYPE_12__ {scalar_t__ power_level; } ;
struct TYPE_9__ {int flags; scalar_t__ ps_dtim_period; } ;
struct TYPE_10__ {TYPE_3__ conf; } ;
struct TYPE_8__ {TYPE_1__* base_params; } ;
struct TYPE_7__ {int /*<<< orphan*/  no_idle_support; } ;

/* Variables and functions */
 int IEEE80211_CONF_IDLE ; 
 int IEEE80211_CONF_PS ; 
 scalar_t__ IWL_POWER_INDEX_1 ; 
 scalar_t__ IWL_POWER_INDEX_5 ; 
 scalar_t__ IWL_POWER_NUM ; 
 int /*<<< orphan*/  iwl_power_sleep_cam_cmd (struct iwl_priv*,struct iwl_powertable_cmd*) ; 
 int /*<<< orphan*/  iwl_static_sleep_cmd (struct iwl_priv*,struct iwl_powertable_cmd*,scalar_t__,int) ; 
 scalar_t__ iwl_tt_current_power_mode (struct iwl_priv*) ; 
 scalar_t__ iwl_tt_is_low_power_state (struct iwl_priv*) ; 
 TYPE_6__ iwlwifi_mod_params ; 

__attribute__((used)) static void iwl_power_build_cmd(struct iwl_priv *priv,
				struct iwl_powertable_cmd *cmd)
{
	bool enabled = priv->hw->conf.flags & IEEE80211_CONF_PS;
	int dtimper;

	dtimper = priv->hw->conf.ps_dtim_period ?: 1;

	if (priv->wowlan)
		iwl_static_sleep_cmd(priv, cmd, IWL_POWER_INDEX_5, dtimper);
	else if (!priv->cfg->base_params->no_idle_support &&
		 priv->hw->conf.flags & IEEE80211_CONF_IDLE)
		iwl_static_sleep_cmd(priv, cmd, IWL_POWER_INDEX_5, 20);
	else if (iwl_tt_is_low_power_state(priv)) {
		/* in thermal throttling low power state */
		iwl_static_sleep_cmd(priv, cmd,
		    iwl_tt_current_power_mode(priv), dtimper);
	} else if (!enabled)
		iwl_power_sleep_cam_cmd(priv, cmd);
	else if (priv->power_data.debug_sleep_level_override >= 0)
		iwl_static_sleep_cmd(priv, cmd,
				     priv->power_data.debug_sleep_level_override,
				     dtimper);
	else {
		/* Note that the user parameter is 1-5 (according to spec),
		but we pass 0-4 because it acts as an array index. */
		if (iwlwifi_mod_params.power_level > IWL_POWER_INDEX_1 &&
		    iwlwifi_mod_params.power_level <= IWL_POWER_NUM)
			iwl_static_sleep_cmd(priv, cmd,
				iwlwifi_mod_params.power_level - 1, dtimper);
		else
			iwl_static_sleep_cmd(priv, cmd,
				IWL_POWER_INDEX_1, dtimper);
	}
}