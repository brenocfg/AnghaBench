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
 scalar_t__ square_check_line (struct arg const*,double,double,double) ; 

__attribute__((used)) static int
check_square(const struct arg *arg, double x, double y)
{
   /* So for this function a result of 'INSIDE' means inside the actual lines.
    */
   double w = arg->width/2;

   if (square_check_line(arg, x, y, w+FILTER_WIDTH) == 0)
   {
      /* Somewhere close to the boundary lines. If far enough inside one of
       * them then we can return INSIDE:
       */
      w -= FILTER_WIDTH;

      if (w > 0 && square_check_line(arg, x, y, w) == 0)
         return INSIDE;

      /* Point is somewhere in the filter region: */
      return 0;
   }

   else /* Inside or outside the square by more than w+FILTER_WIDTH. */
      return OUTSIDE;
}