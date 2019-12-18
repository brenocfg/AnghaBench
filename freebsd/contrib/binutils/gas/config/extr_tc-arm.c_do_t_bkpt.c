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
struct TYPE_4__ {scalar_t__ cond; int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; scalar_t__ present; } ;

/* Variables and functions */
 scalar_t__ COND_ALWAYS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_bkpt (void)
{
  constraint (inst.cond != COND_ALWAYS,
	      _("instruction is always unconditional"));
  if (inst.operands[0].present)
    {
      constraint (inst.operands[0].imm > 255,
		  _("immediate value out of range"));
      inst.instruction |= inst.operands[0].imm;
    }
}