#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_10__ {int* bytes; } ;
typedef  TYPE_1__ decimal32 ;
struct TYPE_11__ {int bits; scalar_t__ exponent; } ;
typedef  TYPE_2__ decNumber ;
typedef  int Int ;

/* Variables and functions */
 scalar_t__ DECIMAL32_Bias ; 
 int DECIMAL32_Pmax ; 
 int DECIMAL_Inf ; 
 int DECIMAL_NaN ; 
 int DECINF ; 
 int DECNAN ; 
 int DECNEG ; 
 int DECSNAN ; 
 int /*<<< orphan*/  decDenseUnpackCoeff (int*,int,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_2__*) ; 
 scalar_t__ decimal32ExpCon (TYPE_1__ const*) ; 
 scalar_t__ decimal32Sign (TYPE_1__ const*) ; 

decNumber *
decimal32ToNumber (const decimal32 * d32, decNumber * dn)
{
  uInt msd;			/* coefficient MSD */
  decimal32 wk;			/* working copy, if needed */
  uInt top = d32->bytes[0] & 0x7f;	/* top byte, less sign bit */
  decNumberZero (dn);		/* clean target */
  /* set the sign if negative */
  if (decimal32Sign (d32))
    dn->bits = DECNEG;

  if (top >= 0x78)
    {				/* is a special */
      if ((top & 0x7c) == (DECIMAL_Inf & 0x7c))
	dn->bits |= DECINF;
      else if ((top & 0x7e) == (DECIMAL_NaN & 0x7e))
	dn->bits |= DECNAN;
      else
	dn->bits |= DECSNAN;
      msd = 0;			/* no top digit */
    }
  else
    {				/* have a finite number */
      uInt comb = top >> 2;	/* combination field */
      uInt exp;			/* working exponent */

      if (comb >= 0x18)
	{
	  msd = 8 + (comb & 0x01);
	  exp = (comb & 0x06) << 5;	/* MSBs */
	}
      else
	{
	  msd = comb & 0x07;
	  exp = (comb & 0x18) << 3;
	}
      dn->exponent = exp + decimal32ExpCon (d32) - DECIMAL32_Bias;	/* remove bias */
    }

  /* get the coefficient, unless infinite */
  if (!(dn->bits & DECINF))
    {
      Int bunches = DECIMAL32_Pmax / 3;	/* coefficient full bunches to convert */
      Int odd = 0;		/* assume MSD is 0 (no odd bunch) */
      if (msd != 0)
	{			/* coefficient has leading non-0 digit */
	  /* make a copy of the decimal32, with an extra bunch which has */
	  /* the top digit ready for conversion */
	  wk = *d32;		/* take a copy */
	  wk.bytes[0] = 0;	/* clear all but coecon */
	  wk.bytes[1] &= 0x0f;	/* .. */
	  wk.bytes[1] |= (msd << 4);	/* and prefix MSD */
	  odd++;		/* indicate the extra */
	  d32 = &wk;		/* use the work copy */
	}
      decDenseUnpackCoeff (d32->bytes, sizeof (d32->bytes), dn, bunches, odd);
    }
  return dn;
}