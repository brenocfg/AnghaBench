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
struct real_format {int emin; unsigned long qnan_msb_set; scalar_t__ has_inf; scalar_t__ has_nans; scalar_t__ has_signed_zero; scalar_t__ has_denorm; } ;
struct TYPE_6__ {int sign; unsigned long* sig; unsigned long signalling; void* cl; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int HOST_BITS_PER_LONG ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGSZ ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 void* rvc_inf ; 
 void* rvc_nan ; 
 void* rvc_normal ; 

__attribute__((used)) static void
decode_ieee_extended (const struct real_format *fmt, REAL_VALUE_TYPE *r,
		      const long *buf)
{
  unsigned long image_hi, sig_hi, sig_lo;
  bool sign;
  int exp;

  sig_lo = buf[0], sig_hi = buf[1], image_hi = buf[2];
  sig_lo &= 0xffffffff;
  sig_hi &= 0xffffffff;
  image_hi &= 0xffffffff;

  sign = (image_hi >> 15) & 1;
  exp = image_hi & 0x7fff;

  memset (r, 0, sizeof (*r));

  if (exp == 0)
    {
      if ((sig_hi || sig_lo) && fmt->has_denorm)
	{
	  r->cl = rvc_normal;
	  r->sign = sign;

	  /* When the IEEE format contains a hidden bit, we know that
	     it's zero at this point, and so shift up the significand
	     and decrease the exponent to match.  In this case, Motorola
	     defines the explicit integer bit to be valid, so we don't
	     know whether the msb is set or not.  */
	  SET_REAL_EXP (r, fmt->emin);
	  if (HOST_BITS_PER_LONG == 32)
	    {
	      r->sig[SIGSZ-1] = sig_hi;
	      r->sig[SIGSZ-2] = sig_lo;
	    }
	  else
	    r->sig[SIGSZ-1] = (sig_hi << 31 << 1) | sig_lo;

	  normalize (r);
	}
      else if (fmt->has_signed_zero)
	r->sign = sign;
    }
  else if (exp == 32767 && (fmt->has_nans || fmt->has_inf))
    {
      /* See above re "pseudo-infinities" and "pseudo-nans".
	 Short summary is that the MSB will likely always be
	 set, and that we don't care about it.  */
      sig_hi &= 0x7fffffff;

      if (sig_hi || sig_lo)
	{
	  r->cl = rvc_nan;
	  r->sign = sign;
	  r->signalling = ((sig_hi >> 30) & 1) ^ fmt->qnan_msb_set;
	  if (HOST_BITS_PER_LONG == 32)
	    {
	      r->sig[SIGSZ-1] = sig_hi;
	      r->sig[SIGSZ-2] = sig_lo;
	    }
	  else
	    r->sig[SIGSZ-1] = (sig_hi << 31 << 1) | sig_lo;
	}
      else
	{
	  r->cl = rvc_inf;
	  r->sign = sign;
	}
    }
  else
    {
      r->cl = rvc_normal;
      r->sign = sign;
      SET_REAL_EXP (r, exp - 16383 + 1);
      if (HOST_BITS_PER_LONG == 32)
	{
	  r->sig[SIGSZ-1] = sig_hi;
	  r->sig[SIGSZ-2] = sig_lo;
	}
      else
	r->sig[SIGSZ-1] = (sig_hi << 31 << 1) | sig_lo;
    }
}