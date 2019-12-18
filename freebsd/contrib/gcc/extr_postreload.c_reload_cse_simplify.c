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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CLOBBER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PARALLEL ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ REG_FUNCTION_VALUE_P (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_change_group () ; 
 scalar_t__ asm_noperands (scalar_t__) ; 
 int /*<<< orphan*/  cselib_invalidate_rtx (scalar_t__) ; 
 int /*<<< orphan*/  delete_insn_and_edges (scalar_t__) ; 
 scalar_t__ reload_cse_noop_set_p (scalar_t__) ; 
 int /*<<< orphan*/  reload_cse_simplify_operands (scalar_t__,scalar_t__) ; 
 scalar_t__ reload_cse_simplify_set (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
reload_cse_simplify (rtx insn, rtx testreg)
{
  rtx body = PATTERN (insn);

  if (GET_CODE (body) == SET)
    {
      int count = 0;

      /* Simplify even if we may think it is a no-op.
         We may think a memory load of a value smaller than WORD_SIZE
         is redundant because we haven't taken into account possible
         implicit extension.  reload_cse_simplify_set() will bring
         this out, so it's safer to simplify before we delete.  */
      count += reload_cse_simplify_set (body, insn);

      if (!count && reload_cse_noop_set_p (body))
	{
	  rtx value = SET_DEST (body);
	  if (REG_P (value)
	      && ! REG_FUNCTION_VALUE_P (value))
	    value = 0;
	  delete_insn_and_edges (insn);
	  return;
	}

      if (count > 0)
	apply_change_group ();
      else
	reload_cse_simplify_operands (insn, testreg);
    }
  else if (GET_CODE (body) == PARALLEL)
    {
      int i;
      int count = 0;
      rtx value = NULL_RTX;

      /* Registers mentioned in the clobber list for an asm cannot be reused
	 within the body of the asm.  Invalidate those registers now so that
	 we don't try to substitute values for them.  */
      if (asm_noperands (body) >= 0)
	{
	  for (i = XVECLEN (body, 0) - 1; i >= 0; --i)
	    {
	      rtx part = XVECEXP (body, 0, i);
	      if (GET_CODE (part) == CLOBBER && REG_P (XEXP (part, 0)))
		cselib_invalidate_rtx (XEXP (part, 0));
	    }
	}

      /* If every action in a PARALLEL is a noop, we can delete
	 the entire PARALLEL.  */
      for (i = XVECLEN (body, 0) - 1; i >= 0; --i)
	{
	  rtx part = XVECEXP (body, 0, i);
	  if (GET_CODE (part) == SET)
	    {
	      if (! reload_cse_noop_set_p (part))
		break;
	      if (REG_P (SET_DEST (part))
		  && REG_FUNCTION_VALUE_P (SET_DEST (part)))
		{
		  if (value)
		    break;
		  value = SET_DEST (part);
		}
	    }
	  else if (GET_CODE (part) != CLOBBER)
	    break;
	}

      if (i < 0)
	{
	  delete_insn_and_edges (insn);
	  /* We're done with this insn.  */
	  return;
	}

      /* It's not a no-op, but we can try to simplify it.  */
      for (i = XVECLEN (body, 0) - 1; i >= 0; --i)
	if (GET_CODE (XVECEXP (body, 0, i)) == SET)
	  count += reload_cse_simplify_set (XVECEXP (body, 0, i), insn);

      if (count > 0)
	apply_change_group ();
      else
	reload_cse_simplify_operands (insn, testreg);
    }
}