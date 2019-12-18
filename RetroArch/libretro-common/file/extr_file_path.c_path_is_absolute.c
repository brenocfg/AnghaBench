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

/* Variables and functions */
 char const* strstr (char const*,char*) ; 

bool path_is_absolute(const char *path)
{
   if (path[0] == '/')
      return true;
#ifdef _WIN32
   /* Many roads lead to Rome ... */
   if ((    strstr(path, "\\\\") == path)
         || strstr(path, ":/")
         || strstr(path, ":\\")
         || strstr(path, ":\\\\"))
      return true;
#elif defined(__wiiu__)
   if (strstr(path, ":/"))
      return true;
#endif
   return false;
}