#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
struct TYPE_7__ {scalar_t__ exponent; scalar_t__* lsu; int digits; int bits; } ;
typedef  TYPE_1__ decNumber ;
typedef  scalar_t__ Unit ;
typedef  scalar_t__ Int ;
typedef  int Flag ;

/* Variables and functions */
 int D2U (int) ; 
 int DECDPUN ; 
 int DECSNAN ; 
 int DECSPECIAL ; 
 int /*<<< orphan*/  DECUNUSED ; 
 int /*<<< orphan*/  ISZERO (TYPE_1__ const*) ; 
 int /*<<< orphan*/  TODIGIT (scalar_t__,scalar_t__,char*) ; 
 scalar_t__ decCheckOperands (int /*<<< orphan*/ ,TYPE_1__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ decNumberIsInfinite (TYPE_1__ const*) ; 
 scalar_t__ decNumberIsNegative (TYPE_1__ const*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void
decToString (const decNumber * dn, char *string, Flag eng)
{
  Int exp = dn->exponent;	/* local copy */
  Int e;			/* E-part value */
  Int pre;			/* digits before the '.' */
  Int cut;			/* for counting digits in a Unit */
  char *c = string;		/* work [output pointer] */
  const Unit *up = dn->lsu + D2U (dn->digits) - 1;	/* -> msu [input pointer] */
  uInt u, pow;			/* work */

#if DECCHECK
  if (decCheckOperands (DECUNUSED, dn, DECUNUSED, DECUNUSED))
    {
      strcpy (string, "?");
      return;
    }
#endif

  if (decNumberIsNegative (dn))
    {				/* Negatives get a minus (except */
      *c = '-';			/* NaNs, which remove the '-' below) */
      c++;
    }
  if (dn->bits & DECSPECIAL)
    {				/* Is a special value */
      if (decNumberIsInfinite (dn))
	{
	  strcpy (c, "Infinity");
	  return;
	}
      /* a NaN */
      if (dn->bits & DECSNAN)
	{			/* signalling NaN */
	  *c = 's';
	  c++;
	}
      strcpy (c, "NaN");
      c += 3;			/* step past */
      /* if not a clean non-zero coefficient, that's all we have in a */
      /* NaN string */
      if (exp != 0 || (*dn->lsu == 0 && dn->digits == 1))
	return;
      /* [drop through to add integer] */
    }

  /* calculate how many digits in msu, and hence first cut */
  cut = dn->digits % DECDPUN;
  if (cut == 0)
    cut = DECDPUN;		/* msu is full */
  cut--;			/* power of ten for digit */

  if (exp == 0)
    {				/* simple integer [common fastpath, */
      /*   used for NaNs, too] */
      for (; up >= dn->lsu; up--)
	{			/* each Unit from msu */
	  u = *up;		/* contains DECDPUN digits to lay out */
	  for (; cut >= 0; c++, cut--)
	    TODIGIT (u, cut, c);
	  cut = DECDPUN - 1;	/* next Unit has all digits */
	}
      *c = '\0';		/* terminate the string */
      return;
    }

  /* non-0 exponent -- assume plain form */
  pre = dn->digits + exp;	/* digits before '.' */
  e = 0;			/* no E */
  if ((exp > 0) || (pre < -5))
    {				/* need exponential form */
      e = exp + dn->digits - 1;	/* calculate E value */
      pre = 1;			/* assume one digit before '.' */
      if (eng && (e != 0))
	{			/* may need to adjust */
	  Int adj;		/* adjustment */
	  /* The C remainder operator is undefined for negative numbers, so */
	  /* we must use positive remainder calculation here */
	  if (e < 0)
	    {
	      adj = (-e) % 3;
	      if (adj != 0)
		adj = 3 - adj;
	    }
	  else
	    {			/* e>0 */
	      adj = e % 3;
	    }
	  e = e - adj;
	  /* if we are dealing with zero we will use exponent which is a */
	  /* multiple of three, as expected, but there will only be the */
	  /* one zero before the E, still.  Otherwise note the padding. */
	  if (!ISZERO (dn))
	    pre += adj;
	  else
	    {			/* is zero */
	      if (adj != 0)
		{		/* 0.00Esnn needed */
		  e = e + 3;
		  pre = -(2 - adj);
		}
	    }			/* zero */
	}			/* eng */
    }

  /* lay out the digits of the coefficient, adding 0s and . as needed */
  u = *up;
  if (pre > 0)
    {				/* xxx.xxx or xx00 (engineering) form */
      for (; pre > 0; pre--, c++, cut--)
	{
	  if (cut < 0)
	    {			/* need new Unit */
	      if (up == dn->lsu)
		break;		/* out of input digits (pre>digits) */
	      up--;
	      cut = DECDPUN - 1;
	      u = *up;
	    }
	  TODIGIT (u, cut, c);
	}
      if (up > dn->lsu || (up == dn->lsu && cut >= 0))
	{			/* more to come, after '.' */
	  *c = '.';
	  c++;
	  for (;; c++, cut--)
	    {
	      if (cut < 0)
		{		/* need new Unit */
		  if (up == dn->lsu)
		    break;	/* out of input digits */
		  up--;
		  cut = DECDPUN - 1;
		  u = *up;
		}
	      TODIGIT (u, cut, c);
	    }
	}
      else
	for (; pre > 0; pre--, c++)
	  *c = '0';		/* 0 padding (for engineering) needed */
    }
  else
    {				/* 0.xxx or 0.000xxx form */
      *c = '0';
      c++;
      *c = '.';
      c++;
      for (; pre < 0; pre++, c++)
	*c = '0';		/* add any 0's after '.' */
      for (;; c++, cut--)
	{
	  if (cut < 0)
	    {			/* need new Unit */
	      if (up == dn->lsu)
		break;		/* out of input digits */
	      up--;
	      cut = DECDPUN - 1;
	      u = *up;
	    }
	  TODIGIT (u, cut, c);
	}
    }

  /* Finally add the E-part, if needed.  It will never be 0, has a
     base maximum and minimum of +999999999 through -999999999, but
     could range down to -1999999998 for subnormal numbers */
  if (e != 0)
    {
      Flag had = 0;		/* 1=had non-zero */
      *c = 'E';
      c++;
      *c = '+';
      c++;			/* assume positive */
      u = e;			/* .. */
      if (e < 0)
	{
	  *(c - 1) = '-';	/* oops, need - */
	  u = -e;		/* uInt, please */
	}
      /* layout the exponent (_itoa is not ANSI C) */
      for (cut = 9; cut >= 0; cut--)
	{
	  TODIGIT (u, cut, c);
	  if (*c == '0' && !had)
	    continue;		/* skip leading zeros */
	  had = 1;		/* had non-0 */
	  c++;			/* step for next */
	}			/* cut */
    }
  *c = '\0';			/* terminate the string (all paths) */
  return;
}