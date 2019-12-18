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
struct TYPE_3__ {int imm; int reg; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PSR_f ; 
 int SPSR_BIT ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arm_ext_v1 ; 
 int /*<<< orphan*/  arm_ext_v7m ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_variant ; 
 scalar_t__ do_vfp_nsyn_msr () ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_msr (void)
{
  int flags;

  if (do_vfp_nsyn_msr () == SUCCESS)
    return;

  constraint (!inst.operands[1].isreg,
	      _("Thumb encoding does not support an immediate here"));
  flags = inst.operands[0].imm;
  if (flags & ~0xff)
    {
      constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v1),
		  _("selected processor does not support "
		    "requested special purpose register"));
    }
  else
    {
      constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v7m),
		  _("selected processor does not support "
		    "requested special purpose register"));
      flags |= PSR_f;
    }
  inst.instruction |= (flags & SPSR_BIT) >> 2;
  inst.instruction |= (flags & ~SPSR_BIT) >> 8;
  inst.instruction |= (flags & 0xff);
  inst.instruction |= inst.operands[1].reg << 16;
}