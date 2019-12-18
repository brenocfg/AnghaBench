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
typedef  int hashval_t ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  CONST 133 
#define  CONST_DOUBLE 132 
#define  CONST_INT 131 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 130 
#define  REG 129 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  df ; 
 struct df_ref* df_find_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int hash_rtx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int) ; 
 struct invariant* invariant_for_use (struct df_ref*) ; 

__attribute__((used)) static hashval_t
hash_invariant_expr_1 (rtx insn, rtx x)
{
  enum rtx_code code = GET_CODE (x);
  int i, j;
  const char *fmt;
  hashval_t val = code;
  int do_not_record_p;
  struct df_ref *use;
  struct invariant *inv;

  switch (code)
    {
    case CONST_INT:
    case CONST_DOUBLE:
    case SYMBOL_REF:
    case CONST:
    case LABEL_REF:
      return hash_rtx (x, GET_MODE (x), &do_not_record_p, NULL, false);

    case REG:
      use = df_find_use (df, insn, x);
      if (!use)
	return hash_rtx (x, GET_MODE (x), &do_not_record_p, NULL, false);
      inv = invariant_for_use (use);
      if (!inv)
	return hash_rtx (x, GET_MODE (x), &do_not_record_p, NULL, false);

      gcc_assert (inv->eqto != ~0u);
      return inv->eqto;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	val ^= hash_invariant_expr_1 (insn, XEXP (x, i));
      else if (fmt[i] == 'E')
	{
	  for (j = 0; j < XVECLEN (x, i); j++)
	    val ^= hash_invariant_expr_1 (insn, XVECEXP (x, i, j));
	}
      else if (fmt[i] == 'i' || fmt[i] == 'n')
	val ^= XINT (x, i);
    }

  return val;
}