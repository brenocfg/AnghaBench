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
struct real_format {unsigned long qnan_msb_set; scalar_t__ has_inf; scalar_t__ has_nans; scalar_t__ has_signed_zero; scalar_t__ has_denorm; } ;
struct TYPE_8__ {int sign; unsigned long* sig; unsigned long signalling; void* cl; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 int HOST_BITS_PER_LONG ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int SIGNIFICAND_BITS ; 
 int SIGSZ ; 
 unsigned long SIG_MSB ; 
 int /*<<< orphan*/  lshift_significand (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 void* rvc_inf ; 
 void* rvc_nan ; 
 void* rvc_normal ; 

__attribute__((used)) static void
decode_ieee_quad (const struct real_format *fmt, REAL_VALUE_TYPE *r,
		  const long *buf)
{
  unsigned long image3, image2, image1, image0;
  bool sign;
  int exp;

  if (FLOAT_WORDS_BIG_ENDIAN)
    {
      image3 = buf[0];
      image2 = buf[1];
      image1 = buf[2];
      image0 = buf[3];
    }
  else
    {
      image0 = buf[0];
      image1 = buf[1];
      image2 = buf[2];
      image3 = buf[3];
    }
  image0 &= 0xffffffff;
  image1 &= 0xffffffff;
  image2 &= 0xffffffff;

  sign = (image3 >> 31) & 1;
  exp = (image3 >> 16) & 0x7fff;
  image3 &= 0xffff;

  memset (r, 0, sizeof (*r));

  if (exp == 0)
    {
      if ((image3 | image2 | image1 | image0) && fmt->has_denorm)
	{
	  r->cl = rvc_normal;
	  r->sign = sign;

	  SET_REAL_EXP (r, -16382 + (SIGNIFICAND_BITS - 112));
	  if (HOST_BITS_PER_LONG == 32)
	    {
	      r->sig[0] = image0;
	      r->sig[1] = image1;
	      r->sig[2] = image2;
	      r->sig[3] = image3;
	    }
	  else
	    {
	      r->sig[0] = (image1 << 31 << 1) | image0;
	      r->sig[1] = (image3 << 31 << 1) | image2;
	    }

	  normalize (r);
	}
      else if (fmt->has_signed_zero)
	r->sign = sign;
    }
  else if (exp == 32767 && (fmt->has_nans || fmt->has_inf))
    {
      if (image3 | image2 | image1 | image0)
	{
	  r->cl = rvc_nan;
	  r->sign = sign;
	  r->signalling = ((image3 >> 15) & 1) ^ fmt->qnan_msb_set;

	  if (HOST_BITS_PER_LONG == 32)
	    {
	      r->sig[0] = image0;
	      r->sig[1] = image1;
	      r->sig[2] = image2;
	      r->sig[3] = image3;
	    }
	  else
	    {
	      r->sig[0] = (image1 << 31 << 1) | image0;
	      r->sig[1] = (image3 << 31 << 1) | image2;
	    }
	  lshift_significand (r, r, SIGNIFICAND_BITS - 113);
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
	  r->sig[0] = image0;
	  r->sig[1] = image1;
	  r->sig[2] = image2;
	  r->sig[3] = image3;
	}
      else
	{
	  r->sig[0] = (image1 << 31 << 1) | image0;
	  r->sig[1] = (image3 << 31 << 1) | image2;
	}
      lshift_significand (r, r, SIGNIFICAND_BITS - 113);
      r->sig[SIGSZ-1] |= SIG_MSB;
    }
}