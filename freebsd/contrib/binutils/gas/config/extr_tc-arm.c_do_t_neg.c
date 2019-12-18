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
typedef  int bfd_boolean ;
struct TYPE_4__ {int instruction; int size_req; TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_HIREG ; 
 int /*<<< orphan*/  BAD_THUMB32 ; 
 int FALSE ; 
 void* THUMB_OP16 (int) ; 
 int THUMB_OP32 (int) ; 
 int THUMB_SETS_FLAGS (int) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 scalar_t__ current_it_mask ; 
 TYPE_2__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_neg (void)
{
  if (unified_syntax)
    {
      bfd_boolean narrow;

      if (THUMB_SETS_FLAGS (inst.instruction))
	narrow = (current_it_mask == 0);
      else
	narrow = (current_it_mask != 0);
      if (inst.operands[0].reg > 7 || inst.operands[1].reg > 7)
	narrow = FALSE;
      if (inst.size_req == 4)
	narrow = FALSE;

      if (!narrow)
	{
	  inst.instruction = THUMB_OP32 (inst.instruction);
	  inst.instruction |= inst.operands[0].reg << 8;
	  inst.instruction |= inst.operands[1].reg << 16;
	}
      else
	{
	  inst.instruction = THUMB_OP16 (inst.instruction);
	  inst.instruction |= inst.operands[0].reg;
	  inst.instruction |= inst.operands[1].reg << 3;
	}
    }
  else
    {
      constraint (inst.operands[0].reg > 7 || inst.operands[1].reg > 7,
		  BAD_HIREG);
      constraint (THUMB_SETS_FLAGS (inst.instruction), BAD_THUMB32);

      inst.instruction = THUMB_OP16 (inst.instruction);
      inst.instruction |= inst.operands[0].reg;
      inst.instruction |= inst.operands[1].reg << 3;
    }
}