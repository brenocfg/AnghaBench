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

/* Variables and functions */

__attribute__((used)) static float easing_out_bounce(float t, float b, float c, float d)
{
   t = t / d;
   if (t < 1 / 2.75)
      return c * (7.5625 * t * t) + b;
   if (t < 2 / 2.75)
   {
      t = t - (1.5 / 2.75);
      return c * (7.5625 * t * t + 0.75) + b;
   }
   else if (t < 2.5 / 2.75)
   {
      t = t - (2.25 / 2.75);
      return c * (7.5625 * t * t + 0.9375) + b;
   }
   t = t - (2.625 / 2.75);
   return c * (7.5625 * t * t + 0.984375) + b;
}