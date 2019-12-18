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
typedef  int /*<<< orphan*/  u8 ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_ERR (struct iwl_mvm*,char*) ; 
 int iwl_mvm_power_disable (struct iwl_mvm*,struct ieee80211_vif*) ; 

__attribute__((used)) static void iwl_mvm_pm_disable_iterator(void *data, u8 *mac,
					struct ieee80211_vif *vif)
{
	struct iwl_mvm *mvm = data;
	int ret;

	ret = iwl_mvm_power_disable(mvm, vif);
	if (ret)
		IWL_ERR(mvm, "failed to disable power management\n");
}