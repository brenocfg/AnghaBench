#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct real_format {int b; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {scalar_t__ cl; scalar_t__ decimal; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 struct real_format* REAL_MODE_FORMAT (int) ; 
 int /*<<< orphan*/  decimal_real_convert (TYPE_1__*,int,TYPE_1__ const*) ; 
 int /*<<< orphan*/  gcc_assert (struct real_format const*) ; 
 int /*<<< orphan*/  normalize (TYPE_1__*) ; 
 int /*<<< orphan*/  round_for_format (struct real_format const*,TYPE_1__*) ; 
 scalar_t__ rvc_normal ; 

void
real_convert (REAL_VALUE_TYPE *r, enum machine_mode mode,
	      const REAL_VALUE_TYPE *a)
{
  const struct real_format *fmt;

  fmt = REAL_MODE_FORMAT (mode);
  gcc_assert (fmt);

  *r = *a;

  if (a->decimal || fmt->b == 10)
    decimal_real_convert (r, mode, a);

  round_for_format (fmt, r);

  /* round_for_format de-normalizes denormals.  Undo just that part.  */
  if (r->cl == rvc_normal)
    normalize (r);
}