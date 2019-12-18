#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uInt ;
struct TYPE_8__ {int* lsu; size_t digits; scalar_t__ exponent; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_9__ {int round; scalar_t__ emax; scalar_t__ emin; scalar_t__ digits; } ;
typedef  TYPE_2__ decContext ;
typedef  int Unit ;
typedef  scalar_t__ Int ;

/* Variables and functions */
 int /*<<< orphan*/  D2U (int) ; 
 size_t DECDPUN ; 
 int DECDPUNMAX ; 
 size_t DEC_Inexact ; 
 size_t DEC_Invalid_context ; 
#define  DEC_ROUND_CEILING 134 
#define  DEC_ROUND_DOWN 133 
#define  DEC_ROUND_FLOOR 132 
#define  DEC_ROUND_HALF_DOWN 131 
#define  DEC_ROUND_HALF_EVEN 130 
#define  DEC_ROUND_HALF_UP 129 
#define  DEC_ROUND_UP 128 
 size_t DEC_Rounded ; 
 size_t DEC_Subnormal ; 
 size_t DEC_Underflow ; 
 int /*<<< orphan*/  decNumberIsNegative (TYPE_1__*) ; 
 int /*<<< orphan*/  decSetOverflow (TYPE_1__*,TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  decUnitAddSub (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int /*<<< orphan*/  one ; 
 int* powers ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
decApplyRound (decNumber * dn, decContext * set, Int residue, uInt * status)
{
  Int bump;			/* 1 if coefficient needs to be incremented */
  /* -1 if coefficient needs to be decremented */

  if (residue == 0)
    return;			/* nothing to apply */

  bump = 0;			/* assume a smooth ride */

  /* now decide whether, and how, to round, depending on mode */
  switch (set->round)
    {
    case DEC_ROUND_DOWN:
      {
	/* no change, except if negative residue */
	if (residue < 0)
	  bump = -1;
	break;
      }				/* r-d */

    case DEC_ROUND_HALF_DOWN:
      {
	if (residue > 5)
	  bump = 1;
	break;
      }				/* r-h-d */

    case DEC_ROUND_HALF_EVEN:
      {
	if (residue > 5)
	  bump = 1;		/* >0.5 goes up */
	else if (residue == 5)
	  {			/* exactly 0.5000... */
	    /* 0.5 goes up iff [new] lsd is odd */
	    if (*dn->lsu & 0x01)
	      bump = 1;
	  }
	break;
      }				/* r-h-e */

    case DEC_ROUND_HALF_UP:
      {
	if (residue >= 5)
	  bump = 1;
	break;
      }				/* r-h-u */

    case DEC_ROUND_UP:
      {
	if (residue > 0)
	  bump = 1;
	break;
      }				/* r-u */

    case DEC_ROUND_CEILING:
      {
	/* same as _UP for positive numbers, and as _DOWN for negatives */
	/* [negative residue cannot occur on 0] */
	if (decNumberIsNegative (dn))
	  {
	    if (residue < 0)
	      bump = -1;
	  }
	else
	  {
	    if (residue > 0)
	      bump = 1;
	  }
	break;
      }				/* r-c */

    case DEC_ROUND_FLOOR:
      {
	/* same as _UP for negative numbers, and as _DOWN for positive */
	/* [negative residue cannot occur on 0] */
	if (!decNumberIsNegative (dn))
	  {
	    if (residue < 0)
	      bump = -1;
	  }
	else
	  {
	    if (residue > 0)
	      bump = 1;
	  }
	break;
      }				/* r-f */

    default:
      {				/* e.g., DEC_ROUND_MAX */
	*status |= DEC_Invalid_context;
#if DECTRACE
	printf ("Unknown rounding mode: %d\n", set->round);
#endif
	break;
      }
    }				/* switch */

  /* now bump the number, up or down, if need be */
  if (bump == 0)
    return;			/* no action required */

  /* Simply use decUnitAddSub unless we are bumping up and the number */
  /* is all nines.  In this special case we set to 1000... and adjust */
  /* the exponent by one (as otherwise we could overflow the array) */
  /* Similarly handle all-nines result if bumping down. */
  if (bump > 0)
    {
      Unit *up;			/* work */
      uInt count = dn->digits;	/* digits to be checked */
      for (up = dn->lsu;; up++)
	{
	  if (count <= DECDPUN)
	    {
	      /* this is the last Unit (the msu) */
	      if (*up != powers[count] - 1)
		break;		/* not still 9s */
	      /* here if it, too, is all nines */
	      *up = (Unit) powers[count - 1];	/* here 999 -> 100 etc. */
	      for (up = up - 1; up >= dn->lsu; up--)
		*up = 0;	/* others all to 0 */
	      dn->exponent++;	/* and bump exponent */
	      /* [which, very rarely, could cause Overflow...] */
	      if ((dn->exponent + dn->digits) > set->emax + 1)
		{
		  decSetOverflow (dn, set, status);
		}
	      return;		/* done */
	    }
	  /* a full unit to check, with more to come */
	  if (*up != DECDPUNMAX)
	    break;		/* not still 9s */
	  count -= DECDPUN;
	}			/* up */
    }				/* bump>0 */
  else
    {				/* -1 */
      /* here we are lookng for a pre-bump of 1000... (leading 1, */
      /* all other digits zero) */
      Unit *up, *sup;		/* work */
      uInt count = dn->digits;	/* digits to be checked */
      for (up = dn->lsu;; up++)
	{
	  if (count <= DECDPUN)
	    {
	      /* this is the last Unit (the msu) */
	      if (*up != powers[count - 1])
		break;		/* not 100.. */
	      /* here if we have the 1000... case */
	      sup = up;		/* save msu pointer */
	      *up = (Unit) powers[count] - 1;	/* here 100 in msu -> 999 */
	      /* others all to all-nines, too */
	      for (up = up - 1; up >= dn->lsu; up--)
		*up = (Unit) powers[DECDPUN] - 1;
	      dn->exponent--;	/* and bump exponent */

	      /* iff the number was at the subnormal boundary (exponent=etiny) */
	      /* then the exponent is now out of range, so it will in fact get */
	      /* clamped to etiny and the final 9 dropped. */
	      /* printf(">> emin=%d exp=%d sdig=%d\n", set->emin, */
	      /*        dn->exponent, set->digits); */
	      if (dn->exponent + 1 == set->emin - set->digits + 1)
		{
		  if (count == 1 && dn->digits == 1)
		    *sup = 0;	/* here 9 -> 0[.9] */
		  else
		    {
		      *sup = (Unit) powers[count - 1] - 1;	/* here 999.. in msu -> 99.. */
		      dn->digits--;
		    }
		  dn->exponent++;
		  *status |=
		    DEC_Underflow | DEC_Subnormal | DEC_Inexact | DEC_Rounded;
		}
	      return;		/* done */
	    }

	  /* a full unit to check, with more to come */
	  if (*up != 0)
	    break;		/* not still 0s */
	  count -= DECDPUN;
	}			/* up */

    }				/* bump<0 */

  /* Actual bump needed.  Do it. */
  decUnitAddSub (dn->lsu, D2U (dn->digits), one, 1, 0, dn->lsu, bump);
}