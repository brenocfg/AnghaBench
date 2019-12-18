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
typedef  int /*<<< orphan*/  user_data_path ;
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
typedef  int /*<<< orphan*/  base_path ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TYPE_DIRECTORY ; 
 scalar_t__ INTERNAL_STORAGE_WRITABLE ; 
 int MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR ; 
 int MSG_APPLICATION_DIR ; 
 int MSG_EXTERNAL_APPLICATION_DIR ; 
 int MSG_INTERNAL_STORAGE ; 
 int MSG_REMOVABLE_STORAGE ; 
 int MSG_UNKNOWN ; 
 int PATH_MAX ; 
 int PATH_MAX_LENGTH ; 
 char* app_dir ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char*,int) ; 
 char* getenv (char*) ; 
 char* internal_storage_app_path ; 
 char* internal_storage_path ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int) ; 
 scalar_t__ path_is_directory (char*) ; 
 scalar_t__ storage_permissions ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static int frontend_unix_parse_drive_list(void *data, bool load_content)
{
#ifdef HAVE_MENU
   file_list_t *list = (file_list_t*)data;
   enum msg_hash_enums enum_idx = load_content ?
      MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR :
      MSG_UNKNOWN;

#ifdef ANDROID
   if (!string_is_empty(internal_storage_path))
   {
      if (storage_permissions == INTERNAL_STORAGE_WRITABLE)
      {
         char user_data_path[PATH_MAX_LENGTH];
         fill_pathname_join(user_data_path,
               internal_storage_path, "RetroArch",
               sizeof(user_data_path));

         menu_entries_append_enum(list,
               user_data_path,
               msg_hash_to_str(MSG_INTERNAL_STORAGE),
               enum_idx,
               FILE_TYPE_DIRECTORY, 0, 0);
      }

      menu_entries_append_enum(list,
            internal_storage_path,
            msg_hash_to_str(MSG_INTERNAL_STORAGE),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
   else
   {
      menu_entries_append_enum(list,
            "/storage/emulated/0",
            msg_hash_to_str(MSG_REMOVABLE_STORAGE),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
   menu_entries_append_enum(list,
         "/storage",
         msg_hash_to_str(MSG_REMOVABLE_STORAGE),
         enum_idx,
         FILE_TYPE_DIRECTORY, 0, 0);
   if (!string_is_empty(internal_storage_app_path))
   {
      menu_entries_append_enum(list,
            internal_storage_app_path,
            msg_hash_to_str(MSG_EXTERNAL_APPLICATION_DIR),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
   if (!string_is_empty(app_dir))
   {
      menu_entries_append_enum(list,
            app_dir,
            msg_hash_to_str(MSG_APPLICATION_DIR),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
#else
   char base_path[PATH_MAX] = {0};
   const char *xdg          = getenv("XDG_CONFIG_HOME");
   const char *home         = getenv("HOME");

   if (xdg)
   {
      strlcpy(base_path, xdg, sizeof(base_path));
      strlcat(base_path, "/retroarch", sizeof(base_path));
   }
   else if (home)
   {
      strlcpy(base_path, home, sizeof(base_path));
      strlcat(base_path, "/.config/retroarch", sizeof(base_path));
   }

   if(!string_is_empty(base_path))
   {
      menu_entries_append_enum(list, base_path,
            msg_hash_to_str(MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
   if (!string_is_empty(home))
   {
      menu_entries_append_enum(list, home,
            msg_hash_to_str(MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
   if (path_is_directory("/media"))
   {
      menu_entries_append_enum(list, "/media",
            msg_hash_to_str(MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
   if (path_is_directory("/mnt"))
   {
      menu_entries_append_enum(list, "/mnt",
            msg_hash_to_str(MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
   }
#endif

   menu_entries_append_enum(list, "/",
         msg_hash_to_str(MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR),
         enum_idx,
         FILE_TYPE_DIRECTORY, 0, 0);
#endif

   return 0;
}