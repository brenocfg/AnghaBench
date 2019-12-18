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
 int MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR ; 
 int /*<<< orphan*/  MSG_EXTERNAL_APPLICATION_DIR ; 
 int MSG_UNKNOWN ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int frontend_gx_parse_drive_list(void *data, bool load_content)
{
#ifndef IS_SALAMANDER
   file_list_t *list = (file_list_t*)data;
   enum msg_hash_enums enum_idx = load_content ?
      MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR :
      MSG_UNKNOWN;
#ifdef HW_RVL
   menu_entries_append_enum(list,
         "sd:/",
         msg_hash_to_str(MSG_EXTERNAL_APPLICATION_DIR),
         enum_idx,
         FILE_TYPE_DIRECTORY, 0, 0);
   menu_entries_append_enum(list,
         "usb:/",
         msg_hash_to_str(MSG_EXTERNAL_APPLICATION_DIR),
         enum_idx,
         FILE_TYPE_DIRECTORY, 0, 0);
#endif
   menu_entries_append_enum(list,
         "carda:/",
         msg_hash_to_str(MSG_EXTERNAL_APPLICATION_DIR),
         enum_idx,
         FILE_TYPE_DIRECTORY, 0, 0);
   menu_entries_append_enum(list,
         "cardb:/",
         msg_hash_to_str(MSG_EXTERNAL_APPLICATION_DIR),
         enum_idx,
         FILE_TYPE_DIRECTORY, 0, 0);
#endif

   return 0;
}