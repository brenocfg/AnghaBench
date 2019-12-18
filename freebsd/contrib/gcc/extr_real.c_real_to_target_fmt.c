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
struct real_format {int /*<<< orphan*/  (* encode ) (struct real_format const*,long*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  round_for_format (struct real_format const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct real_format const*,long*,int /*<<< orphan*/ *) ; 

long
real_to_target_fmt (long *buf, const REAL_VALUE_TYPE *r_orig,
		    const struct real_format *fmt)
{
  REAL_VALUE_TYPE r;
  long buf1;

  r = *r_orig;
  round_for_format (fmt, &r);

  if (!buf)
    buf = &buf1;
  (*fmt->encode) (fmt, buf, &r);

  return *buf;
}