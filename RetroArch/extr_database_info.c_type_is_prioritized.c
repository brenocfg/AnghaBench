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
 char* path_get_extension (char const*) ; 
 scalar_t__ string_is_equal_noncase (char const*,char*) ; 

__attribute__((used)) static bool type_is_prioritized(const char *path)
{
   const char *ext = path_get_extension(path);
   if (string_is_equal_noncase(ext, "cue"))
      return true;
   if (string_is_equal_noncase(ext, "gdi"))
      return true;
   return false;
}