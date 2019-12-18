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
struct arg {int width; int /*<<< orphan*/  y2; int /*<<< orphan*/  x2; int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;

/* Variables and functions */
 int FILTER_WIDTH ; 
 int INSIDE ; 
 int OUTSIDE ; 
 scalar_t__ line_check (double,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
check_line(const struct arg *arg, double x, double y)
{
   /* The end caps of the line must be checked too; it's not enough just to
    * widen the line by FILTER_WIDTH; 'expand' exists for this purpose:
    */
   if (line_check(x, y, arg->x1, arg->y1, arg->x2, arg->y2, arg->width/2,
       FILTER_WIDTH))
   {
      /* Inside the line+filter; far enough inside that the filter isn't
       * required?
       */
      if (arg->width > 2*FILTER_WIDTH &&
          line_check(x, y, arg->x1, arg->y1, arg->x2, arg->y2, arg->width/2,
             -FILTER_WIDTH))
         return INSIDE;

      return 0;
   }

   return OUTSIDE;
}