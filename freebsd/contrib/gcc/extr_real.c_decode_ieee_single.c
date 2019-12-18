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
decode_ieee_single (const struct real_format *fmt, REAL_VALUE_TYPE *r,
		    const long *buf)
{
  unsigned long image = buf[0] & 0xffffffff;
  bool sign = (image >> 31) & 1;
  int exp = (image >> 23) & 0xff;

  memset (r, 0, sizeof (*r));
  image <<= HOST_BITS_PER_LONG - 24;
  image &= ~SIG_MSB;

  if (exp == 0)
    {
      if (image && fmt->has_denorm)
	{
	  r->cl = rvc_normal;
	  r->sign = sign;
	  SET_REAL_EXP (r, -126);
	  r->sig[SIGSZ-1] = image << 1;
	  normalize (r);
	}
      else if (fmt->has_signed_zero)
	r->sign = sign;
    }
  else if (exp == 255 && (fmt->has_nans || fmt->has_inf))
    {
      if (image)
	{
	  r->cl = rvc_nan;
	  r->sign = sign;
	  r->signalling = (((image >> (HOST_BITS_PER_LONG - 2)) & 1)
			   ^ fmt->qnan_msb_set);
	  r->sig[SIGSZ-1] = image;
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
      SET_REAL_EXP (r, exp - 127 + 1);
      r->sig[SIGSZ-1] = image | SIG_MSB;
    }
}