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
 size_t strlcat (char*,char const*,size_t) ; 
 size_t strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

size_t fill_pathname_join_delim(char *out_path, const char *dir,
      const char *path, const char delim, size_t size)
{
   size_t copied;
   /* behavior of strlcpy is undefined if dst and src overlap */
   if (out_path == dir)
      copied = strlen(dir);
   else
      copied = strlcpy(out_path, dir, size);

   out_path[copied]   = delim;
   out_path[copied+1] = '\0';

   if (path)
      copied = strlcat(out_path, path, size);
   return copied;
}