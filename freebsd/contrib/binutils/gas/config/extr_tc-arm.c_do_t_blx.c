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
struct TYPE_4__ {int pc_rel; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int instruction; TYPE_1__ reloc; TYPE_2__* operands; } ;
struct TYPE_5__ {int reg; scalar_t__ isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_BRANCH ; 
 int /*<<< orphan*/  BFD_RELOC_THUMB_PCREL_BLX ; 
 int /*<<< orphan*/  BFD_RELOC_THUMB_PCREL_BRANCH23 ; 
 scalar_t__ EF_ARM_EABI_VER4 ; 
 scalar_t__ EF_ARM_EABI_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int current_it_mask ; 
 TYPE_3__ inst ; 
 int /*<<< orphan*/  meabi_flags ; 

__attribute__((used)) static void
do_t_blx (void)
{
  constraint (current_it_mask && current_it_mask != 0x10, BAD_BRANCH);
  if (inst.operands[0].isreg)
    /* We have a register, so this is BLX(2).  */
    inst.instruction |= inst.operands[0].reg << 3;
  else
    {
      /* No register.  This must be BLX(1).  */
      inst.instruction = 0xf000e800;
#ifdef OBJ_ELF
      if (EF_ARM_EABI_VERSION (meabi_flags) >= EF_ARM_EABI_VER4)
	inst.reloc.type = BFD_RELOC_THUMB_PCREL_BRANCH23;
      else
#endif
	inst.reloc.type = BFD_RELOC_THUMB_PCREL_BLX;
      inst.reloc.pc_rel = 1;
    }
}