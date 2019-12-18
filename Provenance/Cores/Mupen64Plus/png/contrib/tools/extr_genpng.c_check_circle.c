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
struct arg {int width; } ;

/* Variables and functions */
 double FILTER_WIDTH ; 
 int INSIDE ; 
 int OUTSIDE ; 
 scalar_t__ circle_check_line (struct arg const*,double,double,double) ; 

__attribute__((used)) static int
check_circle(const struct arg *arg, double x, double y)
{
   /* Exactly as the 'square' code.  */
   double w = arg->width/2;

   if (circle_check_line(arg, x, y, w+FILTER_WIDTH) == 0)
   {
      w -= FILTER_WIDTH;

      if (w > 0 && circle_check_line(arg, x, y, w) == 0)
         return INSIDE;

      /* Point is somewhere in the filter region: */
      return 0;
   }

   else /* Inside or outside the square by more than w+FILTER_WIDTH. */
      return OUTSIDE;
}