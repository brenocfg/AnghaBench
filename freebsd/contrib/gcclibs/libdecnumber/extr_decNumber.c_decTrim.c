#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uInt ;
struct TYPE_6__ {int bits; int* lsu; int exponent; int digits; } ;
typedef  TYPE_1__ decNumber ;
typedef  size_t Unit ;
typedef  int Int ;
typedef  int /*<<< orphan*/  Flag ;

/* Variables and functions */
 int /*<<< orphan*/  D2U (int) ; 
 size_t DECDPUN ; 
 int DECSPECIAL ; 
 int /*<<< orphan*/  DECUNUSED ; 
 scalar_t__ ISZERO (TYPE_1__*) ; 
 size_t QUOT10 (size_t,size_t) ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decShiftToLeast (size_t*,int /*<<< orphan*/ ,int) ; 
 size_t* powers ; 

__attribute__((used)) static decNumber *
decTrim (decNumber * dn, Flag all, Int * dropped)
{
  Int d, exp;			/* work */
  uInt cut;			/* .. */
  Unit *up;			/* -> current Unit */

#if DECCHECK
  if (decCheckOperands (dn, DECUNUSED, DECUNUSED, DECUNUSED))
    return dn;
#endif

  *dropped = 0;			/* assume no zeros dropped */
  if ((dn->bits & DECSPECIAL)	/* fast exit if special .. */
      || (*dn->lsu & 0x01))
    return dn;			/* .. or odd */
  if (ISZERO (dn))
    {				/* .. or 0 */
      dn->exponent = 0;		/* (sign is preserved) */
      return dn;
    }

  /* we have a finite number which is even */
  exp = dn->exponent;
  cut = 1;			/* digit (1-DECDPUN) in Unit */
  up = dn->lsu;			/* -> current Unit */
  for (d = 0; d < dn->digits - 1; d++)
    {				/* [don't strip the final digit] */
      /* slice by powers */
#if DECDPUN<=4
      uInt quot = QUOT10 (*up, cut);
      if ((*up - quot * powers[cut]) != 0)
	break;			/* found non-0 digit */
#else
      if (*up % powers[cut] != 0)
	break;			/* found non-0 digit */
#endif
      /* have a trailing 0 */
      if (!all)
	{			/* trimming */
	  /* [if exp>0 then all trailing 0s are significant for trim] */
	  if (exp <= 0)
	    {			/* if digit might be significant */
	      if (exp == 0)
		break;		/* then quit */
	      exp++;		/* next digit might be significant */
	    }
	}
      cut++;			/* next power */
      if (cut > DECDPUN)
	{			/* need new Unit */
	  up++;
	  cut = 1;
	}
    }				/* d */
  if (d == 0)
    return dn;			/* none dropped */

  /* effect the drop */
  decShiftToLeast (dn->lsu, D2U (dn->digits), d);
  dn->exponent += d;		/* maintain numerical value */
  dn->digits -= d;		/* new length */
  *dropped = d;			/* report the count */
  return dn;
}