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
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct iwl_priv {TYPE_2__ ucode_trace; TYPE_2__ statistics_periodic; TYPE_1__* cfg; int /*<<< orphan*/  hw_roc_disable_work; int /*<<< orphan*/  bt_runtime_config; int /*<<< orphan*/  bt_full_concurrency; int /*<<< orphan*/  tx_flush; int /*<<< orphan*/  run_time_calib_work; int /*<<< orphan*/  beacon_update; int /*<<< orphan*/  restart; int /*<<< orphan*/  workqueue; } ;
struct TYPE_3__ {scalar_t__ bt_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  iwl_bg_beacon_update ; 
 int /*<<< orphan*/  iwl_bg_bt_full_concurrency ; 
 int /*<<< orphan*/  iwl_bg_bt_runtime_config ; 
 int /*<<< orphan*/  iwl_bg_restart ; 
 int /*<<< orphan*/  iwl_bg_run_time_calib_work ; 
 int /*<<< orphan*/  iwl_bg_statistics_periodic ; 
 int /*<<< orphan*/  iwl_bg_tx_flush ; 
 int /*<<< orphan*/  iwl_bg_ucode_trace ; 
 int /*<<< orphan*/  iwl_setup_scan_deferred_work (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_bt_setup_deferred_work (struct iwl_priv*) ; 
 int /*<<< orphan*/  iwlagn_disable_roc_work ; 

__attribute__((used)) static void iwl_setup_deferred_work(struct iwl_priv *priv)
{
	priv->workqueue = create_singlethread_workqueue(DRV_NAME);

	INIT_WORK(&priv->restart, iwl_bg_restart);
	INIT_WORK(&priv->beacon_update, iwl_bg_beacon_update);
	INIT_WORK(&priv->run_time_calib_work, iwl_bg_run_time_calib_work);
	INIT_WORK(&priv->tx_flush, iwl_bg_tx_flush);
	INIT_WORK(&priv->bt_full_concurrency, iwl_bg_bt_full_concurrency);
	INIT_WORK(&priv->bt_runtime_config, iwl_bg_bt_runtime_config);
	INIT_DELAYED_WORK(&priv->hw_roc_disable_work,
			  iwlagn_disable_roc_work);

	iwl_setup_scan_deferred_work(priv);

	if (priv->cfg->bt_params)
		iwlagn_bt_setup_deferred_work(priv);

	init_timer(&priv->statistics_periodic);
	priv->statistics_periodic.data = (unsigned long)priv;
	priv->statistics_periodic.function = iwl_bg_statistics_periodic;

	init_timer(&priv->ucode_trace);
	priv->ucode_trace.data = (unsigned long)priv;
	priv->ucode_trace.function = iwl_bg_ucode_trace;
}