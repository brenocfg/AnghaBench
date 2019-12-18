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
typedef  size_t u8 ;
struct qlcnic_vf_info {size_t pci_func; } ;
struct qlcnic_adapter {TYPE_2__* ahw; } ;
struct TYPE_4__ {TYPE_1__* sriov; } ;
struct TYPE_3__ {size_t num_vfs; struct qlcnic_vf_info* vf_info; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ qlcnic_sriov_vf_check (struct qlcnic_adapter*) ; 

int qlcnic_sriov_func_to_index(struct qlcnic_adapter *adapter, u8 pci_func)
{
	struct qlcnic_vf_info *vf_info = adapter->ahw->sriov->vf_info;
	u8 i;

	if (qlcnic_sriov_vf_check(adapter))
		return 0;

	for (i = 0; i < adapter->ahw->sriov->num_vfs; i++) {
		if (vf_info[i].pci_func == pci_func)
			return i;
	}

	return -EINVAL;
}