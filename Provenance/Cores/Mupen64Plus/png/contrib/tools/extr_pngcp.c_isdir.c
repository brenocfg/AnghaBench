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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct display {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USER_ERROR ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_log (struct display*,int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int
isdir(struct display *dp, const char *pathname)
{
   if (pathname == NULL)
      return 0; /* stdout */

   else if (pathname[0] == 0)
      return 1; /* empty string */

   else
   {
      struct stat buf;
      int ret = stat(pathname, &buf);

      if (ret == 0) /* the entry exists */
      {
         if (S_ISDIR(buf.st_mode))
            return 1;

         /* Else expect an object that exists and can be written: */
         if (access(pathname, W_OK) != 0)
            display_log(dp, USER_ERROR, "%s: cannot be written (%s)", pathname,
                  strerror(errno));

         return 0; /* file (exists, can be written) */
      }

      else /* an error */
      {
         /* Non-existence is fine, other errors are not: */
         if (errno != ENOENT)
            display_log(dp, USER_ERROR, "%s: invalid output name (%s)",
                  pathname, strerror(errno));

         return 0; /* file (does not exist) */
      }
   }
}