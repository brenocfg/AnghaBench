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
 int /*<<< orphan*/  path_is_absolute (char*) ; 

__attribute__((used)) static void make_relative_path_portable(char *path)
{
#ifdef _WIN32
   /* use '/' instead of '\' for maximum portability */
   if (!path_is_absolute(path))
   {
      char *p;
      for (p = path; *p; p++)
         if (*p == '\\')
            *p = '/';
   }
#endif
}