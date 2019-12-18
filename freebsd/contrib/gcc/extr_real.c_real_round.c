#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_10__ {int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int VOIDmode ; 
 int /*<<< orphan*/  dconsthalf ; 
 int /*<<< orphan*/  do_add (TYPE_1__*,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_fix_trunc (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  real_convert (TYPE_1__*,int,TYPE_1__*) ; 

void
real_round (REAL_VALUE_TYPE *r, enum machine_mode mode,
	    const REAL_VALUE_TYPE *x)
{
  do_add (r, x, &dconsthalf, x->sign);
  do_fix_trunc (r, r);
  if (mode != VOIDmode)
    real_convert (r, mode, r);
}