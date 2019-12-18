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
struct TYPE_5__ {scalar_t__ X_op; scalar_t__ X_add_number; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; TYPE_1__ exp; } ;
struct TYPE_8__ {int instruction; TYPE_3__ reloc; TYPE_2__* operands; } ;
struct TYPE_6__ {int reg; scalar_t__ negative; scalar_t__ shifted; scalar_t__ immisreg; scalar_t__ writeback; scalar_t__ postind; int /*<<< orphan*/  preind; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_ADDR_MODE ; 
 int /*<<< orphan*/  BFD_RELOC_UNUSED ; 
 scalar_t__ O_constant ; 
 int REG_PC ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_4__ inst ; 

__attribute__((used)) static void
do_ldrex (void)
{
  constraint (!inst.operands[1].isreg || !inst.operands[1].preind
	      || inst.operands[1].postind || inst.operands[1].writeback
	      || inst.operands[1].immisreg || inst.operands[1].shifted
	      || inst.operands[1].negative
	      /* This can arise if the programmer has written
		   strex rN, rM, foo
		 or if they have mistakenly used a register name as the last
		 operand,  eg:
		   strex rN, rM, rX
		 It is very difficult to distinguish between these two cases
		 because "rX" might actually be a label. ie the register
		 name has been occluded by a symbol of the same name. So we
		 just generate a general 'bad addressing mode' type error
		 message and leave it up to the programmer to discover the
		 true cause and fix their mistake.  */
	      || (inst.operands[1].reg == REG_PC),
	      BAD_ADDR_MODE);

  constraint (inst.reloc.exp.X_op != O_constant
	      || inst.reloc.exp.X_add_number != 0,
	      _("offset must be zero in ARM encoding"));

  inst.instruction |= inst.operands[0].reg << 12;
  inst.instruction |= inst.operands[1].reg << 16;
  inst.reloc.type = BFD_RELOC_UNUSED;
}