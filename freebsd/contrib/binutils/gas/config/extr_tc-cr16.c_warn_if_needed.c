#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nargs; TYPE_1__* arg; } ;
typedef  TYPE_2__ ins ;
struct TYPE_7__ {int flags; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ r; unsigned int constant; } ;

/* Variables and functions */
 scalar_t__ IS_INSN_MNEMONIC (char*) ; 
 scalar_t__ IS_INSN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_STOR_INS_INC ; 
 int NO_RPTR ; 
 int NO_SP ; 
 scalar_t__ RA ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ arg_r ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int getreg_image (int) ; 
 int ins_parse ; 
 TYPE_4__* instruction ; 
 scalar_t__ ra ; 
 int sp ; 

__attribute__((used)) static void
warn_if_needed (ins *insn)
{
  /* If the post-increment address mode is used and the load/store
     source register is the same as rbase, the result of the
     instruction is undefined.  */
  if (IS_INSN_TYPE (LD_STOR_INS_INC))
    {
      /* Enough to verify that one of the arguments is a simple reg.  */
      if ((insn->arg[0].type == arg_r) || (insn->arg[1].type == arg_r))
        if (insn->arg[0].r == insn->arg[1].r)
          as_bad (_("Same src/dest register is used (`r%d'), result is undefined"), insn->arg[0].r);
    }

  if (IS_INSN_MNEMONIC ("pop")
      || IS_INSN_MNEMONIC ("push")
      || IS_INSN_MNEMONIC ("popret"))
    {
      unsigned int count = insn->arg[0].constant, reg_val;

      /* Check if count operand caused to save/retrive the RA twice
	 to generate warning message.  */
     if (insn->nargs > 2)
       {
         reg_val = getreg_image (insn->arg[1].r);

         if (   ((reg_val == 9) &&  (count > 7))
	     || ((reg_val == 10) && (count > 6))
	     || ((reg_val == 11) && (count > 5))
	     || ((reg_val == 12) && (count > 4))
	     || ((reg_val == 13) && (count > 2))
	     || ((reg_val == 14) && (count > 0)))
           as_warn (_("RA register is saved twice."));

         /* Check if the third operand is "RA" or "ra" */
         if (!(((insn->arg[2].r) == ra) || ((insn->arg[2].r) == RA)))
           as_bad (_("`%s' Illegal use of registers."), ins_parse);
       }

      if (insn->nargs > 1)
       {
         reg_val = getreg_image (insn->arg[1].r);

         /* If register is a register pair ie r12/r13/r14 in operand1, then
            the count constant should be validated.  */
         if (((reg_val == 11) && (count > 7))
	     || ((reg_val == 12) && (count > 6))
	     || ((reg_val == 13) && (count > 4))
	     || ((reg_val == 14) && (count > 2))
	     || ((reg_val == 15) && (count > 0)))
           as_bad (_("`%s' Illegal count-register combination."), ins_parse);
       }
     else
       {
         /* Check if the operand is "RA" or "ra" */
         if (!(((insn->arg[0].r) == ra) || ((insn->arg[0].r) == RA)))
           as_bad (_("`%s' Illegal use of register."), ins_parse);
       }
    }

  /* Some instruction assume the stack pointer as rptr operand.
     Issue an error when the register to be loaded is also SP.  */
  if (instruction->flags & NO_SP)
    {
      if (getreg_image (insn->arg[1].r) == getreg_image (sp))
        as_bad (_("`%s' has undefined result"), ins_parse);
    }

  /* If the rptr register is specified as one of the registers to be loaded,
     the final contents of rptr are undefined. Thus, we issue an error.  */
  if (instruction->flags & NO_RPTR)
    {
      if ((1 << getreg_image (insn->arg[0].r)) & insn->arg[1].constant)
        as_bad (_("Same src/dest register is used (`r%d'),result is undefined"),
                  getreg_image (insn->arg[0].r));
    }
}