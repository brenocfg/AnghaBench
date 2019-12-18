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
typedef  int /*<<< orphan*/  fullpath ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_TYPE_IMAGEVIEWER ; 
 int PATH_MAX_LENGTH ; 
 int default_action_ok_load_content_with_core_from_menu (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_list_get_last (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char const*,char const*,int) ; 
 int /*<<< orphan*/ * menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 

__attribute__((used)) static int action_ok_file_load_imageviewer(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   char fullpath[PATH_MAX_LENGTH];
   const char *menu_path           = NULL;
   file_list_t *menu_stack         = menu_entries_get_menu_stack_ptr(0);

   file_list_get_last(menu_stack, &menu_path, NULL, NULL, NULL);

   fullpath[0] = '\0';

   if (!string_is_empty(menu_path))
      fill_pathname_join(fullpath, menu_path, path,
            sizeof(fullpath));

   return default_action_ok_load_content_with_core_from_menu(fullpath, CORE_TYPE_IMAGEVIEWER);
}