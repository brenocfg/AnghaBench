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
struct TYPE_3__ {int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_BRANCH ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int current_it_mask ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_bx (void)
{
  constraint (current_it_mask && current_it_mask != 0x10, BAD_BRANCH);
  inst.instruction |= inst.operands[0].reg << 3;
  /* ??? FIXME: Should add a hacky reloc here if reg is REG_PC.	 The reloc
     should cause the alignment to be checked once it is known.	 This is
     because BX PC only works if the instruction is word aligned.  */
}