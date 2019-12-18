#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int cl; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
 int REAL_EXP (TYPE_1__ const*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
#define  rvc_inf 131 
#define  rvc_nan 130 
#define  rvc_normal 129 
#define  rvc_zero 128 

int
real_exponent (const REAL_VALUE_TYPE *r)
{
  switch (r->cl)
    {
    case rvc_zero:
      return 0;
    case rvc_inf:
    case rvc_nan:
      return (unsigned int)-1 >> 1;
    case rvc_normal:
      return REAL_EXP (r);
    default:
      gcc_unreachable ();
    }
}