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
struct completion {int dummy; } ;
struct qlcnic_bc_trans {int /*<<< orphan*/  trans_state; struct completion resp_cmpl; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_ABORT ; 
 int /*<<< orphan*/  QLC_END ; 
 int /*<<< orphan*/  QLC_MBOX_RESP_TIMEOUT ; 
 scalar_t__ wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void qlcnic_sriov_wait_for_resp(struct qlcnic_bc_trans *trans)
{
	struct completion *cmpl = &trans->resp_cmpl;

	if (wait_for_completion_timeout(cmpl, QLC_MBOX_RESP_TIMEOUT))
		trans->trans_state = QLC_END;
	else
		trans->trans_state = QLC_ABORT;

	return;
}