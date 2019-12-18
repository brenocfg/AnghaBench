#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_12__ {int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int VOIDmode ; 
 int /*<<< orphan*/  dconst1 ; 
 int /*<<< orphan*/  do_add (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_fix_trunc (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  real_convert (TYPE_1__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  real_identical (TYPE_1__*,TYPE_1__ const*) ; 

void
real_ceil (REAL_VALUE_TYPE *r, enum machine_mode mode,
	   const REAL_VALUE_TYPE *x)
{
  REAL_VALUE_TYPE t;

  do_fix_trunc (&t, x);
  if (! real_identical (&t, x) && ! x->sign)
    do_add (&t, &t, &dconst1, 0);
  if (mode != VOIDmode)
    real_convert (r, mode, &t);
  else
    *r = t;
}