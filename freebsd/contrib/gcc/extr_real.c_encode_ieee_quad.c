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
struct real_format {int /*<<< orphan*/  qnan_msb_set; int /*<<< orphan*/  has_nans; int /*<<< orphan*/  has_inf; } ;
struct TYPE_6__ {int* sig; int sign; int cl; int /*<<< orphan*/  canonical; int /*<<< orphan*/  signalling; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 int HOST_BITS_PER_LONG ; 
 int /*<<< orphan*/  REAL_EXP (TYPE_1__ const*) ; 
 scalar_t__ SIGNIFICAND_BITS ; 
 int SIGSZ ; 
 int SIG_MSB ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  rshift_significand (TYPE_1__*,TYPE_1__ const*,scalar_t__) ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

__attribute__((used)) static void
encode_ieee_quad (const struct real_format *fmt, long *buf,
		  const REAL_VALUE_TYPE *r)
{
  unsigned long image3, image2, image1, image0, exp;
  bool denormal = (r->sig[SIGSZ-1] & SIG_MSB) == 0;
  REAL_VALUE_TYPE u;

  image3 = r->sign << 31;
  image2 = 0;
  image1 = 0;
  image0 = 0;

  rshift_significand (&u, r, SIGNIFICAND_BITS - 113);

  switch (r->cl)
    {
    case rvc_zero:
      break;

    case rvc_inf:
      if (fmt->has_inf)
	image3 |= 32767 << 16;
      else
	{
	  image3 |= 0x7fffffff;
	  image2 = 0xffffffff;
	  image1 = 0xffffffff;
	  image0 = 0xffffffff;
	}
      break;

    case rvc_nan:
      if (fmt->has_nans)
	{
	  image3 |= 32767 << 16;

	  if (r->canonical)
	    {
	      /* Don't use bits from the significand.  The
		 initialization above is right.  */
	    }
	  else if (HOST_BITS_PER_LONG == 32)
	    {
	      image0 = u.sig[0];
	      image1 = u.sig[1];
	      image2 = u.sig[2];
	      image3 |= u.sig[3] & 0xffff;
	    }
	  else
	    {
	      image0 = u.sig[0];
	      image1 = image0 >> 31 >> 1;
	      image2 = u.sig[1];
	      image3 |= (image2 >> 31 >> 1) & 0xffff;
	      image0 &= 0xffffffff;
	      image2 &= 0xffffffff;
	    }
	  if (r->signalling == fmt->qnan_msb_set)
	    image3 &= ~0x8000;
	  else
	    image3 |= 0x8000;
	  /* We overload qnan_msb_set here: it's only clear for
	     mips_ieee_single, which wants all mantissa bits but the
	     quiet/signalling one set in canonical NaNs (at least
	     Quiet ones).  */
	  if (r->canonical && !fmt->qnan_msb_set)
	    {
	      image3 |= 0x7fff;
	      image2 = image1 = image0 = 0xffffffff;
	    }
	  else if (((image3 & 0xffff) | image2 | image1 | image0) == 0)
	    image3 |= 0x4000;
	}
      else
	{
	  image3 |= 0x7fffffff;
	  image2 = 0xffffffff;
	  image1 = 0xffffffff;
	  image0 = 0xffffffff;
	}
      break;

    case rvc_normal:
      /* Recall that IEEE numbers are interpreted as 1.F x 2**exp,
	 whereas the intermediate representation is 0.F x 2**exp.
	 Which means we're off by one.  */
      if (denormal)
	exp = 0;
      else
	exp = REAL_EXP (r) + 16383 - 1;
      image3 |= exp << 16;

      if (HOST_BITS_PER_LONG == 32)
	{
	  image0 = u.sig[0];
	  image1 = u.sig[1];
	  image2 = u.sig[2];
	  image3 |= u.sig[3] & 0xffff;
	}
      else
	{
	  image0 = u.sig[0];
	  image1 = image0 >> 31 >> 1;
	  image2 = u.sig[1];
	  image3 |= (image2 >> 31 >> 1) & 0xffff;
	  image0 &= 0xffffffff;
	  image2 &= 0xffffffff;
	}
      break;

    default:
      gcc_unreachable ();
    }

  if (FLOAT_WORDS_BIG_ENDIAN)
    {
      buf[0] = image3;
      buf[1] = image2;
      buf[2] = image1;
      buf[3] = image0;
    }
  else
    {
      buf[0] = image0;
      buf[1] = image1;
      buf[2] = image2;
      buf[3] = image3;
    }
}