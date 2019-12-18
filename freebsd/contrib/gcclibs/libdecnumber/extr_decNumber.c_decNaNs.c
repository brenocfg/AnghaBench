#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uInt ;
struct TYPE_8__ {int bits; scalar_t__ exponent; } ;
typedef  TYPE_1__ decNumber ;

/* Variables and functions */
 int DECNAN ; 
 int DECSNAN ; 
 int DEC_Invalid_operation ; 
 int DEC_sNaN ; 
 int /*<<< orphan*/  decNumberCopy (TYPE_1__*,TYPE_1__ const*) ; 

__attribute__((used)) static decNumber *
decNaNs (decNumber * res, const decNumber * lhs, const decNumber * rhs, uInt * status)
{
  /* This decision tree ends up with LHS being the source pointer, */
  /* and status updated if need be */
  if (lhs->bits & DECSNAN)
    *status |= DEC_Invalid_operation | DEC_sNaN;
  else if (rhs == NULL);
  else if (rhs->bits & DECSNAN)
    {
      lhs = rhs;
      *status |= DEC_Invalid_operation | DEC_sNaN;
    }
  else if (lhs->bits & DECNAN);
  else
    lhs = rhs;

  decNumberCopy (res, lhs);
  res->bits &= ~DECSNAN;	/* convert any sNaN to NaN, while */
  res->bits |= DECNAN;		/* .. preserving sign */
  res->exponent = 0;		/* clean exponent */
  /* [coefficient was copied] */
  return res;
}