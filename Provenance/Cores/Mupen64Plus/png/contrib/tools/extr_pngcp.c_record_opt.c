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
struct display {unsigned int csp; unsigned int const tsp; int opt_string_start; TYPE_1__* stack; } ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_2__ {int opt_string_end; } ;

/* Variables and functions */
 int set_opt_string_ (struct display*,unsigned int const,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void
record_opt(struct display *dp, png_byte opt, const char *entry_name)
   /* Record this option in dp->curr; called for an option not being searched,
    * the caller passes in the name of the value, or range_lo to use the
    * numerical value.
    */
{
   const unsigned int sp = dp->csp; /* stack entry of next searched option */

   if (sp >= dp->tsp)
   {
      /* At top of stack; add the opt string for this entry to the previous
       * searched entry or the start of the dp->curr buffer if there is nothing
       * on the stack yet (sp == 0).
       */
      const int offset = set_opt_string_(dp, sp, opt, entry_name);

      if (sp > 0)
         dp->stack[sp-1].opt_string_end = offset;

      else
         dp->opt_string_start = offset;
   }

   /* else do nothing: option already recorded */
}