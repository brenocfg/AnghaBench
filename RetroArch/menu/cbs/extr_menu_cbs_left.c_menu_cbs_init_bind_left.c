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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_LEFT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HISTORY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_IMAGES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MAIN_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MUSIC_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NETPLAY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLISTS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_TAB ; 
 unsigned int MENU_SETTING_NO_ITEM ; 
 int /*<<< orphan*/  action_left_mainmenu ; 
 int /*<<< orphan*/  bind_left_generic ; 
 scalar_t__ menu_cbs_init_bind_left_compare_label (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ menu_cbs_init_bind_left_compare_type (int /*<<< orphan*/ *,unsigned int,char const*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 

int menu_cbs_init_bind_left(menu_file_list_cbs_t *cbs,
      const char *path, const char *label, unsigned type, size_t idx,
      const char *menu_label,
      uint32_t label_hash)
{
   if (!cbs)
      return -1;

   BIND_ACTION_LEFT(cbs, bind_left_generic);

   if (type == MENU_SETTING_NO_ITEM)
   {
      if (  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_HISTORY_TAB))   ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_FAVORITES_TAB)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_ADD_TAB)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_NETPLAY_TAB)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_MAIN_MENU)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_MUSIC_TAB)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_IMAGES_TAB)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_VIDEO_TAB)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_HORIZONTAL_MENU)) ||
            string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_SETTINGS_TAB))
         )
      {
            BIND_ACTION_LEFT(cbs, action_left_mainmenu);
            return 0;
      }
   }

   if (menu_cbs_init_bind_left_compare_label(cbs, label, label_hash, menu_label) == 0)
      return 0;

   if (menu_cbs_init_bind_left_compare_type(cbs, type, menu_label) == 0)
      return 0;

   return -1;
}