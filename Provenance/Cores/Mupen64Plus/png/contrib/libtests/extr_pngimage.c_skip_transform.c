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
struct display {int options; char* filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFORMATION ; 
 int LOG_SKIPPED ; 
 int SKIP_BUGS ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int first_transform (int) ; 
 scalar_t__ is_bad_combo (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* transform_name (int) ; 

__attribute__((used)) static int
skip_transform(struct display *dp, int tr)
   /* Helper to test for a bad combo and log it if it is skipped */
{
   if ((dp->options & SKIP_BUGS) != 0 && is_bad_combo(tr))
   {
      /* Log this to stdout if logging is on, otherwise just do an information
       * display_log.
       */
      if ((dp->options & LOG_SKIPPED) != 0)
      {
         printf("SKIP: %s transforms ", dp->filename);

         while (tr != 0)
         {
            int next = first_transform(tr);
            tr &= ~next;

            printf("%s", transform_name(next));
            if (tr != 0)
               putchar('+');
         }

         putchar('\n');
      }

      else
         display_log(dp, INFORMATION, "%s: skipped known bad combo 0x%x",
            dp->filename, tr);

      return 1; /* skip */
   }

   return 0; /* don't skip */
}