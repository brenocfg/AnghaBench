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
struct timespec {unsigned long tv_sec; long tv_nsec; } ;
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mytime (struct timespec*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,long) ; 
 scalar_t__ read_png (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 

__attribute__((used)) static int perform_one_test(FILE *fp, int nfiles, png_int_32 transforms)
{
   int i;
   struct timespec before, after;

   /* Clear out all errors: */
   rewind(fp);

   if (mytime(&before))
   {
      for (i=0; i<nfiles; ++i)
      {
         if (read_png(fp, transforms, NULL/*write*/))
         {
            if (ferror(fp))
            {
               perror("temporary file");
               fprintf(stderr, "file %d: error reading PNG data\n", i);
               return 0;
            }
         }

         else
         {
            perror("temporary file");
            fprintf(stderr, "file %d: error from libpng\n", i);
            return 0;
         }
      }
   }

   else
      return 0;

   if (mytime(&after))
   {
      /* Work out the time difference and print it - this is the only output,
       * so flush it immediately.
       */
      unsigned long s = after.tv_sec - before.tv_sec;
      long ns = after.tv_nsec - before.tv_nsec;

      if (ns < 0)
      {
         --s;
         ns += 1000000000;

         if (ns < 0)
         {
            fprintf(stderr, "timepng: bad clock from kernel\n");
            return 0;
         }
      }

      printf("%lu.%.9ld\n", s, ns);
      fflush(stdout);
      if (ferror(stdout))
      {
         fprintf(stderr, "timepng: error writing output\n");
         return 0;
      }

      /* Successful return */
      return 1;
   }

   else
      return 0;
}