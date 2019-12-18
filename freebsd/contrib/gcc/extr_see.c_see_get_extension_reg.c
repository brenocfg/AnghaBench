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

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/ * PATTERN (int /*<<< orphan*/ *) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_DEST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SET_SRC (int /*<<< orphan*/ *) ; 
 scalar_t__ SIGN_EXTEND ; 
 int /*<<< orphan*/ * SUBREG_REG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTEND ; 
 int /*<<< orphan*/ * single_set (int /*<<< orphan*/ *) ; 

__attribute__((used)) static rtx
see_get_extension_reg (rtx extension, bool return_dest_reg)
{
  rtx set, rhs, lhs;
  rtx reg1 = NULL;
  rtx reg2 = NULL;

  /* Parallel pattern for extension not supported for the moment.  */
  if (GET_CODE (PATTERN (extension)) == PARALLEL)
    return NULL;

  set = single_set (extension);
  if (!set)
    return NULL;
  lhs = SET_DEST (set);
  rhs = SET_SRC (set);

  if (REG_P (lhs))
    reg1 = lhs;
  else if (REG_P (SUBREG_REG (lhs)))
    reg1 = SUBREG_REG (lhs);
  else
    return NULL;

  if (GET_CODE (rhs) != SIGN_EXTEND && GET_CODE (rhs) != ZERO_EXTEND)
    return NULL;

  rhs = XEXP (rhs, 0);
  if (REG_P (rhs))
    reg2 = rhs;
  else if (REG_P (SUBREG_REG (rhs)))
    reg2 = SUBREG_REG (rhs);
  else
    return NULL;

  if (return_dest_reg)
    return reg1;
  return reg2;
}