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
struct qlcnic_vf_info {struct qlcnic_adapter* adapter; } ;
struct qlcnic_sriov {int dummy; } ;
struct qlcnic_adapter {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qlcnic_sriov_pf_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_sriov_pf_handle_flr (struct qlcnic_sriov*,struct qlcnic_vf_info*) ; 

__attribute__((used)) static void qlcnic_sriov_handle_flr_event(struct qlcnic_sriov *sriov,
					  struct qlcnic_vf_info *vf)
{
	struct qlcnic_adapter *adapter = vf->adapter;

	if (qlcnic_sriov_pf_check(adapter))
		qlcnic_sriov_pf_handle_flr(sriov, vf);
	else
		dev_err(&adapter->pdev->dev,
			"Invalid event to VF. VF should not get FLR event\n");
}