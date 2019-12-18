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
 int /*<<< orphan*/  fill_pathname_slash (char*,size_t) ; 
 size_t strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

size_t fill_pathname_join(char *out_path,
      const char *dir, const char *path, size_t size)
{
   if (out_path != dir)
      strlcpy(out_path, dir, size);

   if (*out_path)
      fill_pathname_slash(out_path, size);

   return strlcat(out_path, path, size);
}