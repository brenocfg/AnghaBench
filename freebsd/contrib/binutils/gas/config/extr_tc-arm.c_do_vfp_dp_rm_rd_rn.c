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
struct TYPE_4__ {TYPE_1__* operands; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFP_REG_Dd ; 
 int /*<<< orphan*/  VFP_REG_Dm ; 
 int /*<<< orphan*/  VFP_REG_Dn ; 
 int /*<<< orphan*/  encode_arm_vfp_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_vfp_dp_rm_rd_rn (void)
{
  encode_arm_vfp_reg (inst.operands[0].reg, VFP_REG_Dm);
  encode_arm_vfp_reg (inst.operands[1].reg, VFP_REG_Dd);
  encode_arm_vfp_reg (inst.operands[2].reg, VFP_REG_Dn);
}