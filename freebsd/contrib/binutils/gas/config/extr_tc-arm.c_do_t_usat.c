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
struct TYPE_6__ {scalar_t__ X_op; int X_add_number; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_2__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_3__ reloc; TYPE_1__* operands; } ;
struct TYPE_5__ {int reg; int imm; scalar_t__ shift_kind; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_UNUSED ; 
 scalar_t__ O_constant ; 
 scalar_t__ SHIFT_ASR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ inst ; 

__attribute__((used)) static void
do_t_usat (void)
{
  inst.instruction |= inst.operands[0].reg << 8;
  inst.instruction |= inst.operands[1].imm;
  inst.instruction |= inst.operands[2].reg << 16;

  if (inst.operands[3].present)
    {
      constraint (inst.reloc.exp.X_op != O_constant,
		  _("expression too complex"));
      if (inst.reloc.exp.X_add_number != 0)
	{
	  if (inst.operands[3].shift_kind == SHIFT_ASR)
	    inst.instruction |= 0x00200000;  /* sh bit */

	  inst.instruction |= (inst.reloc.exp.X_add_number & 0x1c) << 10;
	  inst.instruction |= (inst.reloc.exp.X_add_number & 0x03) << 6;
	}
      inst.reloc.type = BFD_RELOC_UNUSED;
    }
}