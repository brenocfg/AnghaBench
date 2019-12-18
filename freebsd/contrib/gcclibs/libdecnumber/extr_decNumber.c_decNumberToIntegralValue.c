#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uInt ;
struct TYPE_24__ {int bits; scalar_t__ exponent; int /*<<< orphan*/  digits; } ;
typedef  TYPE_1__ decNumber ;
struct TYPE_25__ {scalar_t__ traps; int /*<<< orphan*/  digits; } ;
typedef  TYPE_2__ decContext ;

/* Variables and functions */
 int DECSPECIAL ; 
 int /*<<< orphan*/  DECUNUSED ; 
 scalar_t__ decCheckOperands (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__ const*,TYPE_2__*) ; 
 int /*<<< orphan*/  decNaNs (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_1__* decNumberCopy (TYPE_1__*,TYPE_1__ const*) ; 
 scalar_t__ decNumberIsInfinite (TYPE_1__ const*) ; 
 TYPE_1__* decNumberQuantize (TYPE_1__*,TYPE_1__ const*,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  decNumberZero (TYPE_1__*) ; 
 int /*<<< orphan*/  decStatus (TYPE_1__*,scalar_t__,TYPE_2__*) ; 

decNumber *
decNumberToIntegralValue (decNumber * res, const decNumber * rhs, decContext * set)
{
  decNumber dn;
  decContext workset;		/* working context */

#if DECCHECK
  if (decCheckOperands (res, DECUNUSED, rhs, set))
    return res;
#endif

  /* handle infinities and NaNs */
  if (rhs->bits & DECSPECIAL)
    {
      uInt status = 0;
      if (decNumberIsInfinite (rhs))
	decNumberCopy (res, rhs);	/* an Infinity */
      else
	decNaNs (res, rhs, NULL, &status);	/* a NaN */
      if (status != 0)
	decStatus (res, status, set);
      return res;
    }

  /* we have a finite number; no error possible */
  if (rhs->exponent >= 0)
    return decNumberCopy (res, rhs);
  /* that was easy, but if negative exponent we have work to do... */
  workset = *set;		/* clone rounding, etc. */
  workset.digits = rhs->digits;	/* no length rounding */
  workset.traps = 0;		/* no traps */
  decNumberZero (&dn);		/* make a number with exponent 0 */
  return decNumberQuantize (res, rhs, &dn, &workset);
}