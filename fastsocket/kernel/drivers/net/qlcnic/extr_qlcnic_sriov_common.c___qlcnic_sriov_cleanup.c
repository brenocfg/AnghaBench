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
struct qlcnic_back_channel {int /*<<< orphan*/  bc_trans_wq; int /*<<< orphan*/  bc_async_wq; } ;
struct qlcnic_vf_info {int num_vfs; struct qlcnic_vf_info* vf_info; struct qlcnic_vf_info* vp; int /*<<< orphan*/  rcv_act; int /*<<< orphan*/  trans_work; int /*<<< orphan*/  rcv_pend; struct qlcnic_back_channel bc; } ;
struct qlcnic_sriov {int num_vfs; struct qlcnic_sriov* vf_info; struct qlcnic_sriov* vp; int /*<<< orphan*/  rcv_act; int /*<<< orphan*/  trans_work; int /*<<< orphan*/  rcv_pend; struct qlcnic_back_channel bc; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_2__ {struct qlcnic_vf_info* sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlcnic_vf_info*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cleanup_async_list (struct qlcnic_back_channel*) ; 
 int /*<<< orphan*/  qlcnic_sriov_cleanup_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlcnic_sriov_enable_check (struct qlcnic_adapter*) ; 

void __qlcnic_sriov_cleanup(struct qlcnic_adapter *adapter)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	struct qlcnic_back_channel *bc = &sriov->bc;
	struct qlcnic_vf_info *vf;
	int i;

	if (!qlcnic_sriov_enable_check(adapter))
		return;

	qlcnic_sriov_cleanup_async_list(bc);
	destroy_workqueue(bc->bc_async_wq);

	for (i = 0; i < sriov->num_vfs; i++) {
		vf = &sriov->vf_info[i];
		qlcnic_sriov_cleanup_list(&vf->rcv_pend);
		cancel_work_sync(&vf->trans_work);
		qlcnic_sriov_cleanup_list(&vf->rcv_act);
	}

	destroy_workqueue(bc->bc_trans_wq);

	for (i = 0; i < sriov->num_vfs; i++)
		kfree(sriov->vf_info[i].vp);

	kfree(sriov->vf_info);
	kfree(adapter->ahw->sriov);
}