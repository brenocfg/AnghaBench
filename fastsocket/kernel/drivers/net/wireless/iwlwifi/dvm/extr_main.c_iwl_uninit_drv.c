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
struct iwl_priv {int /*<<< orphan*/  wowlan_sram; int /*<<< orphan*/  noa_data; int /*<<< orphan*/  beacon_cmd; int /*<<< orphan*/  scan_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwl_calib_free_results (struct iwl_priv*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_dereference_raw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_uninit_drv(struct iwl_priv *priv)
{
	kfree(priv->scan_cmd);
	kfree(priv->beacon_cmd);
	kfree(rcu_dereference_raw(priv->noa_data));
	iwl_calib_free_results(priv);
#ifdef CONFIG_IWLWIFI_DEBUGFS
	kfree(priv->wowlan_sram);
#endif
}