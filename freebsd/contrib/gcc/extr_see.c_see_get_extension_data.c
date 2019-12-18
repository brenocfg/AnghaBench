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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_P (int /*<<< orphan*/ ) ; 
 int NOT_RELEVANT ; 
 scalar_t__ PARALLEL ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
 scalar_t__ SIGN_EXTEND ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int UNKNOWN ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ZERO_EXTEND ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum rtx_code
see_get_extension_data (rtx extension, enum machine_mode *source_mode)
{
  rtx rhs, lhs, set;

  if (!extension || !INSN_P (extension))
    return UNKNOWN;

  /* Parallel pattern for extension not supported for the moment.  */
  if (GET_CODE (PATTERN (extension)) == PARALLEL)
    return NOT_RELEVANT;

  set = single_set (extension);
  if (!set)
    return NOT_RELEVANT;
  rhs = SET_SRC (set);
  lhs = SET_DEST (set);

  /* Don't handle extensions to something other then register or
     subregister.  */
  if (!REG_P (lhs) && !SUBREG_REG (lhs))
    return UNKNOWN;

  if (GET_CODE (rhs) != SIGN_EXTEND && GET_CODE (rhs) != ZERO_EXTEND)
    return UNKNOWN;

  if (!REG_P (XEXP (rhs, 0))
      && !(GET_CODE (XEXP (rhs, 0)) == SUBREG
	   && REG_P (SUBREG_REG (XEXP (rhs, 0)))))
    return UNKNOWN;

  *source_mode = GET_MODE (XEXP (rhs, 0));

  if (GET_CODE (rhs) == SIGN_EXTEND)
    return SIGN_EXTEND;
  return ZERO_EXTEND;
}