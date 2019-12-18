#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ INSN_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  cselib_finish () ; 
 int /*<<< orphan*/  cselib_init (int) ; 
 int /*<<< orphan*/  cselib_process_insn (scalar_t__) ; 
 int /*<<< orphan*/  end_alias_analysis () ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_alias_analysis () ; 
 int /*<<< orphan*/  reload_cse_simplify (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
reload_cse_regs_1 (rtx first)
{
  rtx insn;
  rtx testreg = gen_rtx_REG (VOIDmode, -1);

  cselib_init (true);
  init_alias_analysis ();

  for (insn = first; insn; insn = NEXT_INSN (insn))
    {
      if (INSN_P (insn))
	reload_cse_simplify (insn, testreg);

      cselib_process_insn (insn);
    }

  /* Clean up.  */
  end_alias_analysis ();
  cselib_finish ();
}