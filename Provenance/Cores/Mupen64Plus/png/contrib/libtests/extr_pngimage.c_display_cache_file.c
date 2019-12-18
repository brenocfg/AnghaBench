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
struct display {char const* filename; int /*<<< orphan*/  original_file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  APP_ERROR ; 
 int /*<<< orphan*/  USER_ERROR ; 
 int buffer_from_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void
display_cache_file(struct display *dp, const char *filename)
   /* Does the initial cache of the file. */
{
   FILE *fp;
   int ret;

   dp->filename = filename;

   if (filename != NULL)
   {
      fp = fopen(filename, "rb");
      if (fp == NULL)
         display_log(dp, USER_ERROR, "open failed: %s", strerror(errno));
   }

   else
      fp = stdin;

   ret = buffer_from_file(&dp->original_file, fp);

   fclose(fp);

   if (ret != 0)
      display_log(dp, APP_ERROR, "read failed: %s", strerror(ret));
}