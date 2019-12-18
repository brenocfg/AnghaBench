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
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_CONTENT_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_CORE_CONTENT_DIRS_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_CORE_CONTENT_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DEFERRED_CORE_UPDATER_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DOWNLOAD_CORE_CONTENT_DIRS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ONLINE_UPDATER ; 
 int /*<<< orphan*/  menu_entries_flush_stack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_get_last_stack (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_cancel_core_content(const char *path,
      const char *label, unsigned type, size_t idx)
{
   const char *menu_label              = NULL;

   menu_entries_get_last_stack(NULL, &menu_label, NULL, NULL, NULL);

   if (string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_CORE_UPDATER_LIST)))
      menu_entries_flush_stack(msg_hash_to_str(MENU_ENUM_LABEL_ONLINE_UPDATER), 0);
   else if (string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_CORE_CONTENT_DIRS_LIST)))
      menu_entries_flush_stack(msg_hash_to_str(MENU_ENUM_LABEL_ONLINE_UPDATER), 0);
   else if (string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_DOWNLOAD_CORE_CONTENT_DIRS)))
      menu_entries_flush_stack(msg_hash_to_str(MENU_ENUM_LABEL_ONLINE_UPDATER), 0);
   else if (string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_DEFERRED_CORE_CONTENT_LIST)))
      menu_entries_flush_stack(msg_hash_to_str(MENU_ENUM_LABEL_ONLINE_UPDATER), 0);
   else
      menu_entries_flush_stack(msg_hash_to_str(MENU_ENUM_LABEL_ADD_CONTENT_LIST), 0);

   return 0;
}