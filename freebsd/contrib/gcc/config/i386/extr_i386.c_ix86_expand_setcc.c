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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 scalar_t__ DImode ; 
 int /*<<< orphan*/  GET_CODE (scalar_t__) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  PUT_CODE (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_MODE (scalar_t__,scalar_t__) ; 
 scalar_t__ QImode ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_andqi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_iorqi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  get_last_insn () ; 
 scalar_t__ ix86_compare_op0 ; 
 scalar_t__ ix86_compare_op1 ; 
 scalar_t__ ix86_expand_compare (int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  reverse_condition_maybe_unordered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unique_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ simplify_gen_relational (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int
ix86_expand_setcc (enum rtx_code code, rtx dest)
{
  rtx ret, tmp, tmpreg, equiv;
  rtx second_test, bypass_test;

  if (GET_MODE (ix86_compare_op0) == (TARGET_64BIT ? TImode : DImode))
    return 0; /* FAIL */

  gcc_assert (GET_MODE (dest) == QImode);

  ret = ix86_expand_compare (code, &second_test, &bypass_test);
  PUT_MODE (ret, QImode);

  tmp = dest;
  tmpreg = dest;

  emit_insn (gen_rtx_SET (VOIDmode, tmp, ret));
  if (bypass_test || second_test)
    {
      rtx test = second_test;
      int bypass = 0;
      rtx tmp2 = gen_reg_rtx (QImode);
      if (bypass_test)
	{
	  gcc_assert (!second_test);
	  test = bypass_test;
	  bypass = 1;
	  PUT_CODE (test, reverse_condition_maybe_unordered (GET_CODE (test)));
	}
      PUT_MODE (test, QImode);
      emit_insn (gen_rtx_SET (VOIDmode, tmp2, test));

      if (bypass)
	emit_insn (gen_andqi3 (tmp, tmpreg, tmp2));
      else
	emit_insn (gen_iorqi3 (tmp, tmpreg, tmp2));
    }

  /* Attach a REG_EQUAL note describing the comparison result.  */
  if (ix86_compare_op0 && ix86_compare_op1)
    {
      equiv = simplify_gen_relational (code, QImode,
				       GET_MODE (ix86_compare_op0),
				       ix86_compare_op0, ix86_compare_op1);
      set_unique_reg_note (get_last_insn (), REG_EQUAL, equiv);
    }

  return 1; /* DONE */
}