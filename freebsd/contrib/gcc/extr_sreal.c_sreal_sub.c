#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uhwi ;
struct TYPE_12__ {int exp; scalar_t__ sig_lo; scalar_t__ sig; scalar_t__ sig_hi; } ;
typedef  TYPE_1__ sreal ;

/* Variables and functions */
 int SREAL_BITS ; 
 int SREAL_PART_BITS ; 
 int /*<<< orphan*/  copy (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  shift_right (TYPE_1__*,int) ; 
 scalar_t__ sreal_compare (TYPE_1__*,TYPE_1__*) ; 

sreal *
sreal_sub (sreal *r, sreal *a, sreal *b)
{
  int dexp;
  sreal tmp;
  sreal *bb;

  gcc_assert (sreal_compare (a, b) >= 0);

  dexp = a->exp - b->exp;
  r->exp = a->exp;
  if (dexp > SREAL_BITS)
    {
#if SREAL_PART_BITS < 32
      r->sig_hi = a->sig_hi;
      r->sig_lo = a->sig_lo;
#else
      r->sig = a->sig;
#endif
      return r;
    }
  if (dexp == 0)
    bb = b;
  else
    {
      copy (&tmp, b);
      shift_right (&tmp, dexp);
      bb = &tmp;
    }

#if SREAL_PART_BITS < 32
  if (a->sig_lo < bb->sig_lo)
    {
      r->sig_hi = a->sig_hi - bb->sig_hi - 1;
      r->sig_lo = a->sig_lo + ((uhwi) 1 << SREAL_PART_BITS) - bb->sig_lo;
    }
  else
    {
      r->sig_hi = a->sig_hi - bb->sig_hi;
      r->sig_lo = a->sig_lo - bb->sig_lo;
    }
#else
  r->sig = a->sig - bb->sig;
#endif
  normalize (r);
  return r;
}