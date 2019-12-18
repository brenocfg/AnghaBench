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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ *) ; 
 int SIGN_EXTEND ; 
 int /*<<< orphan*/  VOIDmode ; 
 int ZERO_EXTEND ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/ * gen_lowpart_SUBREG (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_SIGN_EXTEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_rtx_ZERO_EXTEND (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_insns () ; 
 scalar_t__ insn_invalid_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
see_gen_normalized_extension (rtx reg, enum rtx_code extension_code,
   			      enum machine_mode mode)
{
  rtx subreg, insn;
  rtx extension = NULL;

  if (!reg
      || !REG_P (reg)
      || (extension_code != SIGN_EXTEND && extension_code != ZERO_EXTEND))
    return NULL;

  subreg = gen_lowpart_SUBREG (mode, reg);
  if (extension_code == SIGN_EXTEND)
    extension = gen_rtx_SIGN_EXTEND (GET_MODE (reg), subreg);
  else
    extension = gen_rtx_ZERO_EXTEND (GET_MODE (reg), subreg);

  start_sequence ();
  emit_insn (gen_rtx_SET (VOIDmode, reg, extension));
  insn = get_insns ();
  end_sequence ();

  if (insn_invalid_p (insn))
    /* Recognition failed, this is very bad for this optimization.
       Abort the optimization.  */
    return NULL;
  return insn;
}