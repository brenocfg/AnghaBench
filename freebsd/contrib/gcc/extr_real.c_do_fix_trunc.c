#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int cl; int /*<<< orphan*/  sign; int /*<<< orphan*/  decimal; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ REAL_EXP (TYPE_1__*) ; 
 scalar_t__ SIGNIFICAND_BITS ; 
 int /*<<< orphan*/  clear_significand_below (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  decimal_do_fix_trunc (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_zero (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

__attribute__((used)) static void
do_fix_trunc (REAL_VALUE_TYPE *r, const REAL_VALUE_TYPE *a)
{
  *r = *a;

  switch (r->cl)
    {
    case rvc_zero:
    case rvc_inf:
    case rvc_nan:
      break;

    case rvc_normal:
      if (r->decimal)
	{
	  decimal_do_fix_trunc (r, a);
	  return;
	}
      if (REAL_EXP (r) <= 0)
	get_zero (r, r->sign);
      else if (REAL_EXP (r) < SIGNIFICAND_BITS)
	clear_significand_below (r, SIGNIFICAND_BITS - REAL_EXP (r));
      break;

    default:
      gcc_unreachable ();
    }
}