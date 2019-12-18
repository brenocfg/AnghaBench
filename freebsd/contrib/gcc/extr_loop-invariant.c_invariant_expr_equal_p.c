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
struct invariant {unsigned int eqto; } ;
struct df_ref {int dummy; } ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  CONST 133 
#define  CONST_DOUBLE 132 
#define  CONST_INT 131 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 130 
#define  REG 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  df ; 
 struct df_ref* df_find_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct invariant* invariant_for_use (struct df_ref*) ; 
 int rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
invariant_expr_equal_p (rtx insn1, rtx e1, rtx insn2, rtx e2)
{
  enum rtx_code code = GET_CODE (e1);
  int i, j;
  const char *fmt;
  struct df_ref *use1, *use2;
  struct invariant *inv1 = NULL, *inv2 = NULL;
  rtx sub1, sub2;

  /* If mode of only one of the operands is VOIDmode, it is not equivalent to
     the other one.  If both are VOIDmode, we rely on the caller of this
     function to verify that their modes are the same.  */
  if (code != GET_CODE (e2) || GET_MODE (e1) != GET_MODE (e2))
    return false;

  switch (code)
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case SYMBOL_REF:
    case CONST:
    case LABEL_REF:
      return rtx_equal_p (e1, e2);

    case REG:
      use1 = df_find_use (df, insn1, e1);
      use2 = df_find_use (df, insn2, e2);
      if (use1)
	inv1 = invariant_for_use (use1);
      if (use2)
	inv2 = invariant_for_use (use2);

      if (!inv1 && !inv2)
	return rtx_equal_p (e1, e2);

      if (!inv1 || !inv2)
	return false;

      gcc_assert (inv1->eqto != ~0u);
      gcc_assert (inv2->eqto != ~0u);
      return inv1->eqto == inv2->eqto;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  sub1 = XEXP (e1, i);
	  sub2 = XEXP (e2, i);

	  if (!invariant_expr_equal_p (insn1, sub1, insn2, sub2))
	    return false;
	}

      else if (fmt[i] == 'E')
	{
	  if (XVECLEN (e1, i) != XVECLEN (e2, i))
	    return false;

	  for (j = 0; j < XVECLEN (e1, i); j++)
	    {
	      sub1 = XVECEXP (e1, i, j);
	      sub2 = XVECEXP (e2, i, j);

	      if (!invariant_expr_equal_p (insn1, sub1, insn2, sub2))
		return false;
	    }
	}
      else if (fmt[i] == 'i' || fmt[i] == 'n')
	{
	  if (XINT (e1, i) != XINT (e2, i))
	    return false;
	}
      /* Unhandled type of subexpression, we fail conservatively.  */
      else
	return false;
    }

  return true;
}