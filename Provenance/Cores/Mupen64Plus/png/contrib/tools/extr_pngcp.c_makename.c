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
struct display {char* namebuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERNAL_ERROR ; 
 int /*<<< orphan*/  USER_ERROR ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isdir (struct display*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static void
makename(struct display *dp, const char *dir, const char *infile)
{
   /* Make a name for an output file (and check it). */
   dp->namebuf[0] = 0;

   if (dir == NULL || infile == NULL)
      display_log(dp, INTERNAL_ERROR, "NULL name to makename");

   else
   {
      size_t dsize = strlen(dir);

      if (dsize <= (sizeof dp->namebuf)-2) /* Allow for name + '/' + '\0' */
      {
         size_t isize = strlen(infile);
         size_t istart = isize-1;

         /* This should fail before here: */
         if (infile[istart] == '/')
            display_log(dp, INTERNAL_ERROR, "infile with trailing /");

         memcpy(dp->namebuf, dir, dsize);
         if (dsize > 0 && dp->namebuf[dsize-1] != '/')
            dp->namebuf[dsize++] = '/';

         /* Find the rightmost non-/ character: */
         while (istart > 0 && infile[istart-1] != '/')
            --istart;

         isize -= istart;
         infile += istart;

         if (dsize+isize < (sizeof dp->namebuf)) /* dsize + infile + '\0' */
         {
            memcpy(dp->namebuf+dsize, infile, isize+1);

            if (isdir(dp, dp->namebuf))
               display_log(dp, USER_ERROR, "%s: output file is a directory",
                     dp->namebuf);
         }

         else
         {
            dp->namebuf[dsize] = 0; /* allowed for: -2 at start */
            display_log(dp, USER_ERROR, "%s%s: output file name too long",
                  dp->namebuf, infile);
         }
      }

      else
         display_log(dp, USER_ERROR, "%s: output directory name too long", dir);
   }
}