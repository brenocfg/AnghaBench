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
 scalar_t__ square_check (double,double,double,double,double,double) ; 

__attribute__((used)) static int
circle_check(double x, double y, double x1, double y1, double x2, double y2)
{
   if (square_check(x, y, x1, y1, x2, y2))
   {
      /* Inside the square, so maybe inside the circle too: */
      const double cx = (x1 + x2)/2;
      const double cy = (y1 + y2)/2;
      const double dx = x1 - x2;
      const double dy = y1 - y2;

      x = (x - cx)/dx;
      y = (y - cy)/dy;

      /* It is outside if the distance from the center is more than half the
       * diameter:
       */
      return x*x+y*y < .25;
   }

   return 0; /* outside */
}