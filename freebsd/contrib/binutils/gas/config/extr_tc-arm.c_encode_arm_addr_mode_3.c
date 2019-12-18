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
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_1__ reloc; int /*<<< orphan*/  instruction; TYPE_2__* operands; int /*<<< orphan*/  error; } ;
struct TYPE_5__ {int /*<<< orphan*/  negative; int /*<<< orphan*/  imm; scalar_t__ immisreg; scalar_t__ shifted; } ;

/* Variables and functions */
 scalar_t__ BFD_RELOC_ARM_OFFSET_IMM8 ; 
 scalar_t__ BFD_RELOC_UNUSED ; 
 int /*<<< orphan*/  HWOFFSET_IMM ; 
 int /*<<< orphan*/  INDEX_UP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  encode_arm_addr_mode_common (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ inst ; 

__attribute__((used)) static void
encode_arm_addr_mode_3 (int i, bfd_boolean is_t)
{
  if (inst.operands[i].immisreg && inst.operands[i].shifted)
    {
      inst.error = _("instruction does not accept scaled register index");
      return;
    }

  encode_arm_addr_mode_common (i, is_t);

  if (inst.operands[i].immisreg)
    {
      inst.instruction |= inst.operands[i].imm;
      if (!inst.operands[i].negative)
	inst.instruction |= INDEX_UP;
    }
  else /* immediate offset in inst.reloc */
    {
      inst.instruction |= HWOFFSET_IMM;
      if (inst.reloc.type == BFD_RELOC_UNUSED)
	inst.reloc.type = BFD_RELOC_ARM_OFFSET_IMM8;
    }
}