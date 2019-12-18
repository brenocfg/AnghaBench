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
 float HueToRGB (float,float,float) ; 

__attribute__((used)) static void HSLToRGB(float H, float S, float L, float *rgb) {
   if (S == 0)
      rgb[0] = rgb[1] = rgb[2] = L;
   else
   {
      float v1, v2;

      v2 = (L < 0.5) ? (L * (1 + S)) : ((L + S) - (L * S));
      v1 = 2 * L - v2;

      rgb[0] = HueToRGB(v1, v2, H + (1.0f / 3));
      rgb[1] = HueToRGB(v1, v2, H);
      rgb[2] = HueToRGB(v1, v2, H - (1.0f / 3));
   }
}