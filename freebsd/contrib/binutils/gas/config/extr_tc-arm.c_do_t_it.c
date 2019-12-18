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
struct TYPE_3__ {unsigned int imm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_NOT_IT ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 unsigned int current_cc ; 
 int current_it_mask ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_it (void)
{
  unsigned int cond = inst.operands[0].imm;

  constraint (current_it_mask, BAD_NOT_IT);
  current_it_mask = (inst.instruction & 0xf) | 0x10;
  current_cc = cond;

  /* If the condition is a negative condition, invert the mask.  */
  if ((cond & 0x1) == 0x0)
    {
      unsigned int mask = inst.instruction & 0x000f;

      if ((mask & 0x7) == 0)
	/* no conversion needed */;
      else if ((mask & 0x3) == 0)
	mask ^= 0x8;
      else if ((mask & 0x1) == 0)
	mask ^= 0xC;
      else
	mask ^= 0xE;

      inst.instruction &= 0xfff0;
      inst.instruction |= mask;
    }

  inst.instruction |= cond << 4;
}