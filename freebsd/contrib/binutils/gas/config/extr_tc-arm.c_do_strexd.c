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
struct TYPE_3__ {int reg; scalar_t__ present; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_OVERLAP ; 
 int REG_LR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_strexd (void)
{
  constraint (inst.operands[1].reg % 2 != 0,
	      _("even register required"));
  constraint (inst.operands[2].present
	      && inst.operands[2].reg != inst.operands[1].reg + 1,
	      _("can only store two consecutive registers"));
  /* If op 2 were present and equal to PC, this function wouldn't
     have been called in the first place.  */
  constraint (inst.operands[1].reg == REG_LR, _("r14 not allowed here"));

  constraint (inst.operands[0].reg == inst.operands[1].reg
	      || inst.operands[0].reg == inst.operands[1].reg + 1
	      || inst.operands[0].reg == inst.operands[3].reg,
	      BAD_OVERLAP);

  inst.instruction |= inst.operands[0].reg << 12;
  inst.instruction |= inst.operands[1].reg;
  inst.instruction |= inst.operands[3].reg << 16;
}