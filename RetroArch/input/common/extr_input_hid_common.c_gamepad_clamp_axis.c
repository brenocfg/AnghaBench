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
typedef  scalar_t__ int16_t ;

/* Variables and functions */

__attribute__((used)) static int16_t gamepad_clamp_axis(int16_t value, bool is_negative)
{
   if (is_negative && value > 0)
      return 0;
   if (!is_negative && value < 0)
      return 0;

   return value;
}