#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int X_add_number; } ;
struct TYPE_6__ {int pc_rel; TYPE_1__ exp; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int size_req; int relax; int instruction; TYPE_3__* operands; TYPE_2__ reloc; } ;
struct TYPE_7__ {int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_ARM_T32_ADD_PC12 ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_THUMB_ADD ; 
 void* THUMB_OP16 (int) ; 
 int THUMB_OP32 (int) ; 
 TYPE_4__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_adr (void)
{
  if (unified_syntax && inst.size_req == 0 && inst.operands[0].reg <= 7)
    {
      /* Defer to section relaxation.  */
      inst.relax = inst.instruction;
      inst.instruction = THUMB_OP16 (inst.instruction);
      inst.instruction |= inst.operands[0].reg << 4;
    }
  else if (unified_syntax && inst.size_req != 2)
    {
      /* Generate a 32-bit opcode.  */
      inst.instruction = THUMB_OP32 (inst.instruction);
      inst.instruction |= inst.operands[0].reg << 8;
      inst.reloc.type = BFD_RELOC_ARM_T32_ADD_PC12;
      inst.reloc.pc_rel = 1;
    }
  else
    {
      /* Generate a 16-bit opcode.  */
      inst.instruction = THUMB_OP16 (inst.instruction);
      inst.reloc.type = BFD_RELOC_ARM_THUMB_ADD;
      inst.reloc.exp.X_add_number -= 4; /* PC relative adjust.  */
      inst.reloc.pc_rel = 1;

      inst.instruction |= inst.operands[0].reg << 4;
    }
}