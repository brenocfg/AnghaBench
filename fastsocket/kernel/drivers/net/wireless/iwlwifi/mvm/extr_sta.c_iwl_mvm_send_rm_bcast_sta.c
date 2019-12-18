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
struct iwl_mvm_int_sta {int /*<<< orphan*/  sta_id; } ;
struct iwl_mvm {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWL_WARN (struct iwl_mvm*,char*) ; 
 int iwl_mvm_rm_sta_common (struct iwl_mvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_send_rm_bcast_sta(struct iwl_mvm *mvm,
			      struct iwl_mvm_int_sta *bsta)
{
	int ret;

	lockdep_assert_held(&mvm->mutex);

	ret = iwl_mvm_rm_sta_common(mvm, bsta->sta_id);
	if (ret)
		IWL_WARN(mvm, "Failed sending remove station\n");
	return ret;
}