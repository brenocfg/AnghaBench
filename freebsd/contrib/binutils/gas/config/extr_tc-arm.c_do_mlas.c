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
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arm_ext_v6 ; 
 int /*<<< orphan*/  as_tsktsk (int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 int /*<<< orphan*/  selected_cpu ; 

__attribute__((used)) static void
do_mlas (void)
{
  /* This restriction does not apply to mls (nor to mla in v6 or later).  */
  if (inst.operands[0].reg == inst.operands[1].reg
      && !ARM_CPU_HAS_FEATURE (selected_cpu, arm_ext_v6)
      && !(inst.instruction & 0x00400000))
    as_tsktsk (_("Rd and Rm should be different in mla"));

  inst.instruction |= inst.operands[0].reg << 16;
  inst.instruction |= inst.operands[1].reg;
  inst.instruction |= inst.operands[2].reg << 8;
  inst.instruction |= inst.operands[3].reg << 12;
}