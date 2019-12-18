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
struct iwl_op_mode {int dummy; } ;
struct iwl_mvm {int /*<<< orphan*/  hw; TYPE_1__* nvm_sections; int /*<<< orphan*/  nvm_data; int /*<<< orphan*/ * phy_db; int /*<<< orphan*/  trans; int /*<<< orphan*/  scan_cmd; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct iwl_mvm* IWL_OP_MODE_GET_MVM (struct iwl_op_mode*) ; 
 int NVM_NUM_OF_SECTIONS ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_free_nvm_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_leds_exit (struct iwl_mvm*) ; 
 int /*<<< orphan*/  iwl_phy_db_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwl_trans_stop_hw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_op_mode_mvm_stop(struct iwl_op_mode *op_mode)
{
	struct iwl_mvm *mvm = IWL_OP_MODE_GET_MVM(op_mode);
	int i;

	iwl_mvm_leds_exit(mvm);

	ieee80211_unregister_hw(mvm->hw);

	kfree(mvm->scan_cmd);

	iwl_trans_stop_hw(mvm->trans, true);

	iwl_phy_db_free(mvm->phy_db);
	mvm->phy_db = NULL;

	iwl_free_nvm_data(mvm->nvm_data);
	for (i = 0; i < NVM_NUM_OF_SECTIONS; i++)
		kfree(mvm->nvm_sections[i].data);

	ieee80211_free_hw(mvm->hw);
}