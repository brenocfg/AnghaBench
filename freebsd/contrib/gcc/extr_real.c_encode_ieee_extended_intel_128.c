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
 int /*<<< orphan*/  encode_ieee_extended_intel_96 (struct real_format const*,long*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
encode_ieee_extended_intel_128 (const struct real_format *fmt, long *buf,
				const REAL_VALUE_TYPE *r)
{
  /* All the padding in an Intel-format extended real goes at the high end.  */
  encode_ieee_extended_intel_96 (fmt, buf, r);
  buf[3] = 0;
}