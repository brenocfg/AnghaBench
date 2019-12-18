#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct il_priv {int /*<<< orphan*/  disable_tx_power_cal; int /*<<< orphan*/  disable_chain_noise_cal; TYPE_3__* cfg; int /*<<< orphan*/  disable_sens_cal; struct dentry* debugfs_dir; TYPE_2__* hw; } ;
struct dentry {int dummy; } ;
struct TYPE_6__ {scalar_t__ chain_noise_calib_by_driver; scalar_t__ sensitivity_calib_by_driver; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct TYPE_4__ {struct dentry* debugfsdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD_BOOL (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUGFS_ADD_FILE (int /*<<< orphan*/ ,struct dentry*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  chain_noise ; 
 int /*<<< orphan*/  channels ; 
 int /*<<< orphan*/  clear_traffic_stats ; 
 int /*<<< orphan*/  clear_ucode_stats ; 
 struct dentry* debugfs_create_dir (char const*,struct dentry*) ; 
 int /*<<< orphan*/  disable_chain_noise ; 
 int /*<<< orphan*/  disable_ht40 ; 
 int /*<<< orphan*/  disable_sensitivity ; 
 int /*<<< orphan*/  disable_tx_power ; 
 int /*<<< orphan*/  fh_reg ; 
 int /*<<< orphan*/  force_reset ; 
 int /*<<< orphan*/  il_dbgfs_unregister (struct il_priv*) ; 
 int /*<<< orphan*/  interrupt ; 
 int /*<<< orphan*/  missed_beacon ; 
 int /*<<< orphan*/  nvm ; 
 int /*<<< orphan*/  power_save_status ; 
 int /*<<< orphan*/  qos ; 
 int /*<<< orphan*/  rx_queue ; 
 int /*<<< orphan*/  rx_stats ; 
 int /*<<< orphan*/  rxon_filter_flags ; 
 int /*<<< orphan*/  rxon_flags ; 
 int /*<<< orphan*/  sensitivity ; 
 int /*<<< orphan*/  sram ; 
 int /*<<< orphan*/  stations ; 
 int /*<<< orphan*/  status ; 
 int /*<<< orphan*/  tx_queue ; 
 int /*<<< orphan*/  tx_stats ; 
 int /*<<< orphan*/  ucode_general_stats ; 
 int /*<<< orphan*/  ucode_rx_stats ; 
 int /*<<< orphan*/  ucode_tx_stats ; 
 int /*<<< orphan*/  wd_timeout ; 

int
il_dbgfs_register(struct il_priv *il, const char *name)
{
	struct dentry *phyd = il->hw->wiphy->debugfsdir;
	struct dentry *dir_drv, *dir_data, *dir_rf, *dir_debug;

	dir_drv = debugfs_create_dir(name, phyd);
	if (!dir_drv)
		return -ENOMEM;

	il->debugfs_dir = dir_drv;

	dir_data = debugfs_create_dir("data", dir_drv);
	if (!dir_data)
		goto err;
	dir_rf = debugfs_create_dir("rf", dir_drv);
	if (!dir_rf)
		goto err;
	dir_debug = debugfs_create_dir("debug", dir_drv);
	if (!dir_debug)
		goto err;

	DEBUGFS_ADD_FILE(nvm, dir_data, S_IRUSR);
	DEBUGFS_ADD_FILE(sram, dir_data, S_IWUSR | S_IRUSR);
	DEBUGFS_ADD_FILE(stations, dir_data, S_IRUSR);
	DEBUGFS_ADD_FILE(channels, dir_data, S_IRUSR);
	DEBUGFS_ADD_FILE(status, dir_data, S_IRUSR);
	DEBUGFS_ADD_FILE(interrupt, dir_data, S_IWUSR | S_IRUSR);
	DEBUGFS_ADD_FILE(qos, dir_data, S_IRUSR);
	DEBUGFS_ADD_FILE(disable_ht40, dir_data, S_IWUSR | S_IRUSR);
	DEBUGFS_ADD_FILE(rx_stats, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(tx_stats, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(rx_queue, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(tx_queue, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(power_save_status, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(clear_ucode_stats, dir_debug, S_IWUSR);
	DEBUGFS_ADD_FILE(clear_traffic_stats, dir_debug, S_IWUSR);
	DEBUGFS_ADD_FILE(fh_reg, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(missed_beacon, dir_debug, S_IWUSR);
	DEBUGFS_ADD_FILE(force_reset, dir_debug, S_IWUSR | S_IRUSR);
	DEBUGFS_ADD_FILE(ucode_rx_stats, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(ucode_tx_stats, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(ucode_general_stats, dir_debug, S_IRUSR);

	if (il->cfg->sensitivity_calib_by_driver)
		DEBUGFS_ADD_FILE(sensitivity, dir_debug, S_IRUSR);
	if (il->cfg->chain_noise_calib_by_driver)
		DEBUGFS_ADD_FILE(chain_noise, dir_debug, S_IRUSR);
	DEBUGFS_ADD_FILE(rxon_flags, dir_debug, S_IWUSR);
	DEBUGFS_ADD_FILE(rxon_filter_flags, dir_debug, S_IWUSR);
	DEBUGFS_ADD_FILE(wd_timeout, dir_debug, S_IWUSR);
	if (il->cfg->sensitivity_calib_by_driver)
		DEBUGFS_ADD_BOOL(disable_sensitivity, dir_rf,
				 &il->disable_sens_cal);
	if (il->cfg->chain_noise_calib_by_driver)
		DEBUGFS_ADD_BOOL(disable_chain_noise, dir_rf,
				 &il->disable_chain_noise_cal);
	DEBUGFS_ADD_BOOL(disable_tx_power, dir_rf, &il->disable_tx_power_cal);
	return 0;

err:
	IL_ERR("Can't create the debugfs directory\n");
	il_dbgfs_unregister(il);
	return -ENOMEM;
}