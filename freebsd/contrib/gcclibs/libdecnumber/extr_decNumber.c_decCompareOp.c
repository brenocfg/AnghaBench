#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uInt ;
typedef  int uByte ;
struct TYPE_27__ {scalar_t__ digits; int bits; int* lsu; scalar_t__ exponent; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_28__ {scalar_t__ digits; int /*<<< orphan*/  extended; } ;
typedef  TYPE_2__ decContext ;
typedef  int Int ;
typedef  scalar_t__ Flag ;

/* Variables and functions */
 int BADINT ; 
 scalar_t__ COMPARE ; 
 scalar_t__ COMPMAX ; 
 scalar_t__ COMPMIN ; 
 scalar_t__ COMPNAN ; 
 int DECNAN ; 
 int DECNEG ; 
 int DECSNAN ; 
 int /*<<< orphan*/  DEC_Insufficient_storage ; 
 scalar_t__ decCheckOperands (TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,TYPE_2__*) ; 
 int decCompare (TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  decCopyFit (TYPE_1__*,TYPE_1__ const*,TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decFinish (TYPE_1__*,TYPE_2__*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decNaNs (TYPE_1__*,TYPE_1__ const*,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 TYPE_1__* decRoundOperand (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

decNumber *
decCompareOp (decNumber * res, const decNumber * lhs, const decNumber * rhs,
	      decContext * set, Flag op, uInt * status)
{
  decNumber *alloclhs = NULL;	/* non-NULL if rounded lhs allocated */
  decNumber *allocrhs = NULL;	/* .., rhs */
  Int result = 0;		/* default result value */
  uByte merged;			/* merged flags */
  uByte bits = 0;		/* non-0 for NaN */

#if DECCHECK
  if (decCheckOperands (res, lhs, rhs, set))
    return res;
#endif

  do
    {				/* protect allocated storage */
#if DECSUBSET
      if (!set->extended)
	{
	  /* reduce operands and set lostDigits status, as needed */
	  if (lhs->digits > set->digits)
	    {
	      alloclhs = decRoundOperand (lhs, set, status);
	      if (alloclhs == NULL)
		{
		  result = BADINT;
		  break;
		}
	      lhs = alloclhs;
	    }
	  if (rhs->digits > set->digits)
	    {
	      allocrhs = decRoundOperand (rhs, set, status);
	      if (allocrhs == NULL)
		{
		  result = BADINT;
		  break;
		}
	      rhs = allocrhs;
	    }
	}
#endif
      /* [following code does not require input rounding] */

      /* handle NaNs now; let infinities drop through */
      /* +++ review sNaN handling with 754r, for now assumes sNaN */
      /* (even just one) leads to NaN. */
      merged = (lhs->bits | rhs->bits) & (DECSNAN | DECNAN);
      if (merged)
	{			/* a NaN bit set */
	  if (op == COMPARE);
	  else if (merged & DECSNAN);
	  else
	    {			/* 754r rules for MIN and MAX ignore single NaN */
	      /* here if MIN or MAX, and one or two quiet NaNs */
	      if (lhs->bits & rhs->bits & DECNAN);
	      else
		{		/* just one quiet NaN */
		  /* force choice to be the non-NaN operand */
		  op = COMPMAX;
		  if (lhs->bits & DECNAN)
		    result = -1;	/* pick rhs */
		  else
		    result = +1;	/* pick lhs */
		  break;
		}
	    }
	  op = COMPNAN;		/* use special path */
	  decNaNs (res, lhs, rhs, status);
	  break;
	}

      result = decCompare (lhs, rhs);	/* we have numbers */
    }
  while (0);			/* end protected */

  if (result == BADINT)
    *status |= DEC_Insufficient_storage;	/* rare */
  else
    {
      if (op == COMPARE)
	{			/* return signum */
	  decNumberZero (res);	/* [always a valid result] */
	  if (result == 0)
	    res->bits = bits;	/* (maybe qNaN) */
	  else
	    {
	      *res->lsu = 1;
	      if (result < 0)
		res->bits = DECNEG;
	    }
	}
      else if (op == COMPNAN);	/* special, drop through */
      else
	{			/* MAX or MIN, non-NaN result */
	  Int residue = 0;	/* rounding accumulator */
	  /* choose the operand for the result */
	  const decNumber *choice;
	  if (result == 0)
	    {			/* operands are numerically equal */
	      /* choose according to sign then exponent (see 754r) */
	      uByte slhs = (lhs->bits & DECNEG);
	      uByte srhs = (rhs->bits & DECNEG);
#if DECSUBSET
	      if (!set->extended)
		{		/* subset: force left-hand */
		  op = COMPMAX;
		  result = +1;
		}
	      else
#endif
	      if (slhs != srhs)
		{		/* signs differ */
		  if (slhs)
		    result = -1;	/* rhs is max */
		  else
		    result = +1;	/* lhs is max */
		}
	      else if (slhs && srhs)
		{		/* both negative */
		  if (lhs->exponent < rhs->exponent)
		    result = +1;
		  else
		    result = -1;
		  /* [if equal, we use lhs, technically identical] */
		}
	      else
		{		/* both positive */
		  if (lhs->exponent > rhs->exponent)
		    result = +1;
		  else
		    result = -1;
		  /* [ditto] */
		}
	    }			/* numerically equal */
	  /* here result will be non-0 */
	  if (op == COMPMIN)
	    result = -result;	/* reverse if looking for MIN */
	  choice = (result > 0 ? lhs : rhs);	/* choose */
	  /* copy chosen to result, rounding if need be */
	  decCopyFit (res, choice, set, &residue, status);
	  decFinish (res, set, &residue, status);
	}
    }
  if (allocrhs != NULL)
    free (allocrhs);		/* free any storage we used */
  if (alloclhs != NULL)
    free (alloclhs);		/* .. */
  return res;
}