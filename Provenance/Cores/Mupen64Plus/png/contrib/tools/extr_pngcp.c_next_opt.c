#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct display {unsigned int tsp; int* value; unsigned int nsp; TYPE_2__* stack; } ;
typedef  unsigned int png_byte ;
typedef  scalar_t__ png_alloc_size_t ;
struct TYPE_6__ {unsigned int value_count; TYPE_1__* values; } ;
struct TYPE_5__ {int end; unsigned int opt; unsigned int entry; int lo; int hi; scalar_t__ best_size; scalar_t__ lo_size; scalar_t__ hi_size; int best_val; } ;
struct TYPE_4__ {char* name; int value; } ;

/* Variables and functions */
 scalar_t__ MAX_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ opt_list_end (struct display*,unsigned int,unsigned int) ; 
 TYPE_3__* options ; 
 char const* range_lo ; 
 int /*<<< orphan*/  set_opt_string (struct display*,unsigned int) ; 

__attribute__((used)) static void
next_opt(struct display *dp, unsigned int sp)
   /* Return the next value for this option.  When called 'sp' is expected to be
    * the topmost stack entry - only the topmost entry changes each time round -
    * and there must be a valid entry to return.  next_opt will set dp->nsp to
    * sp+1 if more entries are available, otherwise it will not change it and
    * set dp->stack[s].end to true.
    */
{
   int search = 0;
   png_byte entry, opt;
   const char *entry_name;

   /* dp->stack[sp] must be the top stack entry and it must be active: */
   assert(sp+1U == dp->tsp && !dp->stack[sp].end);

   opt = dp->stack[sp].opt;
   entry = dp->stack[sp].entry;
   assert(entry+1U < options[opt].value_count);
   entry_name = options[opt].values[entry].name;
   assert(entry_name != NULL);

   /* For ranges increment the value but don't change the entry, for all other
    * cases move to the next entry and load its value:
    */
   if (entry_name == range_lo) /* a range */
   {
      /* A range can be iterated over or searched.  The default iteration option
       * is indicated by hi < lo on the stack, otherwise the range being search
       * is [lo..hi] (inclusive).
       */
      if (dp->stack[sp].lo > dp->stack[sp].hi)
         dp->value[opt]++;

      else
      {
         /* This is the best size found for this option value: */
         png_alloc_size_t best_size = dp->stack[sp].best_size;
         int lo = dp->stack[sp].lo;
         int hi = dp->stack[sp].hi;
         int val = dp->value[opt];

         search = 1; /* end is determined here */
         assert(best_size < MAX_SIZE);

         if (val == lo)
         {
            /* Finding the best for the low end of the range: */
            dp->stack[sp].lo_size = best_size;
            assert(hi > val);

            if (hi == val+1) /* only 2 entries */
               dp->stack[sp].end = 1;

            val = hi;
         }

         else if (val == hi)
         {
            dp->stack[sp].hi_size = best_size;
            assert(val > lo+1); /* else 'end' set above */

            if (val == lo+2) /* only three entries to test */
               dp->stack[sp].end = 1;

            val = (lo + val)/2;
         }

         else
         {
            png_alloc_size_t lo_size = dp->stack[sp].lo_size;
            png_alloc_size_t hi_size = dp->stack[sp].hi_size;

            /* lo and hi should have been tested. */
            assert(lo_size < MAX_SIZE && hi_size < MAX_SIZE);

            /* These cases arise with the 'probe' handling below when there is a
             * dip or peak in the size curve.
             */
            if (val < lo) /* probing a new lo */
            {
               /* Swap lo and val: */
               dp->stack[sp].lo = val;
               dp->stack[sp].lo_size = best_size;
               val = lo;
               best_size = lo_size;
               lo = dp->stack[sp].lo;
               lo_size = dp->stack[sp].lo_size;
            }

            else if (val > hi) /* probing a new hi */
            {
               /* Swap hi and val: */
               dp->stack[sp].hi = val;
               dp->stack[sp].hi_size = best_size;
               val = hi;
               best_size = hi_size;
               hi = dp->stack[sp].hi;
               hi_size = dp->stack[sp].hi_size;
            }

            /* The following should be true or something got messed up above. */
            assert(lo < val && val < hi);

            /* If there are only four entries (lo, val, hi plus one more) just
             * test the remaining entry.
             */
            if (hi == lo+3)
            {
               /* Because of the 'probe' code val can either be lo+1 or hi-1; we
                * need to test the other.
                */
               val = lo + ((val == lo+1) ? 2 : 1);
               assert(lo < val && val < hi);
               dp->stack[sp].end = 1;
            }

            else
            {
               /* There are at least 2 entries still untested between lo and hi,
                * i.e. hi >= lo+4.  'val' is the midpoint +/- 0.5
                *
                * Separate out the four easy cases when lo..val..hi are
                * monotonically decreased or (more weird) increasing:
                */
               assert(hi > lo+3);

               if (lo_size <= best_size && best_size <= hi_size)
               {
                  /* Select the low range; testing this first favours the low
                   * range over the high range when everything comes out equal.
                   * Because of the probing 'val' may be lo+1.  In that case end
                   * the search and set 'val' to lo+2.
                   */
                  if (val == lo+1)
                  {
                     ++val;
                     dp->stack[sp].end = 1;
                  }

                  else
                  {
                     dp->stack[sp].hi = hi = val;
                     dp->stack[sp].hi_size = best_size;
                     val = (lo + val) / 2;
                  }
               }

               else if (lo_size >= best_size && best_size >= hi_size)
               {
                  /* Monotonically decreasing size; this is the expected case.
                   * Select the high end of the range.  As above, val may be
                   * hi-1.
                   */
                  if (val == hi-1)
                  {
                     --val;
                     dp->stack[sp].end = 1;
                  }

                  else
                  {
                     dp->stack[sp].lo = lo = val;
                     dp->stack[sp].lo_size = best_size;
                     val = (val + hi) / 2;
                  }
               }

               /* If both those tests failed 'best_size' is either greater than
                * or less than both lo_size and hi_size.  There is a peak or dip
                * in the curve of sizes from lo to hi and val is on the peak or
                * dip.
                *
                * Because the ranges being searched as so small (level is 1..9,
                * windowBits 8..15, memLevel 1..9) there will only be at most
                * three untested values between lo..val and val..hi, so solve
                * the problem by probing down from hi or up from lo, whichever
                * is the higher.
                *
                * This is the place where 'val' is set to outside the range
                * lo..hi, described as 'probing', though maybe 'narrowing' would
                * be more accurate.
                */
               else if (lo_size <= hi_size) /* down from hi */
               {
                  dp->stack[sp].hi = val;
                  dp->stack[sp].hi_size = best_size;
                  val = --hi;
               }

               else /* up from low */
               {
                  dp->stack[sp].lo = val;
                  dp->stack[sp].lo_size = best_size;
                  val = ++lo;
               }

               /* lo and hi are still the true range limits, check for the end
                * condition.
                */
               assert(hi > lo+1);
               if (hi <= lo+2)
                  dp->stack[sp].end = 1;
            }
         }

         assert(val != dp->stack[sp].best_val); /* should be a new value */
         dp->value[opt] = val;
         dp->stack[sp].best_size = MAX_SIZE;
      }
   }

   else
   {
      /* Increment 'entry' */
      dp->value[opt] = options[opt].values[++entry].value;
      dp->stack[sp].entry = entry;
   }

   set_opt_string(dp, sp);

   if (!search && opt_list_end(dp, opt, entry)) /* end of list */
      dp->stack[sp].end = 1;

   else if (!dp->stack[sp].end) /* still active after all these tests */
      dp->nsp = dp->tsp;
}