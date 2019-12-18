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
typedef  scalar_t__ u8 ;
struct qlcnic_trans_list {scalar_t__ count; int /*<<< orphan*/  lock; } ;
struct qlcnic_vf_info {int /*<<< orphan*/  state; int /*<<< orphan*/ * send_cmd; struct qlcnic_trans_list rcv_act; } ;
struct qlcnic_bc_trans {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 scalar_t__ QLC_BC_COMMAND ; 
 scalar_t__ QLC_BC_RESPONSE ; 
 int /*<<< orphan*/  QLC_BC_VF_SEND ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qlcnic_sriov_clear_trans(struct qlcnic_vf_info *vf,
				    struct qlcnic_bc_trans *trans, u8 type)
{
	struct qlcnic_trans_list *t_list;
	unsigned long flags;
	int ret = 0;

	if (type == QLC_BC_RESPONSE) {
		t_list = &vf->rcv_act;
		spin_lock_irqsave(&t_list->lock, flags);
		t_list->count--;
		list_del(&trans->list);
		if (t_list->count > 0)
			ret = 1;
		spin_unlock_irqrestore(&t_list->lock, flags);
	}
	if (type == QLC_BC_COMMAND) {
		while (test_and_set_bit(QLC_BC_VF_SEND, &vf->state))
			msleep(100);
		vf->send_cmd = NULL;
		clear_bit(QLC_BC_VF_SEND, &vf->state);
	}
	return ret;
}