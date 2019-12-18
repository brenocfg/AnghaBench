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
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; scalar_t__ imm; scalar_t__ immisreg; scalar_t__ postind; scalar_t__ writeback; scalar_t__ present; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int LOAD_BIT ; 
 int REG_LR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_arm_addr_mode_3 (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_ldrd (void)
{
  constraint (inst.operands[0].reg % 2 != 0,
	      _("first destination register must be even"));
  constraint (inst.operands[1].present
	      && inst.operands[1].reg != inst.operands[0].reg + 1,
	      _("can only load two consecutive registers"));
  constraint (inst.operands[0].reg == REG_LR, _("r14 not allowed here"));
  constraint (!inst.operands[2].isreg, _("'[' expected"));

  if (!inst.operands[1].present)
    inst.operands[1].reg = inst.operands[0].reg + 1;
  
  if (inst.instruction & LOAD_BIT)
    {
      /* encode_arm_addr_mode_3 will diagnose overlap between the base
	 register and the first register written; we have to diagnose
	 overlap between the base and the second register written here.	 */

      if (inst.operands[2].reg == inst.operands[1].reg
	  && (inst.operands[2].writeback || inst.operands[2].postind))
	as_warn (_("base register written back, and overlaps "
		   "second destination register"));

      /* For an index-register load, the index register must not overlap the
	 destination (even if not write-back).	*/
      else if (inst.operands[2].immisreg
	       && ((unsigned) inst.operands[2].imm == inst.operands[0].reg
		   || (unsigned) inst.operands[2].imm == inst.operands[1].reg))
	as_warn (_("index register overlaps destination register"));
    }

  inst.instruction |= inst.operands[0].reg << 12;
  encode_arm_addr_mode_3 (2, /*is_t=*/FALSE);
}