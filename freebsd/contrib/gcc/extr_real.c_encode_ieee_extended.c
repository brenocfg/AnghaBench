#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct real_format {int /*<<< orphan*/  qnan_msb_set; int /*<<< orphan*/  has_nans; int /*<<< orphan*/  has_inf; } ;
struct TYPE_4__ {int* sig; int sign; int cl; int /*<<< orphan*/  signalling; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int HOST_BITS_PER_LONG ; 
 int REAL_EXP (TYPE_1__ const*) ; 
 int SIGSZ ; 
 int SIG_MSB ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

__attribute__((used)) static void
encode_ieee_extended (const struct real_format *fmt, long *buf,
		      const REAL_VALUE_TYPE *r)
{
  unsigned long image_hi, sig_hi, sig_lo;
  bool denormal = (r->sig[SIGSZ-1] & SIG_MSB) == 0;

  image_hi = r->sign << 15;
  sig_hi = sig_lo = 0;

  switch (r->cl)
    {
    case rvc_zero:
      break;

    case rvc_inf:
      if (fmt->has_inf)
	{
	  image_hi |= 32767;

	  /* Intel requires the explicit integer bit to be set, otherwise
	     it considers the value a "pseudo-infinity".  Motorola docs
	     say it doesn't care.  */
	  sig_hi = 0x80000000;
	}
      else
	{
	  image_hi |= 32767;
	  sig_lo = sig_hi = 0xffffffff;
	}
      break;

    case rvc_nan:
      if (fmt->has_nans)
	{
	  image_hi |= 32767;
	  if (HOST_BITS_PER_LONG == 32)
	    {
	      sig_hi = r->sig[SIGSZ-1];
	      sig_lo = r->sig[SIGSZ-2];
	    }
	  else
	    {
	      sig_lo = r->sig[SIGSZ-1];
	      sig_hi = sig_lo >> 31 >> 1;
	      sig_lo &= 0xffffffff;
	    }
	  if (r->signalling == fmt->qnan_msb_set)
	    sig_hi &= ~(1 << 30);
	  else
	    sig_hi |= 1 << 30;
	  if ((sig_hi & 0x7fffffff) == 0 && sig_lo == 0)
	    sig_hi = 1 << 29;

	  /* Intel requires the explicit integer bit to be set, otherwise
	     it considers the value a "pseudo-nan".  Motorola docs say it
	     doesn't care.  */
	  sig_hi |= 0x80000000;
	}
      else
	{
	  image_hi |= 32767;
	  sig_lo = sig_hi = 0xffffffff;
	}
      break;

    case rvc_normal:
      {
	int exp = REAL_EXP (r);

	/* Recall that IEEE numbers are interpreted as 1.F x 2**exp,
	   whereas the intermediate representation is 0.F x 2**exp.
	   Which means we're off by one.

	   Except for Motorola, which consider exp=0 and explicit
	   integer bit set to continue to be normalized.  In theory
	   this discrepancy has been taken care of by the difference
	   in fmt->emin in round_for_format.  */

	if (denormal)
	  exp = 0;
	else
	  {
	    exp += 16383 - 1;
	    gcc_assert (exp >= 0);
	  }
	image_hi |= exp;

	if (HOST_BITS_PER_LONG == 32)
	  {
	    sig_hi = r->sig[SIGSZ-1];
	    sig_lo = r->sig[SIGSZ-2];
	  }
	else
	  {
	    sig_lo = r->sig[SIGSZ-1];
	    sig_hi = sig_lo >> 31 >> 1;
	    sig_lo &= 0xffffffff;
	  }
      }
      break;

    default:
      gcc_unreachable ();
    }

  buf[0] = sig_lo, buf[1] = sig_hi, buf[2] = image_hi;
}