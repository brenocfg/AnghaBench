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
 int /*<<< orphan*/  fill_pathname_basedir (char*,char const*,size_t) ; 
 scalar_t__ path_is_absolute (char const*) ; 
 int /*<<< orphan*/  path_resolve_realpath (char*,size_t,int) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

void fill_pathname_resolve_relative(char *out_path,
      const char *in_refpath, const char *in_path, size_t size)
{
   if (path_is_absolute(in_path))
   {
      strlcpy(out_path, in_path, size);
      return;
   }

   fill_pathname_basedir(out_path, in_refpath, size);
   strlcat(out_path, in_path, size);
   path_resolve_realpath(out_path, size, false);
}