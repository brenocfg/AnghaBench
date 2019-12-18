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
struct noce_if_info {scalar_t__ cond_earliest; scalar_t__ jump; int /*<<< orphan*/  cond; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GEU ; 
 int GTU ; 
 int LEU ; 
 int LTU ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_conditional_move (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  gen_rtx_IF_THEN_ELSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
noce_emit_cmove (struct noce_if_info *if_info, rtx x, enum rtx_code code,
		 rtx cmp_a, rtx cmp_b, rtx vfalse, rtx vtrue)
{
  /* If earliest == jump, try to build the cmove insn directly.
     This is helpful when combine has created some complex condition
     (like for alpha's cmovlbs) that we can't hope to regenerate
     through the normal interface.  */

  if (if_info->cond_earliest == if_info->jump)
    {
      rtx tmp;

      tmp = gen_rtx_fmt_ee (code, GET_MODE (if_info->cond), cmp_a, cmp_b);
      tmp = gen_rtx_IF_THEN_ELSE (GET_MODE (x), tmp, vtrue, vfalse);
      tmp = gen_rtx_SET (VOIDmode, x, tmp);

      start_sequence ();
      tmp = emit_insn (tmp);

      if (recog_memoized (tmp) >= 0)
	{
	  tmp = get_insns ();
	  end_sequence ();
	  emit_insn (tmp);

	  return x;
	}

      end_sequence ();
    }

  /* Don't even try if the comparison operands are weird.  */
  if (! general_operand (cmp_a, GET_MODE (cmp_a))
      || ! general_operand (cmp_b, GET_MODE (cmp_b)))
    return NULL_RTX;

#if HAVE_conditional_move
  return emit_conditional_move (x, code, cmp_a, cmp_b, VOIDmode,
				vtrue, vfalse, GET_MODE (x),
			        (code == LTU || code == GEU
				 || code == LEU || code == GTU));
#else
  /* We'll never get here, as noce_process_if_block doesn't call the
     functions involved.  Ifdef code, however, should be discouraged
     because it leads to typos in the code not selected.  However,
     emit_conditional_move won't exist either.  */
  return NULL_RTX;
#endif
}