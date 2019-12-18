#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int menu_show_advanced_settings; scalar_t__ quick_menu_show_information; scalar_t__ cheevos_enable; int /*<<< orphan*/  kiosk_mode_enable; scalar_t__ quick_menu_show_save_game_overrides; scalar_t__ quick_menu_show_save_core_overrides; scalar_t__ quick_menu_show_shaders; scalar_t__ quick_menu_show_cheats; scalar_t__ quick_menu_show_controls; scalar_t__ menu_show_latency; scalar_t__ menu_show_rewind; scalar_t__ menu_show_video_layout; scalar_t__ menu_show_overlays; scalar_t__ quick_menu_show_options; scalar_t__ quick_menu_show_start_streaming; scalar_t__ quick_menu_show_start_recording; scalar_t__ quick_menu_show_add_to_favorites; scalar_t__ quick_menu_show_undo_save_load_state; scalar_t__ quick_menu_show_save_load_state; scalar_t__ quick_menu_show_take_screenshot; scalar_t__ quick_menu_show_close_content; scalar_t__ quick_menu_show_restart_content; scalar_t__ quick_menu_show_resume_content; } ;
struct TYPE_11__ {int /*<<< orphan*/  record_driver; } ;
struct TYPE_13__ {TYPE_3__ bools; TYPE_2__ arrays; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_10__ {scalar_t__ get_num_images; } ;
struct TYPE_14__ {TYPE_1__ disk_control_cb; } ;
typedef  TYPE_5__ rarch_system_info_t ;
typedef  int /*<<< orphan*/  menu_handle_t ;
struct TYPE_15__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_6__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_TYPE_PLAYLIST_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ACHIEVEMENT_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TO_FAVORITES ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CLOSE_CONTENT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CORE_CHEAT_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CORE_INPUT_REMAPPING_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_CORE_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DISK_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_INFORMATION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_LATENCY_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_LOAD_STATE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NETPLAY_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NO_ITEMS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ONSCREEN_OVERLAY_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ONSCREEN_VIDEO_LAYOUT_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_QUICK_MENU_OVERRIDE_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_QUICK_MENU_START_RECORDING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_QUICK_MENU_START_STREAMING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_QUICK_MENU_STOP_RECORDING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_QUICK_MENU_STOP_STREAMING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_RESTART_CONTENT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_RESUME_CONTENT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_REWIND_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SAVE_STATE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SHADER_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_STATE_SLOT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_TAKE_SCREENSHOT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_UNDO_LOAD_STATE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_UNDO_SAVE_STATE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ACHIEVEMENT_LIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ADD_TO_FAVORITES ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CLOSE_CONTENT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CORE_CHEAT_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CORE_INPUT_REMAPPING_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_CORE_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_DISK_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_INFORMATION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_LATENCY_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_LOAD_STATE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NETPLAY_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NO_ITEMS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ONSCREEN_OVERLAY_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ONSCREEN_VIDEO_LAYOUT_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_QUICK_MENU_OVERRIDE_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_QUICK_MENU_START_RECORDING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_QUICK_MENU_START_STREAMING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_QUICK_MENU_STOP_RECORDING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_QUICK_MENU_STOP_STREAMING ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RESTART_CONTENT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RESUME_CONTENT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_REWIND_SETTINGS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SAVE_STATE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SHADER_OPTIONS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_TAKE_SCREENSHOT ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_UNDO_LOAD_STATE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_UNDO_SAVE_STATE ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_CLOSE ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_CORE_DISK_OPTIONS ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_LOADSTATE ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_RUN ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_SAVESTATE ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_SCREENSHOT ; 
 int /*<<< orphan*/  MENU_SETTING_NO_ITEM ; 
 int /*<<< orphan*/  PARSE_ONLY_INT ; 
 int /*<<< orphan*/  RARCH_CTL_IS_DUMMY_CORE ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_displaylist_parse_settings_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcheevos_hardcore_active ; 
 int /*<<< orphan*/  recording_is_enabled () ; 
 TYPE_5__* runloop_get_system_info () ; 
 scalar_t__ streaming_is_enabled () ; 
 scalar_t__ string_is_not_equal (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ video_shader_any_supported () ; 

__attribute__((used)) static int menu_displaylist_parse_load_content_settings(
      menu_handle_t *menu,
      menu_displaylist_info_t *info)
{
   settings_t *settings   = config_get_ptr();

   if (!rarch_ctl(RARCH_CTL_IS_DUMMY_CORE, NULL))
   {
#ifdef HAVE_LAKKA
      bool show_advanced_settings    = settings->bools.menu_show_advanced_settings;
#endif
      rarch_system_info_t *system    = runloop_get_system_info();

      if (settings->bools.quick_menu_show_resume_content)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RESUME_CONTENT),
               msg_hash_to_str(MENU_ENUM_LABEL_RESUME_CONTENT),
               MENU_ENUM_LABEL_RESUME_CONTENT,
               MENU_SETTING_ACTION_RUN, 0, 0);

      if (settings->bools.quick_menu_show_restart_content)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RESTART_CONTENT),
               msg_hash_to_str(MENU_ENUM_LABEL_RESTART_CONTENT),
               MENU_ENUM_LABEL_RESTART_CONTENT,
               MENU_SETTING_ACTION_RUN, 0, 0);

      if (settings->bools.quick_menu_show_close_content)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CLOSE_CONTENT),
               msg_hash_to_str(MENU_ENUM_LABEL_CLOSE_CONTENT),
               MENU_ENUM_LABEL_CLOSE_CONTENT,
               MENU_SETTING_ACTION_CLOSE, 0, 0);

      if (settings->bools.quick_menu_show_take_screenshot)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_TAKE_SCREENSHOT),
               msg_hash_to_str(MENU_ENUM_LABEL_TAKE_SCREENSHOT),
               MENU_ENUM_LABEL_TAKE_SCREENSHOT,
               MENU_SETTING_ACTION_SCREENSHOT, 0, 0);
      }

      if (settings->bools.quick_menu_show_save_load_state)
      {
         menu_displaylist_parse_settings_enum(info->list,
               MENU_ENUM_LABEL_STATE_SLOT, PARSE_ONLY_INT, true);

         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SAVE_STATE),
               msg_hash_to_str(MENU_ENUM_LABEL_SAVE_STATE),
               MENU_ENUM_LABEL_SAVE_STATE,
               MENU_SETTING_ACTION_SAVESTATE, 0, 0);
#ifdef HAVE_CHEEVOS
         if (!rcheevos_hardcore_active)
#endif
         {
            menu_entries_append_enum(info->list,
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_LOAD_STATE),
                  msg_hash_to_str(MENU_ENUM_LABEL_LOAD_STATE),
                  MENU_ENUM_LABEL_LOAD_STATE,
                  MENU_SETTING_ACTION_LOADSTATE, 0, 0);
         }
      }

      if (settings->bools.quick_menu_show_save_load_state &&
          settings->bools.quick_menu_show_undo_save_load_state)
      {
#ifdef HAVE_CHEEVOS
         if (!rcheevos_hardcore_active)
#endif
         {
            menu_entries_append_enum(info->list,
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_UNDO_LOAD_STATE),
                  msg_hash_to_str(MENU_ENUM_LABEL_UNDO_LOAD_STATE),
                  MENU_ENUM_LABEL_UNDO_LOAD_STATE,
                  MENU_SETTING_ACTION_LOADSTATE, 0, 0);
         }

         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_UNDO_SAVE_STATE),
               msg_hash_to_str(MENU_ENUM_LABEL_UNDO_SAVE_STATE),
               MENU_ENUM_LABEL_UNDO_SAVE_STATE,
               MENU_SETTING_ACTION_LOADSTATE, 0, 0);
      }

      if (settings->bools.quick_menu_show_add_to_favorites)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ADD_TO_FAVORITES),
               msg_hash_to_str(MENU_ENUM_LABEL_ADD_TO_FAVORITES),
               MENU_ENUM_LABEL_ADD_TO_FAVORITES, FILE_TYPE_PLAYLIST_ENTRY, 0, 0);
      }

      if (string_is_not_equal(settings->arrays.record_driver, "null"))
      {
         if (!recording_is_enabled())
         {
            if (settings->bools.quick_menu_show_start_recording && !settings->bools.kiosk_mode_enable)
            {
               menu_entries_append_enum(info->list,
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QUICK_MENU_START_RECORDING),
                     msg_hash_to_str(MENU_ENUM_LABEL_QUICK_MENU_START_RECORDING),
                     MENU_ENUM_LABEL_QUICK_MENU_START_RECORDING, MENU_SETTING_ACTION, 0, 0);
            }

            if (settings->bools.quick_menu_show_start_streaming && !settings->bools.kiosk_mode_enable)
            {
               menu_entries_append_enum(info->list,
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QUICK_MENU_START_STREAMING),
                     msg_hash_to_str(MENU_ENUM_LABEL_QUICK_MENU_START_STREAMING),
                     MENU_ENUM_LABEL_QUICK_MENU_START_STREAMING, MENU_SETTING_ACTION, 0, 0);
            }
         }
         else
         {
            if (streaming_is_enabled())
               menu_entries_append_enum(info->list,
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QUICK_MENU_STOP_STREAMING),
                     msg_hash_to_str(MENU_ENUM_LABEL_QUICK_MENU_STOP_STREAMING),
                     MENU_ENUM_LABEL_QUICK_MENU_STOP_STREAMING, MENU_SETTING_ACTION, 0, 0);
            else
               menu_entries_append_enum(info->list,
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QUICK_MENU_STOP_RECORDING),
                     msg_hash_to_str(MENU_ENUM_LABEL_QUICK_MENU_STOP_RECORDING),
                     MENU_ENUM_LABEL_QUICK_MENU_STOP_RECORDING, MENU_SETTING_ACTION, 0, 0);
         }
      }

      if (settings->bools.quick_menu_show_options && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_OPTIONS),
               msg_hash_to_str(MENU_ENUM_LABEL_CORE_OPTIONS),
               MENU_ENUM_LABEL_CORE_OPTIONS,
               MENU_SETTING_ACTION, 0, 0);
      }

      if (settings->bools.menu_show_overlays && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ONSCREEN_OVERLAY_SETTINGS),
               msg_hash_to_str(MENU_ENUM_LABEL_ONSCREEN_OVERLAY_SETTINGS),
               MENU_ENUM_LABEL_ONSCREEN_OVERLAY_SETTINGS,
               MENU_SETTING_ACTION, 0, 0);
      }

#ifdef HAVE_VIDEO_LAYOUT
      if (settings->bools.menu_show_video_layout && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ONSCREEN_VIDEO_LAYOUT_SETTINGS),
               msg_hash_to_str(MENU_ENUM_LABEL_ONSCREEN_VIDEO_LAYOUT_SETTINGS),
               MENU_ENUM_LABEL_ONSCREEN_VIDEO_LAYOUT_SETTINGS,
               MENU_SETTING_ACTION, 0, 0);
      }
#endif

      if (settings->bools.menu_show_rewind && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_REWIND_SETTINGS),
               msg_hash_to_str(MENU_ENUM_LABEL_REWIND_SETTINGS),
               MENU_ENUM_LABEL_REWIND_SETTINGS,
               MENU_SETTING_ACTION, 0, 0);
      }

      if (settings->bools.menu_show_latency && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_LATENCY_SETTINGS),
               msg_hash_to_str(MENU_ENUM_LABEL_LATENCY_SETTINGS),
               MENU_ENUM_LABEL_LATENCY_SETTINGS,
               MENU_SETTING_ACTION, 0, 0);
      }

#if 0
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NETPLAY_SETTINGS),
            msg_hash_to_str(MENU_ENUM_LABEL_NETPLAY_SETTINGS),
            MENU_ENUM_LABEL_NETPLAY_SETTINGS,
            MENU_SETTING_ACTION, 0, 0);
#endif

      if (settings->bools.quick_menu_show_controls && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_INPUT_REMAPPING_OPTIONS),
               msg_hash_to_str(MENU_ENUM_LABEL_CORE_INPUT_REMAPPING_OPTIONS),
               MENU_ENUM_LABEL_CORE_INPUT_REMAPPING_OPTIONS,
               MENU_SETTING_ACTION, 0, 0);
      }

      if (settings->bools.quick_menu_show_cheats)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_CHEAT_OPTIONS),
               msg_hash_to_str(MENU_ENUM_LABEL_CORE_CHEAT_OPTIONS),
               MENU_ENUM_LABEL_CORE_CHEAT_OPTIONS,
               MENU_SETTING_ACTION, 0, 0);
      }

      if ((!rarch_ctl(RARCH_CTL_IS_DUMMY_CORE, NULL))
            && system->disk_control_cb.get_num_images)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DISK_OPTIONS),
               msg_hash_to_str(MENU_ENUM_LABEL_DISK_OPTIONS),
               MENU_ENUM_LABEL_DISK_OPTIONS,
               MENU_SETTING_ACTION_CORE_DISK_OPTIONS, 0, 0);

#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
      if (video_shader_any_supported())
      {
         if (settings->bools.quick_menu_show_shaders && !settings->bools.kiosk_mode_enable)
         {
            menu_entries_append_enum(info->list,
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SHADER_OPTIONS),
                  msg_hash_to_str(MENU_ENUM_LABEL_SHADER_OPTIONS),
                  MENU_ENUM_LABEL_SHADER_OPTIONS,
                  MENU_SETTING_ACTION, 0, 0);
         }
      }
#endif

      if ((settings->bools.quick_menu_show_save_core_overrides ||
         settings->bools.quick_menu_show_save_game_overrides) &&
         !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_QUICK_MENU_OVERRIDE_OPTIONS),
            msg_hash_to_str(MENU_ENUM_LABEL_QUICK_MENU_OVERRIDE_OPTIONS),
            MENU_ENUM_LABEL_QUICK_MENU_OVERRIDE_OPTIONS,
            MENU_SETTING_ACTION, 0, 0);
      }

#ifdef HAVE_CHEEVOS
      if (settings->bools.cheevos_enable)
      {
         menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ACHIEVEMENT_LIST),
            msg_hash_to_str(MENU_ENUM_LABEL_ACHIEVEMENT_LIST),
            MENU_ENUM_LABEL_ACHIEVEMENT_LIST,
            MENU_SETTING_ACTION, 0, 0);
      }
#endif

      if (settings->bools.quick_menu_show_information)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_INFORMATION),
               msg_hash_to_str(MENU_ENUM_LABEL_INFORMATION),
               MENU_ENUM_LABEL_INFORMATION,
               MENU_SETTING_ACTION, 0, 0);
      }
   }
   else
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_ITEMS),
            msg_hash_to_str(MENU_ENUM_LABEL_NO_ITEMS),
            MENU_ENUM_LABEL_NO_ITEMS,
            MENU_SETTING_NO_ITEM, 0, 0);
   return 0;
}