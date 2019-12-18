#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct real_format {int dummy; } ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ FLOAT_WORDS_BIG_ENDIAN ; 
 int /*<<< orphan*/  encode_ieee_extended (struct real_format const*,long*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
encode_ieee_extended_intel_96 (const struct real_format *fmt, long *buf,
			       const REAL_VALUE_TYPE *r)
{
  if (FLOAT_WORDS_BIG_ENDIAN)
    {
      /* All the padding in an Intel-format extended real goes at the high
	 end, which in this case is after the mantissa, not the exponent.
	 Therefore we must shift everything down 16 bits.  */
      long intermed[3];
      encode_ieee_extended (fmt, intermed, r);
      buf[0] = ((intermed[2] << 16) | ((unsigned long)(intermed[1] & 0xFFFF0000) >> 16));
      buf[1] = ((intermed[1] << 16) | ((unsigned long)(intermed[0] & 0xFFFF0000) >> 16));
      buf[2] =  (intermed[0] << 16);
    }
  else
    /* encode_ieee_extended produces what we want directly.  */
    encode_ieee_extended (fmt, buf, r);
}