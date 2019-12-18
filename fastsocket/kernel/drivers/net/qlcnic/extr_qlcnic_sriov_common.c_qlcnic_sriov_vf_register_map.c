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
typedef  int /*<<< orphan*/  u32 ;
struct qlcnic_hardware_context {int /*<<< orphan*/ * ext_reg_tbl; int /*<<< orphan*/ * reg_tbl; int /*<<< orphan*/ * hw_ops; } ;

/* Variables and functions */
 scalar_t__ qlcnic_83xx_ext_reg_tbl ; 
 scalar_t__ qlcnic_83xx_reg_tbl ; 
 int /*<<< orphan*/  qlcnic_sriov_vf_hw_ops ; 

void qlcnic_sriov_vf_register_map(struct qlcnic_hardware_context *ahw)
{
	ahw->hw_ops		= &qlcnic_sriov_vf_hw_ops;
	ahw->reg_tbl		= (u32 *)qlcnic_83xx_reg_tbl;
	ahw->ext_reg_tbl	= (u32 *)qlcnic_83xx_ext_reg_tbl;
}