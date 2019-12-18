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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  display ;
struct TYPE_2__ {scalar_t__ keep; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ PNG_HANDLE_CHUNK_AS_DEFAULT ; 
 int PNG_INFO_IDAT ; 
 int check (int /*<<< orphan*/ *,int,char const**,int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_error (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  check_handling (int /*<<< orphan*/ *,int,int,int,int,char*,int) ; 
 TYPE_1__* chunk_info ; 
 int /*<<< orphan*/  clear_keep () ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
perform_one_test(FILE *fp, int argc, const char **argv,
   png_uint_32 *default_flags, display *d, int set_callback)
{
   int def;
   png_uint_32 flags[2][4];

   rewind(fp);
   clear_keep();
   memcpy(flags[0], default_flags, sizeof flags[0]);

   def = check(fp, argc, argv, flags[1], d, set_callback);

   /* If IDAT is being handled as unknown the image read is skipped and all the
    * IDATs after the first end up in the end info struct, so in this case add
    * IDAT to the list of unknowns.  (Do this after 'check' above sets the
    * chunk_info 'keep' fields.)
    *
    * Note that the flag setting has to be in the 'known' field to avoid
    * triggering the consistency check below and the flag must only be set if
    * there are multiple IDATs, so if the check above did find an unknown IDAT
    * after IDAT.
    */
   if (chunk_info[0/*IDAT*/].keep != PNG_HANDLE_CHUNK_AS_DEFAULT &&
       (flags[1][3] & PNG_INFO_IDAT) != 0)
      flags[0][2] |= PNG_INFO_IDAT;

   /* Chunks should either be known or unknown, never both and this should apply
    * whether the chunk is before or after the IDAT (actually, the app can
    * probably change this by swapping the handling after the image, but this
    * test does not do that.)
    */
   check_error(d, (flags[0][0]|flags[0][2]) & (flags[0][1]|flags[0][3]),
      "chunk handled inconsistently in count tests");
   check_error(d, (flags[1][0]|flags[1][2]) & (flags[1][1]|flags[1][3]),
      "chunk handled inconsistently in option tests");

   /* Now find out what happened to each chunk before and after the IDAT and
    * determine if the behavior was correct.  First some basic sanity checks,
    * any known chunk should be known in the original count, any unknown chunk
    * should be either known or unknown in the original.
    */
   {
      png_uint_32 test;

      test = flags[1][0] & ~flags[0][0];
      check_error(d, test, "new known chunk before IDAT");
      test = flags[1][1] & ~(flags[0][0] | flags[0][1]);
      check_error(d, test, "new unknown chunk before IDAT");
      test = flags[1][2] & ~flags[0][2];
      check_error(d, test, "new known chunk after IDAT");
      test = flags[1][3] & ~(flags[0][2] | flags[0][3]);
      check_error(d, test, "new unknown chunk after IDAT");
   }

   /* Now each chunk in the original list should have been handled according to
    * the options set for that chunk, regardless of whether libpng knows about
    * it or not.
    */
   check_handling(d, def, flags[0][0] | flags[0][1], flags[1][0], flags[1][1],
      "before IDAT", set_callback);
   check_handling(d, def, flags[0][2] | flags[0][3], flags[1][2], flags[1][3],
      "after IDAT", set_callback);
}