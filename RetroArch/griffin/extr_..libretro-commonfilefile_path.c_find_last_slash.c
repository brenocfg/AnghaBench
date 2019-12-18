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
 char* strrchr (char const*,char) ; 

char *find_last_slash(const char *str)
{
   const char *slash     = strrchr(str, '/');
#ifdef _WIN32
   const char *backslash = strrchr(str, '\\');

   if (!slash || (backslash > slash))
      return (char*)backslash;
#endif
   return (char*)slash;
}