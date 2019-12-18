#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qlcnic_back_channel {int /*<<< orphan*/  bc_flr_wq; } ;
struct qlcnic_sriov {int num_vfs; TYPE_2__* vf_info; struct qlcnic_back_channel bc; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_4__ {int /*<<< orphan*/  flr_work; } ;
struct TYPE_3__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qlcnic_sriov_pf_del_flr_queue(struct qlcnic_adapter *adapter)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	struct qlcnic_back_channel *bc = &sriov->bc;
	int i;

	for (i = 0; i < sriov->num_vfs; i++)
		cancel_work_sync(&sriov->vf_info[i].flr_work);

	destroy_workqueue(bc->bc_flr_wq);
}