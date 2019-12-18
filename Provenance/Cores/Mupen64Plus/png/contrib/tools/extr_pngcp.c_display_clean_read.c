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
struct display {int /*<<< orphan*/ * fp; int /*<<< orphan*/ * read_pp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_destroy_read_struct (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
display_clean_read(struct display *dp)
{
   if (dp->read_pp != NULL)
      png_destroy_read_struct(&dp->read_pp, NULL, NULL);

   if (dp->fp != NULL)
   {
      FILE *fp = dp->fp;
      dp->fp = NULL;
      (void)fclose(fp);
   }
}