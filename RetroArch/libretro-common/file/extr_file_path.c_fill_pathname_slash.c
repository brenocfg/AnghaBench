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
 char* find_last_slash (char*) ; 
 int /*<<< orphan*/  path_default_slash () ; 
 int /*<<< orphan*/  strlcat (char*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char*) ; 

void fill_pathname_slash(char *path, size_t size)
{
   size_t path_len;
   const char *last_slash = find_last_slash(path);

   if (!last_slash)
   {
      strlcat(path, path_default_slash(), size);
      return;
   }

   path_len               = strlen(path);
   /* Try to preserve slash type. */
   if (last_slash != (path + path_len - 1))
   {
      path[path_len]   = last_slash[0];
      path[path_len+1] = '\0';
   }
}