#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct real_format {scalar_t__ qnan_msb_set; } ;
struct TYPE_9__ {scalar_t__ cl; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  do_add (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  encode_ieee_double (struct real_format const*,long*,TYPE_1__*) ; 
 struct real_format ieee_double_format ; 
 struct real_format mips_double_format ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  round_for_format (struct real_format const*,TYPE_1__*) ; 
 scalar_t__ rvc_normal ; 

__attribute__((used)) static void
encode_ibm_extended (const struct real_format *fmt, long *buf,
		     const REAL_VALUE_TYPE *r)
{
  REAL_VALUE_TYPE u, normr, v;
  const struct real_format *base_fmt;

  base_fmt = fmt->qnan_msb_set ? &ieee_double_format : &mips_double_format;

  /* Renormlize R before doing any arithmetic on it.  */
  normr = *r;
  if (normr.cl == rvc_normal)
    normalize (&normr);

  /* u = IEEE double precision portion of significand.  */
  u = normr;
  round_for_format (base_fmt, &u);
  encode_ieee_double (base_fmt, &buf[0], &u);

  if (u.cl == rvc_normal)
    {
      do_add (&v, &normr, &u, 1);
      /* Call round_for_format since we might need to denormalize.  */
      round_for_format (base_fmt, &v);
      encode_ieee_double (base_fmt, &buf[2], &v);
    }
  else
    {
      /* Inf, NaN, 0 are all representable as doubles, so the
	 least-significant part can be 0.0.  */
      buf[2] = 0;
      buf[3] = 0;
    }
}