#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct real_format {int b; int p; int log2_b; int emin; int emax; int /*<<< orphan*/  has_denorm; int /*<<< orphan*/  has_signed_zero; } ;
struct TYPE_20__ {int cl; unsigned long* sig; int /*<<< orphan*/  sign; scalar_t__ decimal; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DFmode ; 
 int HOST_BITS_PER_LONG ; 
 int REAL_EXP (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGNIFICAND_BITS ; 
 int SIGSZ ; 
 unsigned long SIG_MSB ; 
 scalar_t__ add_significands (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  clear_significand_below (TYPE_1__*,int) ; 
 int /*<<< orphan*/  decimal_real_convert (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  decimal_round_for_format (struct real_format const*,TYPE_1__*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_inf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_zero (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rshift_significand (TYPE_1__*,TYPE_1__*,int) ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 
 int /*<<< orphan*/  set_significand_bit (TYPE_1__*,int) ; 
 unsigned long sticky_rshift_significand (TYPE_1__*,TYPE_1__*,int) ; 
 int test_significand_bit (TYPE_1__*,int) ; 

__attribute__((used)) static void
round_for_format (const struct real_format *fmt, REAL_VALUE_TYPE *r)
{
  int p2, np2, i, w;
  unsigned long sticky;
  bool guard, lsb;
  int emin2m1, emax2;

  if (r->decimal)
    {
      if (fmt->b == 10)
	{
	  decimal_round_for_format (fmt, r);
	  return;
	}
      /* FIXME. We can come here via fp_easy_constant
	 (e.g. -O0 on '_Decimal32 x = 1.0 + 2.0dd'), but have not
	 investigated whether this convert needs to be here, or
	 something else is missing. */
      decimal_real_convert (r, DFmode, r);
    }

  p2 = fmt->p * fmt->log2_b;
  emin2m1 = (fmt->emin - 1) * fmt->log2_b;
  emax2 = fmt->emax * fmt->log2_b;

  np2 = SIGNIFICAND_BITS - p2;
  switch (r->cl)
    {
    underflow:
      get_zero (r, r->sign);
    case rvc_zero:
      if (!fmt->has_signed_zero)
	r->sign = 0;
      return;

    overflow:
      get_inf (r, r->sign);
    case rvc_inf:
      return;

    case rvc_nan:
      clear_significand_below (r, np2);
      return;

    case rvc_normal:
      break;

    default:
      gcc_unreachable ();
    }

  /* If we're not base2, normalize the exponent to a multiple of
     the true base.  */
  if (fmt->log2_b != 1)
    {
      int shift;

      gcc_assert (fmt->b != 10);
      shift = REAL_EXP (r) & (fmt->log2_b - 1);
      if (shift)
	{
	  shift = fmt->log2_b - shift;
	  r->sig[0] |= sticky_rshift_significand (r, r, shift);
	  SET_REAL_EXP (r, REAL_EXP (r) + shift);
	}
    }

  /* Check the range of the exponent.  If we're out of range,
     either underflow or overflow.  */
  if (REAL_EXP (r) > emax2)
    goto overflow;
  else if (REAL_EXP (r) <= emin2m1)
    {
      int diff;

      if (!fmt->has_denorm)
	{
	  /* Don't underflow completely until we've had a chance to round.  */
	  if (REAL_EXP (r) < emin2m1)
	    goto underflow;
	}
      else
	{
	  diff = emin2m1 - REAL_EXP (r) + 1;
	  if (diff > p2)
	    goto underflow;

	  /* De-normalize the significand.  */
	  r->sig[0] |= sticky_rshift_significand (r, r, diff);
	  SET_REAL_EXP (r, REAL_EXP (r) + diff);
	}
    }

  /* There are P2 true significand bits, followed by one guard bit,
     followed by one sticky bit, followed by stuff.  Fold nonzero
     stuff into the sticky bit.  */

  sticky = 0;
  for (i = 0, w = (np2 - 1) / HOST_BITS_PER_LONG; i < w; ++i)
    sticky |= r->sig[i];
  sticky |=
    r->sig[w] & (((unsigned long)1 << ((np2 - 1) % HOST_BITS_PER_LONG)) - 1);

  guard = test_significand_bit (r, np2 - 1);
  lsb = test_significand_bit (r, np2);

  /* Round to even.  */
  if (guard && (sticky || lsb))
    {
      REAL_VALUE_TYPE u;
      get_zero (&u, 0);
      set_significand_bit (&u, np2);

      if (add_significands (r, r, &u))
	{
	  /* Overflow.  Means the significand had been all ones, and
	     is now all zeros.  Need to increase the exponent, and
	     possibly re-normalize it.  */
	  SET_REAL_EXP (r, REAL_EXP (r) + 1);
	  if (REAL_EXP (r) > emax2)
	    goto overflow;
	  r->sig[SIGSZ-1] = SIG_MSB;

	  if (fmt->log2_b != 1)
	    {
	      int shift = REAL_EXP (r) & (fmt->log2_b - 1);
	      if (shift)
		{
		  shift = fmt->log2_b - shift;
		  rshift_significand (r, r, shift);
		  SET_REAL_EXP (r, REAL_EXP (r) + shift);
		  if (REAL_EXP (r) > emax2)
		    goto overflow;
		}
	    }
	}
    }

  /* Catch underflow that we deferred until after rounding.  */
  if (REAL_EXP (r) <= emin2m1)
    goto underflow;

  /* Clear out trailing garbage.  */
  clear_significand_below (r, np2);
}