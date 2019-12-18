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

__attribute__((used)) static int
line_check(double x, double y, double x1, double y1, double x2, double y2,
   double w, double expand)
{
   /* Shift all the points to (arg->x1, arg->y1) */
   double lx = x2 - x1;
   double ly = y2 - y1;
   double len2 = lx*lx + ly*ly;
   double cross, dot;

   x -= x1;
   y -= y1;

   /* The dot product is the distance down the line, the cross product is
    * the distance away from the line:
    *
    *    distance = |cross| / sqrt(len2)
    */
   cross = x * ly - y * lx;

   /* If 'distance' is more than w the point is definitely outside the line:
    *
    *     distance >= w
    *     |cross|  >= w * sqrt(len2)
    *     cross^2  >= w^2 * len2:
    */
   if (cross*cross >= (w+expand)*(w+expand)*len2)
      return 0; /* outside */

   /* Now find the distance *along* the line; this comes from the dot product
    * lx.x+ly.y. The actual distance (in pixels) is:
    *
    *   distance = dot / sqrt(len2)
    */
   dot = lx * x + ly * y;

   /* The test for 'outside' is:
    *
    *    distance < 0 || distance > sqrt(len2)
    *                 -> dot / sqrt(len2) > sqrt(len2)
    *                 -> dot > len2
    *
    * But 'expand' is used for the filter width and needs to be handled too:
    */
   return dot > -expand && dot < len2+expand;
}