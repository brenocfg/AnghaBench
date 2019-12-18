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
typedef  int int64_t ;
struct TYPE_4__ {int num; scalar_t__ den; } ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int MMAL_FALSE ; 

MMAL_BOOL_T mmal_rational_equal(MMAL_RATIONAL_T a, MMAL_RATIONAL_T b)
{
   if (a.num != b.num && a.num * (int64_t)b.num == 0)
      return MMAL_FALSE;
   return a.num * (int64_t)b.den == b.num * (int64_t)a.den;
}