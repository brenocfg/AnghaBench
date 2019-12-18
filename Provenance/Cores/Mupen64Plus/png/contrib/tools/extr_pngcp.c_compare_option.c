#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct display {scalar_t__* value; TYPE_1__* stack; } ;
struct TYPE_2__ {int opt; scalar_t__ best_val; scalar_t__ lo; scalar_t__ hi; } ;

/* Variables and functions */

__attribute__((used)) static int
compare_option(const struct display *dp, unsigned int sp)
{
   int opt = dp->stack[sp].opt;

   /* If the best so far is numerically less than the current value the
    * current set of options is invariably worse.
    */
   if (dp->stack[sp].best_val < dp->value[opt])
      return -1;

   /* Lists of options are searched out of numerical order (currently only
    * strategy), so only return +1 here when a range is being searched.
    */
   else if (dp->stack[sp].best_val > dp->value[opt])
   {
      if (dp->stack[sp].lo <= dp->stack[sp].hi /*searching*/)
         return 1;

      else
         return -1;
   }

   else
      return 0; /* match; current value is the best one */
}