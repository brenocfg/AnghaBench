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
struct TYPE_4__ {int instruction; scalar_t__ cond; TYPE_1__* operands; } ;
struct TYPE_3__ {int reg; scalar_t__ isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_COND ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_PCREL_BLX ; 
 int /*<<< orphan*/  BFD_RELOC_ARM_PCREL_CALL ; 
 scalar_t__ COND_ALWAYS ; 
 scalar_t__ EF_ARM_EABI_VER4 ; 
 scalar_t__ EF_ARM_EABI_VERSION (int /*<<< orphan*/ ) ; 
 int REG_PC ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_tsktsk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_branch (int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 
 int /*<<< orphan*/  meabi_flags ; 

__attribute__((used)) static void
do_blx (void)
{
  if (inst.operands[0].isreg)
    {
      /* Arg is a register; the opcode provided by insns[] is correct.
	 It is not illegal to do "blx pc", just useless.  */
      if (inst.operands[0].reg == REG_PC)
	as_tsktsk (_("use of r15 in blx in ARM mode is not really useful"));

      inst.instruction |= inst.operands[0].reg;
    }
  else
    {
      /* Arg is an address; this instruction cannot be executed
	 conditionally, and the opcode must be adjusted.  */
      constraint (inst.cond != COND_ALWAYS, BAD_COND);
      inst.instruction = 0xfa000000;
#ifdef OBJ_ELF
      if (EF_ARM_EABI_VERSION (meabi_flags) >= EF_ARM_EABI_VER4)
	encode_branch (BFD_RELOC_ARM_PCREL_CALL);
      else
#endif
	encode_branch (BFD_RELOC_ARM_PCREL_BLX);
    }
}