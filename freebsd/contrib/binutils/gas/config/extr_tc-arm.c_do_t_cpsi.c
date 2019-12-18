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
struct TYPE_4__ {int size_req; int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int imm; scalar_t__ present; } ;

/* Variables and functions */
 scalar_t__ ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BAD_NOT_IT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arm_ext_v1 ; 
 int /*<<< orphan*/  arm_ext_v6_notm ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_variant ; 
 int current_it_mask ; 
 TYPE_2__ inst ; 
 scalar_t__ unified_syntax ; 

__attribute__((used)) static void
do_t_cpsi (void)
{
  constraint (current_it_mask, BAD_NOT_IT);
  if (unified_syntax
      && (inst.operands[1].present || inst.size_req == 4)
      && ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v6_notm))
    {
      unsigned int imod = (inst.instruction & 0x0030) >> 4;
      inst.instruction = 0xf3af8000;
      inst.instruction |= imod << 9;
      inst.instruction |= inst.operands[0].imm << 5;
      if (inst.operands[1].present)
	inst.instruction |= 0x100 | inst.operands[1].imm;
    }
  else
    {
      constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v1)
		  && (inst.operands[0].imm & 4),
		  _("selected processor does not support 'A' form "
		    "of this instruction"));
      constraint (inst.operands[1].present || inst.size_req == 4,
		  _("Thumb does not support the 2-argument "
		    "form of this instruction"));
      inst.instruction |= inst.operands[0].imm;
    }
}