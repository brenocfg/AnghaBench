#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char** dirs; } ;

/* Variables and functions */
 unsigned int DEFAULT_DIR_LAST ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  fill_pathname_expand_special (char*,char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ g_defaults ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  path_is_directory (char*) ; 
 scalar_t__ path_is_valid (char*) ; 
 int /*<<< orphan*/  path_mkdir (char*) ; 
 scalar_t__ string_is_empty (char const*) ; 

void dir_check_defaults(void)
{
   unsigned i;
   /* early return for people with a custom folder setup
      so it doesn't create unnecessary directories
    */
#if defined(ORBIS) || defined(ANDROID)
   if (path_is_valid("host0:app/custom.ini"))
#else
   if (path_is_valid("custom.ini"))
#endif
      return;

   for (i = 0; i < DEFAULT_DIR_LAST; i++)
   {
      char       *new_path = NULL;
      const char *dir_path = g_defaults.dirs[i];

      if (string_is_empty(dir_path))
         continue;

      new_path = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));

      if (!new_path)
         continue;

      new_path[0] = '\0';
      fill_pathname_expand_special(new_path,
            dir_path,
            PATH_MAX_LENGTH * sizeof(char));

      if (!path_is_directory(new_path))
         path_mkdir(new_path);

      free(new_path);
   }
}