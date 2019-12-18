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

__attribute__((used)) static double
YfromRGB(double r, double g, double b)
{
   /* Use the sRGB (rounded) coefficients for Rlinear, Glinear, Blinear to get
    * the CIE Y value (also linear).
    */
   return 0.2126 * r + 0.7152 * g + 0.0722 * b;
}