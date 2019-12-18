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

__attribute__((used)) static float HueToRGB(float v1, float v2, float vH)
{
   if (vH < 0)
      vH += 1;

   if (vH > 1)
      vH -= 1;

   if ((6 * vH) < 1)
      return (v1 + (v2 - v1) * 6 * vH);

   if ((2 * vH) < 1)
      return v2;

   if ((3 * vH) < 2)
      return (v1 + (v2 - v1) * ((2.0f / 3) - vH) * 6);

   return v1;
}