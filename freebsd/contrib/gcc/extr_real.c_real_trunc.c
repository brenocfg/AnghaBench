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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int VOIDmode ; 
 int /*<<< orphan*/  do_fix_trunc (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  real_convert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void
real_trunc (REAL_VALUE_TYPE *r, enum machine_mode mode,
	    const REAL_VALUE_TYPE *x)
{
  do_fix_trunc (r, x);
  if (mode != VOIDmode)
    real_convert (r, mode, r);
}