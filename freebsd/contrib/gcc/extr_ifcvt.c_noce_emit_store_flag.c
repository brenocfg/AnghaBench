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
struct noce_if_info {int /*<<< orphan*/  jump; int /*<<< orphan*/  cond_earliest; int /*<<< orphan*/  cond; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int GEU ; 
 int GTU ; 
 int LEU ; 
 int LTU ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  SCALAR_INT_MODE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 int STORE_FLAG_VALUE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_store_flag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  general_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  pc_set (int /*<<< orphan*/ ) ; 
 scalar_t__ recog_memoized (int /*<<< orphan*/ ) ; 
 int reversed_comparison_code (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
noce_emit_store_flag (struct noce_if_info *if_info, rtx x, int reversep,
		      int normalize)
{
  rtx cond = if_info->cond;
  int cond_complex;
  enum rtx_code code;

  cond_complex = (! general_operand (XEXP (cond, 0), VOIDmode)
		  || ! general_operand (XEXP (cond, 1), VOIDmode));

  /* If earliest == jump, or when the condition is complex, try to
     build the store_flag insn directly.  */

  if (cond_complex)
    cond = XEXP (SET_SRC (pc_set (if_info->jump)), 0);

  if (reversep)
    code = reversed_comparison_code (cond, if_info->jump);
  else
    code = GET_CODE (cond);

  if ((if_info->cond_earliest == if_info->jump || cond_complex)
      && (normalize == 0 || STORE_FLAG_VALUE == normalize))
    {
      rtx tmp;

      tmp = gen_rtx_fmt_ee (code, GET_MODE (x), XEXP (cond, 0),
			    XEXP (cond, 1));
      tmp = gen_rtx_SET (VOIDmode, x, tmp);

      start_sequence ();
      tmp = emit_insn (tmp);

      if (recog_memoized (tmp) >= 0)
	{
	  tmp = get_insns ();
	  end_sequence ();
	  emit_insn (tmp);

	  if_info->cond_earliest = if_info->jump;

	  return x;
	}

      end_sequence ();
    }

  /* Don't even try if the comparison operands or the mode of X are weird.  */
  if (cond_complex || !SCALAR_INT_MODE_P (GET_MODE (x)))
    return NULL_RTX;

  return emit_store_flag (x, code, XEXP (cond, 0),
			  XEXP (cond, 1), VOIDmode,
			  (code == LTU || code == LEU
			   || code == GEU || code == GTU), normalize);
}