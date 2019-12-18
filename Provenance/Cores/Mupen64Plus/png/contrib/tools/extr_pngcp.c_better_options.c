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
struct display {unsigned int csp; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int compare_option (struct display const*,unsigned int) ; 

__attribute__((used)) static int
better_options(const struct display *dp)
{
   /* Are these options better than the best found so far?  Normally the
    * options are tested in preference order, best first, however when doing a
    * search operation on a range the range values are tested out of order.  In
    * that case preferable options will get tested later.
    *
    * This function looks through the stack from the bottom up looking for an
    * option that does not match the current best value.  When it finds one it
    * checks to see if it is more or less desireable and returns true or false
    * as appropriate.
    *
    * Notice that this means that the order options are pushed onto the stack
    * conveys a priority; lower/earlier options are more important than later
    * ones.
    */
   unsigned int sp;

   for (sp=0; sp<dp->csp; ++sp)
   {
      int c = compare_option(dp, sp);

      if (c < 0)
         return 0; /* worse */

      else if (c > 0)
         return 1; /* better */
   }

   assert(0 && "unreached");
}