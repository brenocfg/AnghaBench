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
struct display {unsigned int nsp; unsigned int tsp; unsigned int write_size; TYPE_1__* stack; int /*<<< orphan*/ * value; int /*<<< orphan*/  csp; } ;
typedef  size_t png_byte ;
struct TYPE_2__ {unsigned int best_size; int /*<<< orphan*/  end; int /*<<< orphan*/  best_val; } ;

/* Variables and functions */
 unsigned int MAX_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ compare_option (struct display*,unsigned int) ; 
 int /*<<< orphan*/  next_opt (struct display*,unsigned int) ; 
 int /*<<< orphan*/  push_opt (struct display*,unsigned int,size_t,int) ; 

__attribute__((used)) static int
advance_opt(struct display *dp, png_byte opt, int search)
{
   unsigned int sp = dp->csp++; /* my stack entry */

   assert(sp >= dp->nsp); /* nsp starts off zero */

   /* If the entry was active in the previous run dp->stack[sp] is already
    * set up and dp->tsp will be greater than sp, otherwise a new entry
    * needs to be created.
    *
    * dp->nsp is handled this way:
    *
    * 1) When an option is pushed onto the stack dp->nsp and dp->tsp are
    *    both set (by push_opt) to the next stack entry *unless* there is
    *    only one entry in the new list, in which case dp->stack[sp].end
    *    is set.
    *
    * 2) For the top stack entry next_opt is called.  The entry must be
    *    active (dp->stack[sp].end is not set) and either 'nsp' or 'end'
    *    will be updated as appropriate.
    *
    * 3) For lower stack entries nsp is set unless the stack entry is
    *    already at the end.  This means that when all the higher entries
    *    are popped this entry will be too.
    */
   if (sp >= dp->tsp)
   {
      push_opt(dp, sp, opt, search); /* This sets tsp to sp+1 */
      return 1; /* initialized */
   }

   else
   {
      int ret = 0; /* unchanged */

      /* An option that is already on the stack; update best_size and best_val
       * if appropriate.  On the first run there are no previous values and
       * dp->write_size will be MAX_SIZE, however on the first run dp->tsp
       * starts off as 0.
       */
      assert(dp->write_size > 0U && dp->write_size < MAX_SIZE);

      if (dp->stack[sp].best_size > dp->write_size ||
          (dp->stack[sp].best_size == dp->write_size &&
           compare_option(dp, sp) > 0))
      {
         dp->stack[sp].best_size = dp->write_size;
         dp->stack[sp].best_val = dp->value[opt];
      }

      if (sp+1U >= dp->tsp)
      {
         next_opt(dp, sp);
         ret = 1; /* advanced */
      }

      else if (!dp->stack[sp].end) /* Active, not at top of stack */
         dp->nsp = sp+1U;

      return ret; /* advanced || unchanged */
   }
}