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
typedef  int bfd_boolean ;
struct TYPE_6__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_2__ exp; } ;
struct TYPE_8__ {int instruction; int size_req; TYPE_3__ reloc; TYPE_1__* operands; } ;
struct TYPE_5__ {int reg; int /*<<< orphan*/  isreg; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_ARM_T32_IMMEDIATE ; 
 int /*<<< orphan*/  BFD_RELOC_UNUSED ; 
 int FALSE ; 
 scalar_t__ O_constant ; 
 int THUMB_OP16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_MNEM_negs ; 
 scalar_t__ current_it_mask ; 
 int /*<<< orphan*/  encode_thumb32_shifted_operand (int) ; 
 TYPE_4__ inst ; 
 int /*<<< orphan*/  unified_syntax ; 

__attribute__((used)) static void
do_t_rsb (void)
{
  int Rd, Rs;

  Rd = inst.operands[0].reg;
  Rs = (inst.operands[1].present
	? inst.operands[1].reg    /* Rd, Rs, foo */
	: inst.operands[0].reg);  /* Rd, foo -> Rd, Rd, foo */

  inst.instruction |= Rd << 8;
  inst.instruction |= Rs << 16;
  if (!inst.operands[2].isreg)
    {
      bfd_boolean narrow;

      if ((inst.instruction & 0x00100000) != 0)
	narrow = (current_it_mask == 0);
      else
	narrow = (current_it_mask != 0);

      if (Rd > 7 || Rs > 7)
	narrow = FALSE;

      if (inst.size_req == 4 || !unified_syntax)
	narrow = FALSE;

      if (inst.reloc.exp.X_op != O_constant
	  || inst.reloc.exp.X_add_number != 0)
	narrow = FALSE;

      /* Turn rsb #0 into 16-bit neg.  We should probably do this via
         relaxation, but it doesn't seem worth the hassle.  */
      if (narrow)
	{
	  inst.reloc.type = BFD_RELOC_UNUSED;
	  inst.instruction = THUMB_OP16 (T_MNEM_negs);
	  inst.instruction |= Rs << 3;
	  inst.instruction |= Rd;
	}
      else
	{
	  inst.instruction = (inst.instruction & 0xe1ffffff) | 0x10000000;
	  inst.reloc.type = BFD_RELOC_ARM_T32_IMMEDIATE;
	}
    }
  else
    encode_thumb32_shifted_operand (2);
}