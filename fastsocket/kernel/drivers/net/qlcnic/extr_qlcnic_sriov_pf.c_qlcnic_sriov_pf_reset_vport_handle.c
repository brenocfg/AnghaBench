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
typedef  scalar_t__ u8 ;
struct qlcnic_vport {scalar_t__ handle; } ;
struct qlcnic_sriov {TYPE_2__* vf_info; scalar_t__ vp_handle; } ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct TYPE_4__ {struct qlcnic_vport* vp; } ;
struct TYPE_3__ {scalar_t__ pci_func; struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int qlcnic_sriov_func_to_index (struct qlcnic_adapter*,scalar_t__) ; 

__attribute__((used)) static void qlcnic_sriov_pf_reset_vport_handle(struct qlcnic_adapter *adapter,
					       u8 func)
{
	struct qlcnic_sriov  *sriov = adapter->ahw->sriov;
	struct qlcnic_vport *vp;
	int index;

	if (adapter->ahw->pci_func == func) {
		sriov->vp_handle = 0;
	} else {
		index = qlcnic_sriov_func_to_index(adapter, func);
		if (index < 0)
			return;
		vp = sriov->vf_info[index].vp;
		vp->handle = 0;
	}
}