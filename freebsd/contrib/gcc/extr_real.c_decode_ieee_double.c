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
struct real_format {unsigned long qnan_msb_set; scalar_t__ has_inf; scalar_t__ has_nans; scalar_t__ has_signed_zero; scalar_t__ has_denorm; } ;
struct TYPE_6__ {int sign; unsigned long* sig; unsigned long signalling; void* cl; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 int HOST_BITS_PER_LONG ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGSZ ; 
 unsigned long SIG_MSB ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 void* rvc_inf ; 
 void* rvc_nan ; 
 void* rvc_normal ; 

__attribute__((used)) static void
decode_ieee_double (const struct real_format *fmt, REAL_VALUE_TYPE *r,
		    const long *buf)
{
  unsigned long image_hi, image_lo;
  bool sign;
  int exp;

  if (FLOAT_WORDS_BIG_ENDIAN)
    image_hi = buf[0], image_lo = buf[1];
  else
    image_lo = buf[0], image_hi = buf[1];
  image_lo &= 0xffffffff;
  image_hi &= 0xffffffff;

  sign = (image_hi >> 31) & 1;
  exp = (image_hi >> 20) & 0x7ff;

  memset (r, 0, sizeof (*r));

  image_hi <<= 32 - 21;
  image_hi |= image_lo >> 21;
  image_hi &= 0x7fffffff;
  image_lo <<= 32 - 21;

  if (exp == 0)
    {
      if ((image_hi || image_lo) && fmt->has_denorm)
	{
	  r->cl = rvc_normal;
	  r->sign = sign;
	  SET_REAL_EXP (r, -1022);
	  if (HOST_BITS_PER_LONG == 32)
	    {
	      image_hi = (image_hi << 1) | (image_lo >> 31);
	      image_lo <<= 1;
	      r->sig[SIGSZ-1] = image_hi;
	      r->sig[SIGSZ-2] = image_lo;
	    }
	  else
	    {
	      image_hi = (image_hi << 31 << 2) | (image_lo << 1);
	      r->sig[SIGSZ-1] = image_hi;
	    }
	  normalize (r);
	}
      else if (fmt->has_signed_zero)
	r->sign = sign;
    }
  else if (exp == 2047 && (fmt->has_nans || fmt->has_inf))
    {
      if (image_hi || image_lo)
	{
	  r->cl = rvc_nan;
	  r->sign = sign;
	  r->signalling = ((image_hi >> 30) & 1) ^ fmt->qnan_msb_set;
	  if (HOST_BITS_PER_LONG == 32)
	    {
	      r->sig[SIGSZ-1] = image_hi;
	      r->sig[SIGSZ-2] = image_lo;
	    }
	  else
	    r->sig[SIGSZ-1] = (image_hi << 31 << 1) | image_lo;
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
      SET_REAL_EXP (r, exp - 1023 + 1);
      if (HOST_BITS_PER_LONG == 32)
	{
	  r->sig[SIGSZ-1] = image_hi | SIG_MSB;
	  r->sig[SIGSZ-2] = image_lo;
	}
      else
	r->sig[SIGSZ-1] = (image_hi << 31 << 1) | image_lo | SIG_MSB;
    }
}