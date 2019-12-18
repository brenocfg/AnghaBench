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
 double pow (double,int) ; 

__attribute__((used)) static double
sRGB_from_linear(double l)
{
   if (l <= 0.0031308)
      l *= 12.92;

   else
      l = 1.055 * pow(l, 1/2.4) - 0.055;

   return l;
}