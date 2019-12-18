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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 struct real_format* REAL_MODE_FORMAT (int) ; 
 int /*<<< orphan*/  gcc_assert (struct real_format const*) ; 
 long real_to_target_fmt (long*,int /*<<< orphan*/  const*,struct real_format const*) ; 

long
real_to_target (long *buf, const REAL_VALUE_TYPE *r, enum machine_mode mode)
{
  const struct real_format *fmt;

  fmt = REAL_MODE_FORMAT (mode);
  gcc_assert (fmt);

  return real_to_target_fmt (buf, r, fmt);
}