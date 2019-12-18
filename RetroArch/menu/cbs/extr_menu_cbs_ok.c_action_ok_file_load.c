#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rarch_setting_t ;
typedef  int /*<<< orphan*/  menu_path_new ;
struct TYPE_3__ {char* scratch2_buf; char const* scratch_buf; } ;
typedef  TYPE_1__ menu_handle_t ;
typedef  int /*<<< orphan*/  full_path_new ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_TYPE_PLAIN ; 
 scalar_t__ FILEBROWSER_SELECT_FILE_SUBSYSTEM ; 
#define  FILE_TYPE_IN_CARCHIVE 128 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE ; 
 int /*<<< orphan*/  MENU_SETTINGS ; 
 int PATH_MAX_LENGTH ; 
 scalar_t__ ST_PATH ; 
 int action_ok_set_path (char const*,char const*,unsigned int,size_t,size_t) ; 
 int /*<<< orphan*/  content_add_subsystem (char*) ; 
 int default_action_ok_load_content_with_core_from_menu (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_list_get_last (int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ filebrowser_get_type () ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char const*,int) ; 
 int /*<<< orphan*/  fill_pathname_join_delim (char*,char*,char const*,char,int) ; 
 int menu_cbs_exit () ; 
 TYPE_1__* menu_driver_get_ptr () ; 
 int /*<<< orphan*/  menu_entries_flush_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * menu_entries_get_menu_stack_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * menu_setting_find (char const*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ setting_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int action_ok_file_load(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   char menu_path_new[PATH_MAX_LENGTH];
   char full_path_new[PATH_MAX_LENGTH];
   const char *menu_label              = NULL;
   const char *menu_path               = NULL;
   rarch_setting_t *setting            = NULL;
   file_list_t  *menu_stack            = menu_entries_get_menu_stack_ptr(0);

   menu_path_new[0] = full_path_new[0] = '\0';

   if (filebrowser_get_type() == FILEBROWSER_SELECT_FILE_SUBSYSTEM)
   {
      /* TODO/FIXME - this path is triggered when we try to load a
       * file from an archive while inside the load subsystem
       * action */
      menu_handle_t *menu                 = menu_driver_get_ptr();
      if (!menu)
         return menu_cbs_exit();

      fill_pathname_join(menu_path_new,
            menu->scratch2_buf, menu->scratch_buf,
            sizeof(menu_path_new));
      switch (type)
      {
         case FILE_TYPE_IN_CARCHIVE:
            fill_pathname_join_delim(full_path_new, menu_path_new, path,
                  '#',sizeof(full_path_new));
            break;
         default:
            fill_pathname_join(full_path_new, menu_path_new, path,
                  sizeof(full_path_new));
            break;
      }

      content_add_subsystem(full_path_new);
      menu_entries_flush_stack(NULL, MENU_SETTINGS);
      return 0;
   }

   file_list_get_last(menu_stack, &menu_path, &menu_label, NULL, NULL);

   if (!string_is_empty(menu_label))
      setting = menu_setting_find(menu_label);

   if (setting_get_type(setting) == ST_PATH)
      return action_ok_set_path(path, label, type, idx, entry_idx);

   if (!string_is_empty(menu_path))
      strlcpy(menu_path_new, menu_path, sizeof(menu_path_new));

   if (!string_is_empty(menu_label))
   {
      if (
            string_is_equal(menu_label,
               msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE)) ||
            string_is_equal(menu_label,
               msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN))
         )
      {
         menu_handle_t *menu                 = menu_driver_get_ptr();
         if (!menu)
            return menu_cbs_exit();

         fill_pathname_join(menu_path_new,
               menu->scratch2_buf, menu->scratch_buf,
               sizeof(menu_path_new));
      }
   }

   switch (type)
   {
      case FILE_TYPE_IN_CARCHIVE:
         fill_pathname_join_delim(full_path_new, menu_path_new, path,
               '#',sizeof(full_path_new));
         break;
      default:
         fill_pathname_join(full_path_new, menu_path_new, path,
               sizeof(full_path_new));
         break;
   }

   return default_action_ok_load_content_with_core_from_menu(full_path_new,
         CORE_TYPE_PLAIN);
}