#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; } ;
struct TYPE_6__ {int instruction; TYPE_2__ reloc; void* error; TYPE_1__* operands; } ;
struct TYPE_4__ {int reg; int imm; scalar_t__ writeback; scalar_t__ preind; scalar_t__ postind; } ;

/* Variables and functions */
 int BFD_RELOC_ARM_ALU_PC_G0_NC ; 
 int BFD_RELOC_ARM_CP_OFF_IMM ; 
 int BFD_RELOC_ARM_LDC_SB_G2 ; 
 int BFD_RELOC_ARM_LDR_PC_G0 ; 
 int BFD_RELOC_ARM_T32_CP_OFF_IMM ; 
 int FAIL ; 
 int INDEX_UP ; 
 int PRE_INDEX ; 
 int REG_PC ; 
 int SUCCESS ; 
 int WRITE_BACK ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ inst ; 
 scalar_t__ thumb_mode ; 

__attribute__((used)) static int
encode_arm_cp_address (int i, int wb_ok, int unind_ok, int reloc_override)
{
  inst.instruction |= inst.operands[i].reg << 16;

  assert (!(inst.operands[i].preind && inst.operands[i].postind));

  if (!inst.operands[i].preind && !inst.operands[i].postind) /* unindexed */
    {
      assert (!inst.operands[i].writeback);
      if (!unind_ok)
	{
	  inst.error = _("instruction does not support unindexed addressing");
	  return FAIL;
	}
      inst.instruction |= inst.operands[i].imm;
      inst.instruction |= INDEX_UP;
      return SUCCESS;
    }

  if (inst.operands[i].preind)
    inst.instruction |= PRE_INDEX;

  if (inst.operands[i].writeback)
    {
      if (inst.operands[i].reg == REG_PC)
	{
	  inst.error = _("pc may not be used with write-back");
	  return FAIL;
	}
      if (!wb_ok)
	{
	  inst.error = _("instruction does not support writeback");
	  return FAIL;
	}
      inst.instruction |= WRITE_BACK;
    }

  if (reloc_override)
    inst.reloc.type = reloc_override;
  else if ((inst.reloc.type < BFD_RELOC_ARM_ALU_PC_G0_NC
            || inst.reloc.type > BFD_RELOC_ARM_LDC_SB_G2)
           && inst.reloc.type != BFD_RELOC_ARM_LDR_PC_G0)
    {
      if (thumb_mode)
        inst.reloc.type = BFD_RELOC_ARM_T32_CP_OFF_IMM;
      else
        inst.reloc.type = BFD_RELOC_ARM_CP_OFF_IMM;
    }

  return SUCCESS;
}