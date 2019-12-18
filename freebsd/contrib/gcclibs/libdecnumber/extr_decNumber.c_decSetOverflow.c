#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
typedef  int uByte ;
struct TYPE_7__ {int bits; int exponent; int digits; scalar_t__* lsu; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_8__ {int emax; int digits; int round; scalar_t__ clamp; } ;
typedef  TYPE_2__ decContext ;
typedef  scalar_t__ Unit ;
typedef  int Int ;
typedef  int Flag ;

/* Variables and functions */
 int DECDPUN ; 
 scalar_t__ DECDPUNMAX ; 
 int DECINF ; 
 int DECNEG ; 
 int DEC_Clamped ; 
 int DEC_Inexact ; 
 int DEC_Overflow ; 
#define  DEC_ROUND_CEILING 130 
#define  DEC_ROUND_DOWN 129 
#define  DEC_ROUND_FLOOR 128 
 int DEC_Rounded ; 
 scalar_t__ ISZERO (TYPE_1__*) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int* powers ; 

__attribute__((used)) static void
decSetOverflow (decNumber * dn, decContext * set, uInt * status)
{
  Flag needmax = 0;		/* result is maximum finite value */
  uByte sign = dn->bits & DECNEG;	/* clean and save sign bit */

  if (ISZERO (dn))
    {				/* zero does not overflow magnitude */
      Int emax = set->emax;	/* limit value */
      if (set->clamp)
	emax -= set->digits - 1;	/* lower if clamping */
      if (dn->exponent > emax)
	{			/* clamp required */
	  dn->exponent = emax;
	  *status |= DEC_Clamped;
	}
      return;
    }

  decNumberZero (dn);
  switch (set->round)
    {
    case DEC_ROUND_DOWN:
      {
	needmax = 1;		/* never Infinity */
	break;
      }				/* r-d */
    case DEC_ROUND_CEILING:
      {
	if (sign)
	  needmax = 1;		/* Infinity if non-negative */
	break;
      }				/* r-c */
    case DEC_ROUND_FLOOR:
      {
	if (!sign)
	  needmax = 1;		/* Infinity if negative */
	break;
      }				/* r-f */
    default:
      break;			/* Infinity in all other cases */
    }
  if (needmax)
    {
      Unit *up;			/* work */
      Int count = set->digits;	/* nines to add */
      dn->digits = count;
      /* fill in all nines to set maximum value */
      for (up = dn->lsu;; up++)
	{
	  if (count > DECDPUN)
	    *up = DECDPUNMAX;	/* unit full o'nines */
	  else
	    {			/* this is the msu */
	      *up = (Unit) (powers[count] - 1);
	      break;
	    }
	  count -= DECDPUN;	/* we filled those digits */
	}			/* up */
      dn->bits = sign;		/* sign */
      dn->exponent = set->emax - set->digits + 1;
    }
  else
    dn->bits = sign | DECINF;	/* Value is +/-Infinity */
  *status |= DEC_Overflow | DEC_Inexact | DEC_Rounded;
}