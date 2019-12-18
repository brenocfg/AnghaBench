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
struct display {unsigned int tsp; size_t min_windowBits; unsigned int nsp; TYPE_2__* stack; int /*<<< orphan*/ * value; } ;
typedef  size_t png_byte ;
struct TYPE_6__ {size_t value_count; int /*<<< orphan*/  name; TYPE_1__* values; } ;
struct TYPE_5__ {size_t opt; size_t entry; int end; int /*<<< orphan*/  best_val; int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; int /*<<< orphan*/  hi_size; int /*<<< orphan*/  lo_size; int /*<<< orphan*/  best_size; } ;
struct TYPE_4__ {char* name; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_WARNING ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  MAX_SIZE ; 
 unsigned int SL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ opt_list_end (struct display*,size_t,size_t) ; 
 TYPE_3__* options ; 
 char* range_hi ; 
 char const* range_lo ; 
 int /*<<< orphan*/  set_opt_string (struct display*,unsigned int) ; 
 int /*<<< orphan*/  text_stash (struct display*) ; 

__attribute__((used)) static void
push_opt(struct display *dp, unsigned int sp, png_byte opt, int search)
   /* Push a new option onto the stack, initializing the new stack entry
    * appropriately; this does all the work of next_opt (setting end/nsp) for
    * the first entry in the list.
    */
{
   png_byte entry;
   const char *entry_name;

   assert(sp == dp->tsp && sp < SL);

   /* The starting entry is entry 0 unless there is a range in which case it is
    * the entry corresponding to range_lo:
    */
   entry = options[opt].value_count;
   assert(entry > 0U);

   do
   {
      entry_name = options[opt].values[--entry].name;
      if (entry_name == range_lo)
         break;
   }
   while (entry > 0U);

   dp->tsp = sp+1U;
   dp->stack[sp].best_size =
      dp->stack[sp].lo_size =
      dp->stack[sp].hi_size = MAX_SIZE;

   if (search && entry_name == range_lo) /* search this range */
   {
      dp->stack[sp].lo = options[opt].values[entry].value;
      /* check for a mal-formed RANGE above: */
      assert(entry+1 < options[opt].value_count &&
             options[opt].values[entry+1].name == range_hi);
      dp->stack[sp].hi = options[opt].values[entry+1].value;
   }

   else
   {
      /* next_opt will just iterate over the range. */
      dp->stack[sp].lo = INT_MAX;
      dp->stack[sp].hi = INT_MIN; /* Prevent range chop */
   }

   dp->stack[sp].opt = opt;
   dp->stack[sp].entry = entry;
   dp->stack[sp].best_val = dp->value[opt] = options[opt].values[entry].value;

   set_opt_string(dp, sp);

   /* This works for the search case too; if the range has only one entry 'end'
    * will be marked here.
    */
   if (opt_list_end(dp, opt, entry))
   {
      dp->stack[sp].end = 1;
      /* Skip the warning if pngcp did this itself.  See the code in
       * set_windowBits_hi.
       */
      if (opt != dp->min_windowBits)
         display_log(dp, APP_WARNING, "%s: only testing one value",
               options[opt].name);
   }

   else
   {
      dp->stack[sp].end = 0;
      dp->nsp = dp->tsp;
   }

   /* Do a lazy cache of the text chunks for libpng 1.6 and earlier; this is
    * because they can only be written once(!) so if we are going to re-use the
    * png_info we need a copy.
    */
   text_stash(dp);
}