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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ SUBREG ; 
 int SUBREG_PROMOTED_UNSIGNED_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG_PROMOTED_VAR_P (int /*<<< orphan*/ ) ; 
 scalar_t__ UNITS_PER_WORD ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  convert_modes (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SUBREG (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
widen_operand (rtx op, enum machine_mode mode, enum machine_mode oldmode,
	       int unsignedp, int no_extend)
{
  rtx result;

  /* If we don't have to extend and this is a constant, return it.  */
  if (no_extend && GET_MODE (op) == VOIDmode)
    return op;

  /* If we must extend do so.  If OP is a SUBREG for a promoted object, also
     extend since it will be more efficient to do so unless the signedness of
     a promoted object differs from our extension.  */
  if (! no_extend
      || (GET_CODE (op) == SUBREG && SUBREG_PROMOTED_VAR_P (op)
	  && SUBREG_PROMOTED_UNSIGNED_P (op) == unsignedp))
    return convert_modes (mode, oldmode, op, unsignedp);

  /* If MODE is no wider than a single word, we return a paradoxical
     SUBREG.  */
  if (GET_MODE_SIZE (mode) <= UNITS_PER_WORD)
    return gen_rtx_SUBREG (mode, force_reg (GET_MODE (op), op), 0);

  /* Otherwise, get an object of MODE, clobber it, and set the low-order
     part to OP.  */

  result = gen_reg_rtx (mode);
  emit_insn (gen_rtx_CLOBBER (VOIDmode, result));
  emit_move_insn (gen_lowpart (GET_MODE (op), result), op);
  return result;
}