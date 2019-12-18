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
 int /*<<< orphan*/  decode_ieee_extended (struct real_format const*,int /*<<< orphan*/ *,long*) ; 

__attribute__((used)) static void
decode_ieee_extended_motorola (const struct real_format *fmt, REAL_VALUE_TYPE *r,
			       const long *buf)
{
  long intermed[3];

  /* Motorola chips are assumed always to be big-endian.  Also, the
     padding in a Motorola extended real goes between the exponent and
     the mantissa; remove it.  */
  intermed[0] = buf[2];
  intermed[1] = buf[1];
  intermed[2] = (unsigned long)buf[0] >> 16;

  decode_ieee_extended (fmt, r, intermed);
}