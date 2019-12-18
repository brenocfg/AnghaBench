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
struct TYPE_7__ {int /*<<< orphan*/  kiosk_mode_enable; scalar_t__ menu_show_core_updater; } ;
struct TYPE_8__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_9__ {int* list; int /*<<< orphan*/  menu_list; scalar_t__ need_push_no_playlist_entries; scalar_t__ need_push; scalar_t__ need_clear; scalar_t__ need_refresh; scalar_t__ push_builtin_cores; scalar_t__ download_core; scalar_t__ need_sort; scalar_t__ need_entries_refresh; scalar_t__ need_navigation_clear; } ;
typedef  TYPE_3__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TYPE_CORE ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_REFRESH ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_SET_REFRESH ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CORE_UPDATER_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NO_PLAYLIST_ENTRIES_AVAILABLE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SIDELOAD_CORE_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_START_NET_RETROPAD ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_START_VIDEO_PROCESSOR ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_DOWNLOAD_CORE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NO_PLAYLIST_ENTRIES_AVAILABLE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SIDELOAD_CORE_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_START_NET_RETROPAD ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_START_VIDEO_PROCESSOR ; 
 int /*<<< orphan*/  MENU_INFO_MESSAGE ; 
 int /*<<< orphan*/  MENU_NAVIGATION_CTL_CLEAR ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  file_list_set_alt_at_offset (int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  file_list_sort_on_alt (int*) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  menu_driver_populate_entries (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  menu_entries_prepend (int*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_navigation_set_selection (size_t) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* new_entry ; 
 char* new_lbl_entry ; 
 char* new_path_entry ; 
 int /*<<< orphan*/  new_type ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  ui_companion_driver_notify_list_loaded (int*,int /*<<< orphan*/ ) ; 

bool menu_displaylist_process(menu_displaylist_info_t *info)
{
   size_t idx   = 0;
#if defined(HAVE_NETWORKING)
   settings_t *settings         = config_get_ptr();
#endif

   if (info->need_navigation_clear)
   {
      bool pending_push = true;
      menu_driver_ctl(MENU_NAVIGATION_CTL_CLEAR, &pending_push);
   }

   if (info->need_entries_refresh)
   {
      bool refresh = false;
      menu_entries_ctl(MENU_ENTRIES_CTL_SET_REFRESH, &refresh);
   }

   if (info->need_sort)
      file_list_sort_on_alt(info->list);

#if defined(HAVE_NETWORKING)
#if defined(__WINRT__) || defined(WINAPI_FAMILY) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#else
   if (settings->bools.menu_show_core_updater && !settings->bools.kiosk_mode_enable)
   {
      if (info->download_core)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DOWNLOAD_CORE),
               msg_hash_to_str(MENU_ENUM_LABEL_CORE_UPDATER_LIST),
               MENU_ENUM_LABEL_CORE_UPDATER_LIST,
               MENU_SETTING_ACTION, 0, 0);

         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SIDELOAD_CORE_LIST),
               msg_hash_to_str(MENU_ENUM_LABEL_SIDELOAD_CORE_LIST),
               MENU_ENUM_LABEL_SIDELOAD_CORE_LIST,
               MENU_SETTING_ACTION, 0, 0);
      }
   }
#endif
#endif

   if (info->push_builtin_cores)
   {
#if defined(HAVE_VIDEOPROCESSOR)
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_START_VIDEO_PROCESSOR),
            msg_hash_to_str(MENU_ENUM_LABEL_START_VIDEO_PROCESSOR),
            MENU_ENUM_LABEL_START_VIDEO_PROCESSOR,
            MENU_SETTING_ACTION, 0, 0);
#endif

#if defined(HAVE_NETWORKING) && defined(HAVE_NETWORKGAMEPAD)
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_START_NET_RETROPAD),
            msg_hash_to_str(MENU_ENUM_LABEL_START_NET_RETROPAD),
            MENU_ENUM_LABEL_START_NET_RETROPAD,
            MENU_SETTING_ACTION, 0, 0);
#endif
   }

   if (!string_is_empty(new_entry))
   {
      menu_entries_prepend(info->list,
            new_path_entry,
            new_lbl_entry,
            new_type,
            FILE_TYPE_CORE, 0, 0);
      file_list_set_alt_at_offset(info->list, 0,
            new_entry);

      new_type          = MSG_UNKNOWN;
      new_lbl_entry[0]  = '\0';
      new_path_entry[0] = '\0';
      new_entry[0]      = '\0';
   }

   if (info->need_refresh)
      menu_entries_ctl(MENU_ENTRIES_CTL_REFRESH, info->list);

   if (info->need_clear)
      menu_navigation_set_selection(idx);

   if (info->need_push)
   {
      if (info->need_push_no_playlist_entries)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(
                  MENU_ENUM_LABEL_VALUE_NO_PLAYLIST_ENTRIES_AVAILABLE),
               msg_hash_to_str(
                  MENU_ENUM_LABEL_NO_PLAYLIST_ENTRIES_AVAILABLE),
               MENU_ENUM_LABEL_NO_PLAYLIST_ENTRIES_AVAILABLE,
               MENU_INFO_MESSAGE, 0, 0);

      menu_driver_populate_entries(info);
      ui_companion_driver_notify_list_loaded(info->list, info->menu_list);
   }
   return true;
}