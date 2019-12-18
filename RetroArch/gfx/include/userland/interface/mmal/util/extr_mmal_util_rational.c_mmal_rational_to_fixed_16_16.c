#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {int den; scalar_t__ num; } ;
typedef  TYPE_1__ MMAL_RATIONAL_T ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 

int32_t mmal_rational_to_fixed_16_16(MMAL_RATIONAL_T rational)
{
   int64_t result = (int64_t)rational.num << 16;
   if (rational.den)
      result /= rational.den;

   if (result > INT_MAX)
      result = INT_MAX;
   else if (result < INT_MIN)
      result = INT_MIN;

   return (int32_t)result;
}