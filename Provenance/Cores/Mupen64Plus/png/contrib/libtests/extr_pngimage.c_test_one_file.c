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
struct display {char* operation; scalar_t__ ignored_transforms; unsigned int active_transforms; int options; char* filename; int /*<<< orphan*/  written_file; int /*<<< orphan*/  read_ip; int /*<<< orphan*/  original_file; int /*<<< orphan*/  original_ip; scalar_t__ transforms; } ;

/* Variables and functions */
 int EXHAUSTIVE ; 
 int FIND_BAD_COMBOS ; 
 int SKIP_BUGS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compare_read (struct display*,unsigned int) ; 
 int /*<<< orphan*/  display_cache_file (struct display*,char const*) ; 
 unsigned int first_transform (unsigned int) ; 
 scalar_t__ is_combo (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  read_png (struct display*,int /*<<< orphan*/ *,char*,unsigned int) ; 
 unsigned int read_transforms ; 
 unsigned int rw_transforms ; 
 scalar_t__ skip_transform (struct display*,unsigned int) ; 
 int /*<<< orphan*/  update_display (struct display*) ; 
 int /*<<< orphan*/  write_png (struct display*,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int write_transforms ; 

__attribute__((used)) static void
test_one_file(struct display *dp, const char *filename)
{
   /* First cache the file and update the display original file
    * information for the new file.
    */
   dp->operation = "cache file";
   dp->transforms = 0;
   display_cache_file(dp, filename);
   update_display(dp);

   /* First test: if there are options that should be ignored for this file
    * verify that they really are ignored.
    */
   if (dp->ignored_transforms != 0)
   {
      read_png(dp, &dp->original_file, "ignored transforms",
         dp->ignored_transforms);

      /* The result should be identical to the original_rows */
      if (!compare_read(dp, 0/*transforms applied*/))
         return; /* no point testing more */
   }

#ifdef PNG_WRITE_PNG_SUPPORTED
   /* Second test: write the original PNG data out to a new file (to test the
    * write side) then read the result back in and make sure that it hasn't
    * changed.
    */
   dp->operation = "write";
   write_png(dp, dp->original_ip, 0/*transforms*/);
   read_png(dp, &dp->written_file, NULL, 0/*transforms*/);
   if (!compare_read(dp, 0/*transforms applied*/))
      return;
#endif

   /* Third test: the active options.  Test each in turn, or, with the
    * EXHAUSTIVE option, test all possible combinations.
    */
   {
      /* Use unsigned int here because the code below to increment through all
       * the possibilities exhaustively has to use a compare and that must be
       * unsigned, because some transforms are negative on a 16-bit system.
       */
      unsigned int active = dp->active_transforms;
      const int exhaustive = (dp->options & EXHAUSTIVE) != 0;
      unsigned int current = first_transform(active);
      unsigned int bad_transforms = 0;
      unsigned int bad_combo = ~0U;    /* bitwise AND of failing transforms */
      unsigned int bad_combo_list = 0; /* bitwise OR of failures */

      for (;;)
      {
         read_png(dp, &dp->original_file, "active transforms", current);

         /* If this involved any irreversible transformations then if we write
          * it out with just the reversible transformations and read it in again
          * with the same transforms we should get the same thing.  At present
          * this isn't done - it just seems like a waste of time and it would
          * require two sets of read png_struct/png_info.
          *
          * If there were no irreversible transformations then if we write it
          * out and read it back in again (without the reversible transforms)
          * we should get back to the place where we started.
          */
#ifdef PNG_WRITE_PNG_SUPPORTED
         if ((current & write_transforms) == current)
         {
            /* All transforms reversible: write the PNG with the transformations
             * reversed, then read it back in with no transformations.  The
             * result should be the same as the original apart from the loss of
             * low order bits because of the SHIFT/sBIT transform.
             */
            dp->operation = "reversible transforms";
            write_png(dp, dp->read_ip, current);

            /* And if this is read back in, because all the transformations were
             * reversible, the result should be the same.
             */
            read_png(dp, &dp->written_file, NULL, 0);
            if (!compare_read(dp, current/*for the SHIFT/sBIT transform*/))
            {
               /* This set of transforms failed.  If a single bit is set - if
                * there is just one transform - don't include this in further
                * 'exhaustive' tests.  Notice that each transform is tested on
                * its own before testing combos in the exhaustive case.
                */
               if (is_combo(current))
               {
                  bad_combo &= current;
                  bad_combo_list |= current;
               }

               else
                  bad_transforms |= current;
            }
         }
#endif

         /* Now move to the next transform */
         if (exhaustive) /* all combinations */
         {
            unsigned int next = current;

            do
            {
               if (next == read_transforms) /* Everything tested */
                  goto combo;

               ++next;
            }  /* skip known bad combos if the relevant option is set; skip
                * combos involving known bad single transforms in all cases.
                */
            while (  (next & read_transforms) <= current
                  || (next & active) == 0 /* skip cases that do nothing */
                  || (next & bad_transforms) != 0
                  || skip_transform(dp, next));

            assert((next & read_transforms) == next);
            current = next;
         }

         else /* one at a time */
         {
            active &= ~current;

            if (active == 0)
               goto combo;

            current = first_transform(active);
         }
      }

combo:
      if (dp->options & FIND_BAD_COMBOS)
      {
         /* bad_combos identifies the combos that occur in all failing cases;
          * bad_combo_list identifies transforms that do not prevent the
          * failure.
          */
         if (bad_combo != ~0U)
            printf("%s[0x%x]: PROBLEM: 0x%x[0x%x] ANTIDOTE: 0x%x\n",
               dp->filename, active, bad_combo, bad_combo_list,
               rw_transforms & ~bad_combo_list);

         else
            printf("%s: no %sbad combos found\n", dp->filename,
               (dp->options & SKIP_BUGS) ? "additional " : "");
      }
   }
}