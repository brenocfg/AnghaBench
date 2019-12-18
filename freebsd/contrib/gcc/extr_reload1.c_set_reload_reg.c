#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {scalar_t__ mode; scalar_t__ in; scalar_t__ out; scalar_t__ reg_rtx; int /*<<< orphan*/  when_needed; int /*<<< orphan*/  opnum; } ;

/* Variables and functions */
 int GET_MODE (scalar_t__) ; 
 scalar_t__ HARD_REGNO_MODE_OK (int,int) ; 
 int VOIDmode ; 
 scalar_t__ gen_rtx_REG (scalar_t__,int /*<<< orphan*/ ) ; 
 int last_spill_reg ; 
 int /*<<< orphan*/  mark_reload_reg_in_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * reload_spill_index ; 
 TYPE_1__* rld ; 
 scalar_t__* spill_reg_rtx ; 
 int /*<<< orphan*/ * spill_regs ; 
 int true_regnum (scalar_t__) ; 

__attribute__((used)) static int
set_reload_reg (int i, int r)
{
  int regno;
  rtx reg = spill_reg_rtx[i];

  if (reg == 0 || GET_MODE (reg) != rld[r].mode)
    spill_reg_rtx[i] = reg
      = gen_rtx_REG (rld[r].mode, spill_regs[i]);

  regno = true_regnum (reg);

  /* Detect when the reload reg can't hold the reload mode.
     This used to be one `if', but Sequent compiler can't handle that.  */
  if (HARD_REGNO_MODE_OK (regno, rld[r].mode))
    {
      enum machine_mode test_mode = VOIDmode;
      if (rld[r].in)
	test_mode = GET_MODE (rld[r].in);
      /* If rld[r].in has VOIDmode, it means we will load it
	 in whatever mode the reload reg has: to wit, rld[r].mode.
	 We have already tested that for validity.  */
      /* Aside from that, we need to test that the expressions
	 to reload from or into have modes which are valid for this
	 reload register.  Otherwise the reload insns would be invalid.  */
      if (! (rld[r].in != 0 && test_mode != VOIDmode
	     && ! HARD_REGNO_MODE_OK (regno, test_mode)))
	if (! (rld[r].out != 0
	       && ! HARD_REGNO_MODE_OK (regno, GET_MODE (rld[r].out))))
	  {
	    /* The reg is OK.  */
	    last_spill_reg = i;

	    /* Mark as in use for this insn the reload regs we use
	       for this.  */
	    mark_reload_reg_in_use (spill_regs[i], rld[r].opnum,
				    rld[r].when_needed, rld[r].mode);

	    rld[r].reg_rtx = reg;
	    reload_spill_index[r] = spill_regs[i];
	    return 1;
	  }
    }
  return 0;
}