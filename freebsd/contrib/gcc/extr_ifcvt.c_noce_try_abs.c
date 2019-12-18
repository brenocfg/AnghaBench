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
struct noce_if_info {scalar_t__ a; scalar_t__ b; scalar_t__ x; scalar_t__ cond_earliest; scalar_t__ cond; int /*<<< orphan*/  insn_a; int /*<<< orphan*/  jump; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CONST0_RTX (int /*<<< orphan*/ ) ; 
 scalar_t__ CONSTANT_POOL_ADDRESS_P (scalar_t__) ; 
 int FALSE ; 
#define  GE 135 
 int GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
#define  GT 134 
 int /*<<< orphan*/  INSN_LOCATOR (int /*<<< orphan*/ ) ; 
#define  LE 133 
#define  LT 132 
 scalar_t__ MEM_P (scalar_t__) ; 
 int NEG ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
 int SYMBOL_REF ; 
 int TRUE ; 
#define  UNGE 131 
#define  UNGT 130 
#define  UNLE 129 
#define  UNLT 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ const1_rtx ; 
 scalar_t__ constm1_rtx ; 
 int /*<<< orphan*/  emit_insn_before_setloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ end_ifcvt_sequence (struct noce_if_info*) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_abs_nojump (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int) ; 
 scalar_t__ expand_simple_unop (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_equal_equiv_note (scalar_t__) ; 
 scalar_t__ get_pool_constant (scalar_t__) ; 
 scalar_t__ no_new_pseudos ; 
 int /*<<< orphan*/  noce_emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ noce_get_alt_condition (struct noce_if_info*,scalar_t__,scalar_t__*) ; 
 scalar_t__ prev_nonnote_insn (scalar_t__) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static int
noce_try_abs (struct noce_if_info *if_info)
{
  rtx cond, earliest, target, seq, a, b, c;
  int negate;

  /* ??? Can't guarantee that expand_binop won't create pseudos.  */
  if (no_new_pseudos)
    return FALSE;

  /* Recognize A and B as constituting an ABS or NABS.  The canonical
     form is a branch around the negation, taken when the object is the
     first operand of a comparison against 0 that evaluates to true.  */
  a = if_info->a;
  b = if_info->b;
  if (GET_CODE (a) == NEG && rtx_equal_p (XEXP (a, 0), b))
    negate = 0;
  else if (GET_CODE (b) == NEG && rtx_equal_p (XEXP (b, 0), a))
    {
      c = a; a = b; b = c;
      negate = 1;
    }
  else
    return FALSE;

  cond = noce_get_alt_condition (if_info, b, &earliest);
  if (!cond)
    return FALSE;

  /* Verify the condition is of the form we expect.  */
  if (rtx_equal_p (XEXP (cond, 0), b))
    c = XEXP (cond, 1);
  else if (rtx_equal_p (XEXP (cond, 1), b))
    {
      c = XEXP (cond, 0);
      negate = !negate;
    }
  else
    return FALSE;

  /* Verify that C is zero.  Search one step backward for a
     REG_EQUAL note or a simple source if necessary.  */
  if (REG_P (c))
    {
      rtx set, insn = prev_nonnote_insn (earliest);
      if (insn
	  && (set = single_set (insn))
	  && rtx_equal_p (SET_DEST (set), c))
	{
	  rtx note = find_reg_equal_equiv_note (insn);
	  if (note)
	    c = XEXP (note, 0);
	  else
	    c = SET_SRC (set);
	}
      else
	return FALSE;
    }
  if (MEM_P (c)
      && GET_CODE (XEXP (c, 0)) == SYMBOL_REF
      && CONSTANT_POOL_ADDRESS_P (XEXP (c, 0)))
    c = get_pool_constant (XEXP (c, 0));

  /* Work around funny ideas get_condition has wrt canonicalization.
     Note that these rtx constants are known to be CONST_INT, and
     therefore imply integer comparisons.  */
  if (c == constm1_rtx && GET_CODE (cond) == GT)
    ;
  else if (c == const1_rtx && GET_CODE (cond) == LT)
    ;
  else if (c != CONST0_RTX (GET_MODE (b)))
    return FALSE;

  /* Determine what sort of operation this is.  */
  switch (GET_CODE (cond))
    {
    case LT:
    case LE:
    case UNLT:
    case UNLE:
      negate = !negate;
      break;
    case GT:
    case GE:
    case UNGT:
    case UNGE:
      break;
    default:
      return FALSE;
    }

  start_sequence ();

  target = expand_abs_nojump (GET_MODE (if_info->x), b, if_info->x, 1);

  /* ??? It's a quandary whether cmove would be better here, especially
     for integers.  Perhaps combine will clean things up.  */
  if (target && negate)
    target = expand_simple_unop (GET_MODE (target), NEG, target, if_info->x, 0);

  if (! target)
    {
      end_sequence ();
      return FALSE;
    }

  if (target != if_info->x)
    noce_emit_move_insn (if_info->x, target);

  seq = end_ifcvt_sequence (if_info);
  if (!seq)
    return FALSE;

  emit_insn_before_setloc (seq, if_info->jump, INSN_LOCATOR (if_info->insn_a));
  if_info->cond = cond;
  if_info->cond_earliest = earliest;

  return TRUE;
}