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
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_6__ {int instruction; TYPE_2__ reloc; TYPE_1__* operands; } ;
struct TYPE_4__ {int imm; int shift_kind; scalar_t__ shifted; int /*<<< orphan*/  negative; scalar_t__ immisreg; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_ARM_OFFSET_IMM ; 
 scalar_t__ BFD_RELOC_ARM_SHIFT_IMM ; 
 scalar_t__ BFD_RELOC_UNUSED ; 
 int INDEX_UP ; 
 int INST_IMMEDIATE ; 
 int SHIFT_ROR ; 
 int SHIFT_RRX ; 
 int /*<<< orphan*/  encode_arm_addr_mode_common (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ inst ; 

__attribute__((used)) static void
encode_arm_addr_mode_2 (int i, bfd_boolean is_t)
{
  encode_arm_addr_mode_common (i, is_t);

  if (inst.operands[i].immisreg)
    {
      inst.instruction |= INST_IMMEDIATE;  /* yes, this is backwards */
      inst.instruction |= inst.operands[i].imm;
      if (!inst.operands[i].negative)
	inst.instruction |= INDEX_UP;
      if (inst.operands[i].shifted)
	{
	  if (inst.operands[i].shift_kind == SHIFT_RRX)
	    inst.instruction |= SHIFT_ROR << 5;
	  else
	    {
	      inst.instruction |= inst.operands[i].shift_kind << 5;
	      inst.reloc.type = BFD_RELOC_ARM_SHIFT_IMM;
	    }
	}
    }
  else /* immediate offset in inst.reloc */
    {
      if (inst.reloc.type == BFD_RELOC_UNUSED)
	inst.reloc.type = BFD_RELOC_ARM_OFFSET_IMM;
    }
}