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
typedef  int /*<<< orphan*/  file_list_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TYPE_DIRECTORY ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_OPEN_PICKER ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_OPEN_UWP_PERMISSIONS ; 
 int MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR ; 
 int MENU_ENUM_LABEL_VALUE_FILE_BROWSER_OPEN_PICKER ; 
 int MENU_ENUM_LABEL_VALUE_FILE_BROWSER_OPEN_UWP_PERMISSIONS ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION ; 
 int MSG_UNKNOWN ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  fill_pathname_home_dir (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* msg_hash_to_str (int) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uwp_device_family ; 
 scalar_t__ uwp_drive_exists (char*) ; 

__attribute__((used)) static int frontend_uwp_parse_drive_list(void *data, bool load_content)
{
#ifdef HAVE_MENU
   file_list_t            *list = (file_list_t*)data;
   enum msg_hash_enums enum_idx = load_content ?
         MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR :
         MSG_UNKNOWN;
   char drive[]                 = " :\\";
   char *home_dir               = (char*)malloc(PATH_MAX_LENGTH * sizeof(char));
   bool have_any_drives         = false;

   fill_pathname_home_dir(home_dir, PATH_MAX_LENGTH * sizeof(char));

   for (drive[0] = 'A'; drive[0] <= 'Z'; drive[0]++)
   {
      if (uwp_drive_exists(drive))
      {
         menu_entries_append_enum(list,
            drive,
            msg_hash_to_str(MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR),
            enum_idx,
            FILE_TYPE_DIRECTORY, 0, 0);
         have_any_drives = true;
      }
   }

   menu_entries_append_enum(list,
      home_dir,
      msg_hash_to_str(MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR),
      enum_idx,
      FILE_TYPE_DIRECTORY, 0, 0);

   if (!have_any_drives)
   {
      menu_entries_append_enum(list,
         msg_hash_to_str(MENU_ENUM_LABEL_VALUE_FILE_BROWSER_OPEN_PICKER),
         msg_hash_to_str(MENU_ENUM_LABEL_FILE_BROWSER_OPEN_PICKER),
         MENU_ENUM_LABEL_FILE_BROWSER_OPEN_PICKER,
         MENU_SETTING_ACTION, 0, 0);

      if (string_is_equal(uwp_device_family, "Windows.Desktop"))
      {
         menu_entries_append_enum(list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_FILE_BROWSER_OPEN_UWP_PERMISSIONS),
            msg_hash_to_str(MENU_ENUM_LABEL_FILE_BROWSER_OPEN_UWP_PERMISSIONS),
            MENU_ENUM_LABEL_FILE_BROWSER_OPEN_UWP_PERMISSIONS,
            MENU_SETTING_ACTION, 0, 0);
      }
   }

   free(home_dir);
#endif

   return 0;
}