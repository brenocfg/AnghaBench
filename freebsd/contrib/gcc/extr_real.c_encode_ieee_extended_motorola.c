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
 int /*<<< orphan*/  encode_ieee_extended (struct real_format const*,long*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
encode_ieee_extended_motorola (const struct real_format *fmt, long *buf,
			       const REAL_VALUE_TYPE *r)
{
  long intermed[3];
  encode_ieee_extended (fmt, intermed, r);

  /* Motorola chips are assumed always to be big-endian.  Also, the
     padding in a Motorola extended real goes between the exponent and
     the mantissa.  At this point the mantissa is entirely within
     elements 0 and 1 of intermed, and the exponent entirely within
     element 2, so all we have to do is swap the order around, and
     shift element 2 left 16 bits.  */
  buf[0] = intermed[2] << 16;
  buf[1] = intermed[1];
  buf[2] = intermed[0];
}