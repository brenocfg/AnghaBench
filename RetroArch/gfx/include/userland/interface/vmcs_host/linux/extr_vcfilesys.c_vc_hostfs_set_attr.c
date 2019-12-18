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
typedef  int /*<<< orphan*/  mode_t ;
typedef  int fattributes_t ;

/* Variables and functions */
 int ATTR_RDONLY ; 
 int /*<<< orphan*/  DEBUG_MINOR (char*,char const*,int) ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  backslash_to_slash (char*) ; 
 scalar_t__ chmod (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 char* strdup (char const*) ; 

int vc_hostfs_set_attr(const char *path, fattributes_t attr)
{
   char *pathbuf = strdup(path);
   int ret = -1;

   DEBUG_MINOR( "vc_hostfs_set_attr: '%s', %x", path, attr );

   if (pathbuf)
   {
      mode_t mode = 0;
      struct stat sb;

      backslash_to_slash(pathbuf);

      if ( stat( path, &sb ) == 0 )
      {
         mode = sb.st_mode;

         if ( attr & ATTR_RDONLY )
         {
            mode &= ~S_IWUSR;
         }
         else
         {
            mode |= S_IWUSR;
         }

         /* coverity[toctou] Not doing anything security-relevant here,
          * so the race condition is harmless */
         if ( chmod( path, mode ) == 0 )
            ret = 0;
      }
   }

   if (pathbuf)
      free(pathbuf);

   return ret;
}