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
 int /*<<< orphan*/  decode_ieee_extended (struct real_format const*,int /*<<< orphan*/ *,long const*) ; 

__attribute__((used)) static void
decode_ieee_extended_intel_96 (const struct real_format *fmt, REAL_VALUE_TYPE *r,
			       const long *buf)
{
  if (FLOAT_WORDS_BIG_ENDIAN)
    {
      /* All the padding in an Intel-format extended real goes at the high
	 end, which in this case is after the mantissa, not the exponent.
	 Therefore we must shift everything up 16 bits.  */
      long intermed[3];

      intermed[0] = (((unsigned long)buf[2] >> 16) | (buf[1] << 16));
      intermed[1] = (((unsigned long)buf[1] >> 16) | (buf[0] << 16));
      intermed[2] =  ((unsigned long)buf[0] >> 16);

      decode_ieee_extended (fmt, r, intermed);
    }
  else
    /* decode_ieee_extended produces what we want directly.  */
    decode_ieee_extended (fmt, r, buf);
}