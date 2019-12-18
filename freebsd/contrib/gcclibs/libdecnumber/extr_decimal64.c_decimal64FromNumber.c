#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
typedef  void* uByte ;
struct TYPE_18__ {int* bytes; } ;
typedef  TYPE_1__ decimal64 ;
struct TYPE_19__ {int bits; scalar_t__ exponent; int digits; scalar_t__* lsu; } ;
typedef  TYPE_2__ decNumber ;
struct TYPE_20__ {int status; int /*<<< orphan*/  round; } ;
typedef  TYPE_3__ decContext ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 scalar_t__ DECIMAL64_Bias ; 
 int DECIMAL64_Ehigh ; 
 scalar_t__ DECIMAL64_Emax ; 
 scalar_t__ DECIMAL64_Emin ; 
 int DECIMAL64_Pmax ; 
 void* DECIMAL_Inf ; 
 void* DECIMAL_NaN ; 
 void* DECIMAL_sNaN ; 
 int DECINF ; 
 int DECNAN ; 
 int DECNEG ; 
 int DECSPECIAL ; 
 int DEC_Clamped ; 
 int /*<<< orphan*/  DEC_INIT_DECIMAL64 ; 
 int /*<<< orphan*/  DEC_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  decContextDefault (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decContextSetStatus (TYPE_3__*,int) ; 
 int /*<<< orphan*/  decDensePackCoeff (TYPE_2__ const*,int*,int,scalar_t__) ; 
 scalar_t__ decNumberIsZero (TYPE_2__ const*) ; 
 int /*<<< orphan*/  decNumberPlus (TYPE_2__*,TYPE_2__ const*,TYPE_3__*) ; 
 int /*<<< orphan*/  decimal64SetExpCon (TYPE_1__*,int) ; 
 int /*<<< orphan*/  decimal64SetSign (TYPE_1__*,int) ; 

decimal64 *
decimal64FromNumber (decimal64 * d64, const decNumber * dn, decContext * set)
{
  uInt status = 0;		/* status accumulator */
  Int pad = 0;			/* coefficient pad digits */
  decNumber dw;			/* work */
  decContext dc;		/* .. */
  uByte isneg = dn->bits & DECNEG;	/* non-0 if original sign set */
  uInt comb, exp;		/* work */

  /* If the number is finite, and has too many digits, or the exponent */
  /* could be out of range then we reduce the number under the */
  /* appropriate constraints */
  if (!(dn->bits & DECSPECIAL))
    {				/* not a special value */
      Int ae = dn->exponent + dn->digits - 1;	/* adjusted exponent */
      if (dn->digits > DECIMAL64_Pmax	/* too many digits */
	  || ae > DECIMAL64_Emax	/* likely overflow */
	  || ae < DECIMAL64_Emin)
	{			/* likely underflow */
	  decContextDefault (&dc, DEC_INIT_DECIMAL64);	/* [no traps] */
	  dc.round = set->round;	/* use supplied rounding */
	  decNumberPlus (&dw, dn, &dc);	/* (round and check) */
	  /* [this changes -0 to 0, but it will be restored below] */
	  status |= dc.status;	/* save status */
	  dn = &dw;		/* use the work number */
	}
      /* [this could have pushed number to Infinity or zero, so this */
      /* rounding must be done before we generate the decimal64] */
    }

  DEC_clear (d64);		/* clean the target */
  if (dn->bits & DECSPECIAL)
    {				/* a special value */
      uByte top;		/* work */
      if (dn->bits & DECINF)
	top = DECIMAL_Inf;
      else
	{			/* sNaN or qNaN */
	  if ((*dn->lsu != 0 || dn->digits > 1)	/* non-zero coefficient */
	      && (dn->digits < DECIMAL64_Pmax))
	    {			/* coefficient fits */
	      decDensePackCoeff (dn, d64->bytes, sizeof (d64->bytes), 0);
	    }
	  if (dn->bits & DECNAN)
	    top = DECIMAL_NaN;
	  else
	    top = DECIMAL_sNaN;
	}
      d64->bytes[0] = top;
    }
  else if (decNumberIsZero (dn))
    {				/* a zero */
      /* set and clamp exponent */
      if (dn->exponent < -DECIMAL64_Bias)
	{
	  exp = 0;
	  status |= DEC_Clamped;
	}
      else
	{
	  exp = dn->exponent + DECIMAL64_Bias;	/* bias exponent */
	  if (exp > DECIMAL64_Ehigh)
	    {			/* top clamp */
	      exp = DECIMAL64_Ehigh;
	      status |= DEC_Clamped;
	    }
	}
      comb = (exp >> 5) & 0x18;	/* combination field */
      d64->bytes[0] = (uByte) (comb << 2);
      exp &= 0xff;		/* remaining exponent bits */
      decimal64SetExpCon (d64, exp);
    }
  else
    {				/* non-zero finite number */
      uInt msd;			/* work */

      /* we have a dn that fits, but it may need to be padded */
      exp = (uInt) (dn->exponent + DECIMAL64_Bias);	/* bias exponent */
      if (exp > DECIMAL64_Ehigh)
	{			/* fold-down case */
	  pad = exp - DECIMAL64_Ehigh;
	  exp = DECIMAL64_Ehigh;	/* [to maximum] */
	  status |= DEC_Clamped;
	}

      decDensePackCoeff (dn, d64->bytes, sizeof (d64->bytes), pad);

      /* save and clear the top digit */
      msd = ((unsigned) d64->bytes[1] >> 2) & 0x0f;
      d64->bytes[1] &= 0x03;
      /* create the combination field */
      if (msd >= 8)
	comb = 0x18 | (msd & 0x01) | ((exp >> 7) & 0x06);
      else
	comb = (msd & 0x07) | ((exp >> 5) & 0x18);
      d64->bytes[0] = (uByte) (comb << 2);
      exp &= 0xff;		/* remaining exponent bits */
      decimal64SetExpCon (d64, exp);
    }

  if (isneg)
    decimal64SetSign (d64, 1);
  if (status != 0)
    decContextSetStatus (set, status);	/* pass on status */

  /*decimal64Show(d64); */
  return d64;
}