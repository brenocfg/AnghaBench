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
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */

__attribute__((used)) static int16_t scale_touchpad(int16_t from_min, int16_t from_max,
      int16_t to_min,   int16_t to_max, int16_t value )
{
   int32_t from_range = from_max - from_min;
   int32_t to_range   = to_max - to_min;

   return (((value - from_min) * to_range) / from_range) + to_min;
}