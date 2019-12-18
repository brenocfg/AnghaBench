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
struct completion {int dummy; } ;
struct qlcnic_vf_info {int /*<<< orphan*/  state; struct completion ch_free_cmpl; } ;
struct qlcnic_bc_trans {int /*<<< orphan*/  trans_state; struct qlcnic_vf_info* vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_ABORT ; 
 int /*<<< orphan*/  QLC_BC_VF_CHANNEL ; 
 int /*<<< orphan*/  QLC_MBOX_CH_FREE_TIMEOUT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_handle_multi_frags (struct qlcnic_bc_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_sriov_wait_for_channel_free(struct qlcnic_bc_trans *trans,
					       u8 type)
{
	struct qlcnic_vf_info *vf = trans->vf;
	struct completion *cmpl = &vf->ch_free_cmpl;

	if (!wait_for_completion_timeout(cmpl, QLC_MBOX_CH_FREE_TIMEOUT)) {
		trans->trans_state = QLC_ABORT;
		return;
	}

	clear_bit(QLC_BC_VF_CHANNEL, &vf->state);
	qlcnic_sriov_handle_multi_frags(trans, type);
}