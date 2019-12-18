#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* directory_playlist; } ;
struct TYPE_8__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_9__ {int type; char* exts; char* label; int need_push_no_playlist_entries; int need_refresh; int need_push; char* path; int /*<<< orphan*/  list; } ;
typedef  TYPE_3__ menu_displaylist_info_t ;
typedef  int /*<<< orphan*/  menu_displaylist_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  DISPLAYLIST_CHEAT_SEARCH_SETTINGS_LIST ; 
 int /*<<< orphan*/  DISPLAYLIST_DATABASE_PLAYLISTS ; 
 int /*<<< orphan*/  DISPLAYLIST_FAVORITES ; 
 int /*<<< orphan*/  DISPLAYLIST_HISTORY ; 
 int /*<<< orphan*/  DISPLAYLIST_HORIZONTAL ; 
 int /*<<< orphan*/  DISPLAYLIST_IMAGES_HISTORY ; 
 int /*<<< orphan*/  DISPLAYLIST_MUSIC_HISTORY ; 
 int /*<<< orphan*/  DISPLAYLIST_NETPLAY_ROOM_LIST ; 
 int /*<<< orphan*/  DISPLAYLIST_SCAN_DIRECTORY_LIST ; 
 int /*<<< orphan*/  DISPLAYLIST_SETTINGS_ALL ; 
 int /*<<< orphan*/  DISPLAYLIST_VIDEO_HISTORY ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_CLEAR ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CHEAT_SEARCH_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HISTORY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_IMAGES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MUSIC_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NETPLAY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLISTS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_TAKE_SCREENSHOT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_TAKE_SCREENSHOT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_TAB ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_SCREENSHOT ; 
 int /*<<< orphan*/  RARCH_CTL_IS_DUMMY_CORE ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  filebrowser_clear_type () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ menu_displaylist_ctl (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* strdup (char*) ; 
 scalar_t__ string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static bool menu_displaylist_push_internal(
      const char *label,
      menu_displaylist_ctx_entry_t *entry,
      menu_displaylist_info_t *info)
{
   if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_HISTORY_TAB)))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_HISTORY, info))
         return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_FAVORITES_TAB)))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_FAVORITES, info))
         return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_SETTINGS_TAB)))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_SETTINGS_ALL, info))
         return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_CHEAT_SEARCH_SETTINGS)))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_CHEAT_SEARCH_SETTINGS_LIST, info))
         return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_MUSIC_TAB)))
   {
      filebrowser_clear_type();
      info->type = 42;

      if (!string_is_empty(info->exts))
         free(info->exts);
      if (!string_is_empty(info->label))
         free(info->label);

      info->exts  = strdup("lpl");
      info->label = strdup(
            msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB));

      menu_entries_ctl(MENU_ENTRIES_CTL_CLEAR, info->list);
      menu_displaylist_ctl(DISPLAYLIST_MUSIC_HISTORY, info);
      return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_VIDEO_TAB)))
   {
      filebrowser_clear_type();
      info->type = 42;

      if (!string_is_empty(info->exts))
         free(info->exts);
      if (!string_is_empty(info->label))
         free(info->label);

      info->exts  = strdup("lpl");
      info->label = strdup(
            msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB));

      menu_entries_ctl(MENU_ENTRIES_CTL_CLEAR, info->list);
      menu_displaylist_ctl(DISPLAYLIST_VIDEO_HISTORY, info);
      return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_IMAGES_TAB)))
   {
      filebrowser_clear_type();
      info->type = 42;

      if (!string_is_empty(info->exts))
         free(info->exts);
      if (!string_is_empty(info->label))
         free(info->label);

      info->exts  = strdup("lpl");
      info->label = strdup(
            msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB));

      menu_entries_ctl(MENU_ENTRIES_CTL_CLEAR, info->list);

#if 0
      if (!rarch_ctl(RARCH_CTL_IS_DUMMY_CORE, NULL))
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_TAKE_SCREENSHOT),
               msg_hash_to_str(MENU_ENUM_LABEL_TAKE_SCREENSHOT),
               MENU_ENUM_LABEL_TAKE_SCREENSHOT,
               MENU_SETTING_ACTION_SCREENSHOT, 0, 0);
      else
         info->need_push_no_playlist_entries = true;
#endif
      menu_displaylist_ctl(DISPLAYLIST_IMAGES_HISTORY, info);
      return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB)))
   {
      settings_t *settings  = config_get_ptr();

      filebrowser_clear_type();
      info->type = 42;

      if (!string_is_empty(info->exts))
         free(info->exts);
      if (!string_is_empty(info->label))
         free(info->label);

      info->exts  = strdup("lpl");
      info->label = strdup(
            msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB));

      if (string_is_empty(settings->paths.directory_playlist))
      {
         menu_entries_ctl(MENU_ENTRIES_CTL_CLEAR, info->list);
         info->need_refresh                  = true;
         info->need_push_no_playlist_entries = true;
         info->need_push                     = true;

         return true;
      }
      else
      {
         if (!string_is_empty(info->path))
            free(info->path);

         info->path = strdup(settings->paths.directory_playlist);

         if (menu_displaylist_ctl(
                  DISPLAYLIST_DATABASE_PLAYLISTS, info))
            return true;
      }
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_ADD_TAB)))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_SCAN_DIRECTORY_LIST, info))
         return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_NETPLAY_TAB)))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_NETPLAY_ROOM_LIST, info))
         return true;
   }
   else if (string_is_equal(label, msg_hash_to_str(MENU_ENUM_LABEL_HORIZONTAL_MENU)))
   {
      if (menu_displaylist_ctl(DISPLAYLIST_HORIZONTAL, info))
         return true;
   }

   return false;
}