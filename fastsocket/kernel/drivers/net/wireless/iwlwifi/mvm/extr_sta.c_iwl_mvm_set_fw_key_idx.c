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
struct iwl_mvm {int /*<<< orphan*/  fw_key_table; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int STA_KEY_IDX_INVALID ; 
 int STA_KEY_MAX_NUM ; 
 int /*<<< orphan*/  __set_bit (int,int /*<<< orphan*/ ) ; 
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwl_mvm_set_fw_key_idx(struct iwl_mvm *mvm)
{
	int i;

	lockdep_assert_held(&mvm->mutex);

	i = find_first_zero_bit(mvm->fw_key_table, STA_KEY_MAX_NUM);

	if (i == STA_KEY_MAX_NUM)
		return STA_KEY_IDX_INVALID;

	__set_bit(i, mvm->fw_key_table);

	return i;
}