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
struct qty_table_elem {scalar_t__ mode; scalar_t__ const_rtx; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO_QTY_VALID_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int REG_QTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 struct qty_table_elem* qty_table ; 
 int rtx_varies_p (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
cse_rtx_varies_p (rtx x, int from_alias)
{
  /* We need not check for X and the equivalence class being of the same
     mode because if X is equivalent to a constant in some mode, it
     doesn't vary in any mode.  */

  if (REG_P (x)
      && REGNO_QTY_VALID_P (REGNO (x)))
    {
      int x_q = REG_QTY (REGNO (x));
      struct qty_table_elem *x_ent = &qty_table[x_q];

      if (GET_MODE (x) == x_ent->mode
	  && x_ent->const_rtx != NULL_RTX)
	return 0;
    }

  if (GET_CODE (x) == PLUS
      && GET_CODE (XEXP (x, 1)) == CONST_INT
      && REG_P (XEXP (x, 0))
      && REGNO_QTY_VALID_P (REGNO (XEXP (x, 0))))
    {
      int x0_q = REG_QTY (REGNO (XEXP (x, 0)));
      struct qty_table_elem *x0_ent = &qty_table[x0_q];

      if ((GET_MODE (XEXP (x, 0)) == x0_ent->mode)
	  && x0_ent->const_rtx != NULL_RTX)
	return 0;
    }

  /* This can happen as the result of virtual register instantiation, if
     the initial constant is too large to be a valid address.  This gives
     us a three instruction sequence, load large offset into a register,
     load fp minus a constant into a register, then a MEM which is the
     sum of the two `constant' registers.  */
  if (GET_CODE (x) == PLUS
      && REG_P (XEXP (x, 0))
      && REG_P (XEXP (x, 1))
      && REGNO_QTY_VALID_P (REGNO (XEXP (x, 0)))
      && REGNO_QTY_VALID_P (REGNO (XEXP (x, 1))))
    {
      int x0_q = REG_QTY (REGNO (XEXP (x, 0)));
      int x1_q = REG_QTY (REGNO (XEXP (x, 1)));
      struct qty_table_elem *x0_ent = &qty_table[x0_q];
      struct qty_table_elem *x1_ent = &qty_table[x1_q];

      if ((GET_MODE (XEXP (x, 0)) == x0_ent->mode)
	  && x0_ent->const_rtx != NULL_RTX
	  && (GET_MODE (XEXP (x, 1)) == x1_ent->mode)
	  && x1_ent->const_rtx != NULL_RTX)
	return 0;
    }

  return rtx_varies_p (x, from_alias);
}