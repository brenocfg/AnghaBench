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
struct TYPE_8__ {int cl; int /*<<< orphan*/  sign; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int MAX_EXP ; 
 int REAL_EXP (TYPE_1__ const*) ; 
 int /*<<< orphan*/  SET_REAL_EXP (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_inf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_zero (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

void
real_ldexp (REAL_VALUE_TYPE *r, const REAL_VALUE_TYPE *op0, int exp)
{
  *r = *op0;
  switch (r->cl)
    {
    case rvc_zero:
    case rvc_inf:
    case rvc_nan:
      break;

    case rvc_normal:
      exp += REAL_EXP (op0);
      if (exp > MAX_EXP)
	get_inf (r, r->sign);
      else if (exp < -MAX_EXP)
	get_zero (r, r->sign);
      else
	SET_REAL_EXP (r, exp);
      break;

    default:
      gcc_unreachable ();
    }
}