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
struct table_elt {scalar_t__ exp; scalar_t__ is_const; struct table_elt* next_same_value; struct table_elt* first_same_value; } ;
struct qty_table_elem {scalar_t__ const_rtx; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 scalar_t__ REGNO_QTY_VALID_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int REG_QTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_HASH (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_rtx (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_lowpart (int /*<<< orphan*/ ,scalar_t__) ; 
 struct table_elt* lookup (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qty_table_elem* qty_table ; 

__attribute__((used)) static rtx
equiv_constant (rtx x)
{
  if (REG_P (x)
      && REGNO_QTY_VALID_P (REGNO (x)))
    {
      int x_q = REG_QTY (REGNO (x));
      struct qty_table_elem *x_ent = &qty_table[x_q];

      if (x_ent->const_rtx)
	x = gen_lowpart (GET_MODE (x), x_ent->const_rtx);
    }

  if (x == 0 || CONSTANT_P (x))
    return x;

  /* If X is a MEM, try to fold it outside the context of any insn to see if
     it might be equivalent to a constant.  That handles the case where it
     is a constant-pool reference.  Then try to look it up in the hash table
     in case it is something whose value we have seen before.  */

  if (MEM_P (x))
    {
      struct table_elt *elt;

      x = fold_rtx (x, NULL_RTX);
      if (CONSTANT_P (x))
	return x;

      elt = lookup (x, SAFE_HASH (x, GET_MODE (x)), GET_MODE (x));
      if (elt == 0)
	return 0;

      for (elt = elt->first_same_value; elt; elt = elt->next_same_value)
	if (elt->is_const && CONSTANT_P (elt->exp))
	  return elt->exp;
    }

  return 0;
}