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
typedef  int /*<<< orphan*/  entry_real_core_path ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  path_resolve_realpath (char*,int,int) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 scalar_t__ string_is_equal_noncase (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static bool playlist_core_path_equal(const char *real_core_path, const char *entry_core_path)
{
   char entry_real_core_path[PATH_MAX_LENGTH];

   entry_real_core_path[0] = '\0';

   /* Sanity check */
   if (string_is_empty(real_core_path) || string_is_empty(entry_core_path))
      return false;

   /* Get entry 'real' core path */
   strlcpy(entry_real_core_path, entry_core_path, sizeof(entry_real_core_path));
   if (!string_is_equal(entry_real_core_path, "DETECT"))
      path_resolve_realpath(entry_real_core_path, sizeof(entry_real_core_path), true);

   if (string_is_empty(entry_real_core_path))
      return false;

#ifdef _WIN32
   /* Handle case-insensitive operating systems*/
   if (string_is_equal_noncase(real_core_path, entry_real_core_path))
      return true;
#else
   if (string_is_equal(real_core_path, entry_real_core_path))
      return true;
#endif

   return false;
}