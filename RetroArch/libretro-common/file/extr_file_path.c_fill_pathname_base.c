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
 char* path_basename (char const*) ; 
 size_t strlcpy (char*,char const*,size_t) ; 

size_t fill_pathname_base(char *out, const char *in_path, size_t size)
{
   const char     *ptr = path_basename(in_path);

   if (!ptr)
      ptr = in_path;

   return strlcpy(out, ptr, size);
}