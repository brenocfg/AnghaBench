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
struct TYPE_4__ {unsigned long sign; int* sig; int cl; int /*<<< orphan*/  canonical; int /*<<< orphan*/  signalling; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int HOST_BITS_PER_LONG ; 
 int /*<<< orphan*/  REAL_EXP (TYPE_1__ const*) ; 
 int SIGSZ ; 
 int SIG_MSB ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

__attribute__((used)) static void
encode_ieee_single (const struct real_format *fmt, long *buf,
		    const REAL_VALUE_TYPE *r)
{
  unsigned long image, sig, exp;
  unsigned long sign = r->sign;
  bool denormal = (r->sig[SIGSZ-1] & SIG_MSB) == 0;

  image = sign << 31;
  sig = (r->sig[SIGSZ-1] >> (HOST_BITS_PER_LONG - 24)) & 0x7fffff;

  switch (r->cl)
    {
    case rvc_zero:
      break;

    case rvc_inf:
      if (fmt->has_inf)
	image |= 255 << 23;
      else
	image |= 0x7fffffff;
      break;

    case rvc_nan:
      if (fmt->has_nans)
	{
	  if (r->canonical)
	    sig = 0;
	  if (r->signalling == fmt->qnan_msb_set)
	    sig &= ~(1 << 22);
	  else
	    sig |= 1 << 22;
	  /* We overload qnan_msb_set here: it's only clear for
	     mips_ieee_single, which wants all mantissa bits but the
	     quiet/signalling one set in canonical NaNs (at least
	     Quiet ones).  */
	  if (r->canonical && !fmt->qnan_msb_set)
	    sig |= (1 << 22) - 1;
	  else if (sig == 0)
	    sig = 1 << 21;

	  image |= 255 << 23;
	  image |= sig;
	}
      else
	image |= 0x7fffffff;
      break;

    case rvc_normal:
      /* Recall that IEEE numbers are interpreted as 1.F x 2**exp,
	 whereas the intermediate representation is 0.F x 2**exp.
	 Which means we're off by one.  */
      if (denormal)
	exp = 0;
      else
      exp = REAL_EXP (r) + 127 - 1;
      image |= exp << 23;
      image |= sig;
      break;

    default:
      gcc_unreachable ();
    }

  buf[0] = image;
}