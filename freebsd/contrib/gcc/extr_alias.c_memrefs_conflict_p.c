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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int AND ; 
 int CONST ; 
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int CONST_INT ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int HIGH ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int LO_SUM ; 
#define  MULT 128 
 scalar_t__ PLUS ; 
 int VALUE ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  addr_side_effect_eval (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canon_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ rtx_equal_for_memref_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
memrefs_conflict_p (int xsize, rtx x, int ysize, rtx y, HOST_WIDE_INT c)
{
  if (GET_CODE (x) == VALUE)
    x = get_addr (x);
  if (GET_CODE (y) == VALUE)
    y = get_addr (y);
  if (GET_CODE (x) == HIGH)
    x = XEXP (x, 0);
  else if (GET_CODE (x) == LO_SUM)
    x = XEXP (x, 1);
  else
    x = addr_side_effect_eval (x, xsize, 0);
  if (GET_CODE (y) == HIGH)
    y = XEXP (y, 0);
  else if (GET_CODE (y) == LO_SUM)
    y = XEXP (y, 1);
  else
    y = addr_side_effect_eval (y, ysize, 0);

  if (rtx_equal_for_memref_p (x, y))
    {
      if (xsize <= 0 || ysize <= 0)
	return 1;
      if (c >= 0 && xsize > c)
	return 1;
      if (c < 0 && ysize+c > 0)
	return 1;
      return 0;
    }

  /* This code used to check for conflicts involving stack references and
     globals but the base address alias code now handles these cases.  */

  if (GET_CODE (x) == PLUS)
    {
      /* The fact that X is canonicalized means that this
	 PLUS rtx is canonicalized.  */
      rtx x0 = XEXP (x, 0);
      rtx x1 = XEXP (x, 1);

      if (GET_CODE (y) == PLUS)
	{
	  /* The fact that Y is canonicalized means that this
	     PLUS rtx is canonicalized.  */
	  rtx y0 = XEXP (y, 0);
	  rtx y1 = XEXP (y, 1);

	  if (rtx_equal_for_memref_p (x1, y1))
	    return memrefs_conflict_p (xsize, x0, ysize, y0, c);
	  if (rtx_equal_for_memref_p (x0, y0))
	    return memrefs_conflict_p (xsize, x1, ysize, y1, c);
	  if (GET_CODE (x1) == CONST_INT)
	    {
	      if (GET_CODE (y1) == CONST_INT)
		return memrefs_conflict_p (xsize, x0, ysize, y0,
					   c - INTVAL (x1) + INTVAL (y1));
	      else
		return memrefs_conflict_p (xsize, x0, ysize, y,
					   c - INTVAL (x1));
	    }
	  else if (GET_CODE (y1) == CONST_INT)
	    return memrefs_conflict_p (xsize, x, ysize, y0, c + INTVAL (y1));

	  return 1;
	}
      else if (GET_CODE (x1) == CONST_INT)
	return memrefs_conflict_p (xsize, x0, ysize, y, c - INTVAL (x1));
    }
  else if (GET_CODE (y) == PLUS)
    {
      /* The fact that Y is canonicalized means that this
	 PLUS rtx is canonicalized.  */
      rtx y0 = XEXP (y, 0);
      rtx y1 = XEXP (y, 1);

      if (GET_CODE (y1) == CONST_INT)
	return memrefs_conflict_p (xsize, x, ysize, y0, c + INTVAL (y1));
      else
	return 1;
    }

  if (GET_CODE (x) == GET_CODE (y))
    switch (GET_CODE (x))
      {
      case MULT:
	{
	  /* Handle cases where we expect the second operands to be the
	     same, and check only whether the first operand would conflict
	     or not.  */
	  rtx x0, y0;
	  rtx x1 = canon_rtx (XEXP (x, 1));
	  rtx y1 = canon_rtx (XEXP (y, 1));
	  if (! rtx_equal_for_memref_p (x1, y1))
	    return 1;
	  x0 = canon_rtx (XEXP (x, 0));
	  y0 = canon_rtx (XEXP (y, 0));
	  if (rtx_equal_for_memref_p (x0, y0))
	    return (xsize == 0 || ysize == 0
		    || (c >= 0 && xsize > c) || (c < 0 && ysize+c > 0));

	  /* Can't properly adjust our sizes.  */
	  if (GET_CODE (x1) != CONST_INT)
	    return 1;
	  xsize /= INTVAL (x1);
	  ysize /= INTVAL (x1);
	  c /= INTVAL (x1);
	  return memrefs_conflict_p (xsize, x0, ysize, y0, c);
	}

      default:
	break;
      }

  /* Treat an access through an AND (e.g. a subword access on an Alpha)
     as an access with indeterminate size.  Assume that references
     besides AND are aligned, so if the size of the other reference is
     at least as large as the alignment, assume no other overlap.  */
  if (GET_CODE (x) == AND && GET_CODE (XEXP (x, 1)) == CONST_INT)
    {
      if (GET_CODE (y) == AND || ysize < -INTVAL (XEXP (x, 1)))
	xsize = -1;
      return memrefs_conflict_p (xsize, canon_rtx (XEXP (x, 0)), ysize, y, c);
    }
  if (GET_CODE (y) == AND && GET_CODE (XEXP (y, 1)) == CONST_INT)
    {
      /* ??? If we are indexing far enough into the array/structure, we
	 may yet be able to determine that we can not overlap.  But we
	 also need to that we are far enough from the end not to overlap
	 a following reference, so we do nothing with that for now.  */
      if (GET_CODE (x) == AND || xsize < -INTVAL (XEXP (y, 1)))
	ysize = -1;
      return memrefs_conflict_p (xsize, x, ysize, canon_rtx (XEXP (y, 0)), c);
    }

  if (CONSTANT_P (x))
    {
      if (GET_CODE (x) == CONST_INT && GET_CODE (y) == CONST_INT)
	{
	  c += (INTVAL (y) - INTVAL (x));
	  return (xsize <= 0 || ysize <= 0
		  || (c >= 0 && xsize > c) || (c < 0 && ysize+c > 0));
	}

      if (GET_CODE (x) == CONST)
	{
	  if (GET_CODE (y) == CONST)
	    return memrefs_conflict_p (xsize, canon_rtx (XEXP (x, 0)),
				       ysize, canon_rtx (XEXP (y, 0)), c);
	  else
	    return memrefs_conflict_p (xsize, canon_rtx (XEXP (x, 0)),
				       ysize, y, c);
	}
      if (GET_CODE (y) == CONST)
	return memrefs_conflict_p (xsize, x, ysize,
				   canon_rtx (XEXP (y, 0)), c);

      if (CONSTANT_P (y))
	return (xsize <= 0 || ysize <= 0
		|| (rtx_equal_for_memref_p (x, y)
		    && ((c >= 0 && xsize > c) || (c < 0 && ysize+c > 0))));

      return 1;
    }
  return 1;
}