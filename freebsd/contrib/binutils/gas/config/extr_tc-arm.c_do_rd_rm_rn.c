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
struct TYPE_3__ {unsigned int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_rd_rm_rn (void)
{
  unsigned Rn = inst.operands[2].reg;
  /* Enforce restrictions on SWP instruction.  */
  if ((inst.instruction & 0x0fbfffff) == 0x01000090)
    constraint (Rn == inst.operands[0].reg || Rn == inst.operands[1].reg,
		_("Rn must not overlap other operands"));
  inst.instruction |= inst.operands[0].reg << 12;
  inst.instruction |= inst.operands[1].reg;
  inst.instruction |= Rn << 16;
}