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
 double pow (double,double) ; 

__attribute__((used)) static double
linear_from_sRGB(double s)
{
   if (s <= 0.04045)
      return s / 12.92;

   else
      return pow((s+0.055)/1.055, 2.4);
}