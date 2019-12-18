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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {int* sig; } ;
typedef  TYPE_1__ REAL_VALUE_TYPE ;

/* Variables and functions */
#define  DDmode 130 
#define  SDmode 129 
#define  TDmode 128 
 int /*<<< orphan*/  decimal_real_from_string (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

void
decimal_real_maxval (REAL_VALUE_TYPE *r, int sign, enum machine_mode mode)
{ 
  char *max;

  switch (mode)
    {
    case SDmode:
      max = (char *) "9.999999E96";
      break;
    case DDmode:
      max = (char *) "9.999999999999999E384";
      break;
    case TDmode:
      max = (char *) "9.999999999999999999999999999999999E6144";
      break;
    default:
      gcc_unreachable ();
    }

  decimal_real_from_string (r, max);
  if (sign)
    r->sig[0] |= 0x80000000;
}