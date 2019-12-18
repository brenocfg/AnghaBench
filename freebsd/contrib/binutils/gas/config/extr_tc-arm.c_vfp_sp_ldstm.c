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
typedef  enum vfp_ldstm_type { ____Placeholder_vfp_ldstm_type } vfp_ldstm_type ;
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; int imm; scalar_t__ writeback; } ;

/* Variables and functions */
 int VFP_LDSTMIA ; 
 int /*<<< orphan*/  VFP_REG_Sd ; 
 int WRITE_BACK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_arm_vfp_reg (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
vfp_sp_ldstm (enum vfp_ldstm_type ldstm_type)
{
  if (inst.operands[0].writeback)
    inst.instruction |= WRITE_BACK;
  else
    constraint (ldstm_type != VFP_LDSTMIA,
		_("this addressing mode requires base-register writeback"));
  inst.instruction |= inst.operands[0].reg << 16;
  encode_arm_vfp_reg (inst.operands[1].reg, VFP_REG_Sd);
  inst.instruction |= inst.operands[1].imm;
}