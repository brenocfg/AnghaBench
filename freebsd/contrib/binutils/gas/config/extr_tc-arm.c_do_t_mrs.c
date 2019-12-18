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
struct TYPE_3__ {int imm; int reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_CPU_HAS_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PSR_c ; 
 int PSR_f ; 
 int PSR_s ; 
 int PSR_x ; 
 int SPSR_BIT ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  arm_ext_v1 ; 
 int /*<<< orphan*/  arm_ext_v7m ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_variant ; 
 scalar_t__ do_vfp_nsyn_mrs () ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_mrs (void)
{
  int flags;

  if (do_vfp_nsyn_mrs () == SUCCESS)
    return;

  flags = inst.operands[1].imm & (PSR_c|PSR_x|PSR_s|PSR_f|SPSR_BIT);
  if (flags == 0)
    {
      constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v7m),
		  _("selected processor does not support "
		    "requested special purpose register"));
    }
  else
    {
      constraint (!ARM_CPU_HAS_FEATURE (cpu_variant, arm_ext_v1),
		  _("selected processor does not support "
		    "requested special purpose register %x"));
      /* mrs only accepts CPSR/SPSR/CPSR_all/SPSR_all.  */
      constraint ((flags & ~SPSR_BIT) != (PSR_c|PSR_f),
		  _("'CPSR' or 'SPSR' expected"));
    }
    
  inst.instruction |= inst.operands[0].reg << 8;
  inst.instruction |= (flags & SPSR_BIT) >> 2;
  inst.instruction |= inst.operands[1].imm & 0xff;
}