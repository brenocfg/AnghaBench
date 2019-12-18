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
 int /*<<< orphan*/  path_basename (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 scalar_t__ strrchr (int /*<<< orphan*/ ,char) ; 

char *path_remove_extension(char *path)
{
   char *last = !string_is_empty(path)
      ? (char*)strrchr(path_basename(path), '.') : NULL;
   if (!last)
      return NULL;
   if (*last)
      *last = '\0';
   return path;
}