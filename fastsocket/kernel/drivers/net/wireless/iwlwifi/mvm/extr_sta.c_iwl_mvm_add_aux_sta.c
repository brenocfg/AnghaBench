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
struct iwl_mvm {int /*<<< orphan*/  aux_sta; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_INDEX_AUX ; 
 int iwl_mvm_add_int_sta_common (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwl_mvm_allocate_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_mvm_dealloc_int_sta (struct iwl_mvm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int iwl_mvm_add_aux_sta(struct iwl_mvm *mvm)
{
	int ret;

	lockdep_assert_held(&mvm->mutex);

	/* Add the aux station, but without any queues */
	ret = iwl_mvm_allocate_int_sta(mvm, &mvm->aux_sta, 0);
	if (ret)
		return ret;

	ret = iwl_mvm_add_int_sta_common(mvm, &mvm->aux_sta, NULL,
					 MAC_INDEX_AUX, 0);

	if (ret)
		iwl_mvm_dealloc_int_sta(mvm, &mvm->aux_sta);
	return ret;
}