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
struct stat {int dummy; } ;

/* Variables and functions */
 scalar_t__ CheckFile (char*) ; 
 int mkdir (char*,int) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 size_t strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 

int CreateSubfolder(const char * fullpath)
{
   int pos;
   int result = 0;

   if (!fullpath)
      return 0;

   char dirnoslash[strlen(fullpath)+1];
   strcpy(dirnoslash, fullpath);

   pos = strlen(dirnoslash)-1;
   while(dirnoslash[pos] == '/')
   {
      dirnoslash[pos] = '\0';
      pos--;
   }

   if (CheckFile(dirnoslash))
      return 1;

   {
      char parentpath[strlen(dirnoslash)+2];
      size_t copied = strcpy(parentpath, dirnoslash);
      char * ptr    = strrchr(parentpath, '/');

      if (!ptr)
      {
         struct stat filestat;
         /* Device root directory (must be with '/') */
         parentpath[copied]   = '/';
         parentpath[copied+1] = '\0';

         if (stat(parentpath, &filestat) == 0)
            return 1;

         return 0;
      }

      ptr++;
      ptr[0] = '\0';

      result = CreateSubfolder(parentpath);
   }

   if (!result)
      return 0;

   if (mkdir(dirnoslash, 0777) == -1)
      return 0;

   return 1;
}