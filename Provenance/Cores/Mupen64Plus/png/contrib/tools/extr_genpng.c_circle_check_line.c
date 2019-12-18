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
struct arg {int x1; int x2; int y1; int y2; } ;

/* Variables and functions */
 int INSIDE ; 
 int OUTSIDE ; 
 scalar_t__ circle_check (double,double,double,double,double,double) ; 
 int fabs (int) ; 

__attribute__((used)) static int
circle_check_line(const struct arg *arg, double x, double y, double w)
   /* Check for a point being inside the boundaries implied by the given arg
    * and assuming a width 2*w each side of the boundaries.  This function has
    * the same semantic as square_check_line but tests the circle.
    */
{
   double cx = (arg->x1+arg->x2)/2;
   double wx = fabs(arg->x1-arg->x2)/2;
   double cy = (arg->y1+arg->y2)/2;
   double wy = fabs(arg->y1-arg->y2)/2;

   if (circle_check(x, y, cx-wx-w, cy-wy-w, cx+wx+w, cy+wy+w))
   {
      /* Inside, but maybe too far; check for the redundant case where
       * the lines overlap:
       */
      wx -= w;
      wy -= w;
      if (wx > 0 && wy > 0 && circle_check(x, y, cx-wx, cy-wy, cx+wx, cy+wy))
         return INSIDE; /* between (inside) the boundary lines. */

      return 0; /* inside the lines themselves. */
   }

   return OUTSIDE; /* outside the boundary lines. */
}