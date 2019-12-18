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
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_info {int dummy; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int qlcnic_sriov_pf_cal_res_limit (struct qlcnic_adapter*,struct qlcnic_info*,int /*<<< orphan*/ ) ; 
 int qlcnic_sriov_set_vf_acl (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qlcnic_sriov_set_vf_vport_info(struct qlcnic_adapter *adapter,
					  u16 func)
{
	struct qlcnic_info defvp_info;
	int err;

	err = qlcnic_sriov_pf_cal_res_limit(adapter, &defvp_info, func);
	if (err)
		return -EIO;

	err = qlcnic_sriov_set_vf_acl(adapter, func);
	if (err)
		return err;

	return 0;
}