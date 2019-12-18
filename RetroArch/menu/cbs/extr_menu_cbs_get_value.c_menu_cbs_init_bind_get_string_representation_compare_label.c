#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enum_idx; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_GET_VALUE (TYPE_1__*,int /*<<< orphan*/ ) ; 
#define  MENU_ENUM_LABEL_ACHIEVEMENT_LIST 180 
#define  MENU_ENUM_LABEL_ACHIEVEMENT_LIST_HARDCORE 179 
#define  MENU_ENUM_LABEL_AUDIO_DRIVER 178 
#define  MENU_ENUM_LABEL_AUDIO_RESAMPLER_DRIVER 177 
#define  MENU_ENUM_LABEL_CAMERA_DRIVER 176 
#define  MENU_ENUM_LABEL_CHEAT_FILE_SAVE_AS 175 
#define  MENU_ENUM_LABEL_CHEAT_NUM_PASSES 174 
#define  MENU_ENUM_LABEL_CLOSE_CONTENT 173 
#define  MENU_ENUM_LABEL_CONFIGURATIONS 172 
#define  MENU_ENUM_LABEL_CONNECT_WIFI 171 
#define  MENU_ENUM_LABEL_CORE_CHEAT_OPTIONS 170 
#define  MENU_ENUM_LABEL_CORE_COUNTERS 169 
#define  MENU_ENUM_LABEL_CORE_INFORMATION 168 
#define  MENU_ENUM_LABEL_CORE_INPUT_REMAPPING_OPTIONS 167 
#define  MENU_ENUM_LABEL_CORE_OPTIONS 166 
#define  MENU_ENUM_LABEL_CURSOR_MANAGER_LIST 165 
#define  MENU_ENUM_LABEL_DATABASE_MANAGER_LIST 164 
#define  MENU_ENUM_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST 163 
#define  MENU_ENUM_LABEL_FAVORITES 162 
#define  MENU_ENUM_LABEL_FRONTEND_COUNTERS 161 
#define  MENU_ENUM_LABEL_INPUT_DRIVER 160 
#define  MENU_ENUM_LABEL_JOYPAD_DRIVER 159 
#define  MENU_ENUM_LABEL_LOAD_CONTENT_HISTORY 158 
#define  MENU_ENUM_LABEL_LOAD_STATE 157 
#define  MENU_ENUM_LABEL_LOCATION_DRIVER 156 
#define  MENU_ENUM_LABEL_MENU_DRIVER 155 
#define  MENU_ENUM_LABEL_MIDI_DRIVER 154 
#define  MENU_ENUM_LABEL_PLAYLISTS_TAB 153 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_DEFAULT_CORE 152 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE 151 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE 150 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE 149 
#define  MENU_ENUM_LABEL_RECORD_DRIVER 148 
#define  MENU_ENUM_LABEL_REMAP_FILE_LOAD 147 
#define  MENU_ENUM_LABEL_RESTART_CONTENT 146 
#define  MENU_ENUM_LABEL_RESUME_CONTENT 145 
#define  MENU_ENUM_LABEL_SAVE_STATE 144 
#define  MENU_ENUM_LABEL_SCREEN_RESOLUTION 143 
#define  MENU_ENUM_LABEL_SHADER_OPTIONS 142 
#define  MENU_ENUM_LABEL_SHADER_WATCH_FOR_CHANGES 141 
#define  MENU_ENUM_LABEL_SYSTEM_INFORMATION 140 
#define  MENU_ENUM_LABEL_TAKE_SCREENSHOT 139 
#define  MENU_ENUM_LABEL_VIDEO_DRIVER 138 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_DEFAULT_FILTER 137 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_FILTER_PASS 136 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_NUM_PASSES 135 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_PARAMETERS 134 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_PASS 133 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_PRESET_PARAMETERS 132 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_PRESET_SAVE 131 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_PRESET_SAVE_AS 130 
#define  MENU_ENUM_LABEL_VIDEO_SHADER_SCALE_PASS 129 
#define  MENU_ENUM_LABEL_WIFI_DRIVER 128 
 int MSG_UNKNOWN ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_cheat_num_passes ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_configurations ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_more ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_video_resolution ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_playlist_associations ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_playlist_label_display_mode ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_playlist_left_thumbnail_mode ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_playlist_right_thumbnail_mode ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_remap_file_load ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_shader_default_filter ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_shader_filter_pass ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_shader_num_passes ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_shader_pass ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_shader_scale_pass ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_shader_watch_for_changes ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_wifi_is_online ; 

__attribute__((used)) static int menu_cbs_init_bind_get_string_representation_compare_label(
      menu_file_list_cbs_t *cbs)
{
   if (cbs->enum_idx != MSG_UNKNOWN)
   {
      switch (cbs->enum_idx)
      {
         case MENU_ENUM_LABEL_VIDEO_DRIVER:
         case MENU_ENUM_LABEL_AUDIO_DRIVER:
         case MENU_ENUM_LABEL_INPUT_DRIVER:
         case MENU_ENUM_LABEL_JOYPAD_DRIVER:
         case MENU_ENUM_LABEL_AUDIO_RESAMPLER_DRIVER:
         case MENU_ENUM_LABEL_RECORD_DRIVER:
         case MENU_ENUM_LABEL_MIDI_DRIVER:
         case MENU_ENUM_LABEL_LOCATION_DRIVER:
         case MENU_ENUM_LABEL_CAMERA_DRIVER:
         case MENU_ENUM_LABEL_WIFI_DRIVER:
         case MENU_ENUM_LABEL_MENU_DRIVER:
            BIND_ACTION_GET_VALUE(cbs, menu_action_setting_disp_set_label);
            break;
         case MENU_ENUM_LABEL_CONNECT_WIFI:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_wifi_is_online);
            break;
         case MENU_ENUM_LABEL_CHEAT_NUM_PASSES:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_cheat_num_passes);
            break;
         case MENU_ENUM_LABEL_REMAP_FILE_LOAD:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_remap_file_load);
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_FILTER_PASS:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_shader_filter_pass);
#endif
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_SCALE_PASS:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_shader_scale_pass);
#endif
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_NUM_PASSES:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_shader_num_passes);
#endif
            break;
         case MENU_ENUM_LABEL_SHADER_WATCH_FOR_CHANGES:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_shader_watch_for_changes);
#endif
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_PASS:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_shader_pass);
#endif
            break;
         case MENU_ENUM_LABEL_VIDEO_SHADER_DEFAULT_FILTER:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_shader_default_filter);
#endif
            break;
         case MENU_ENUM_LABEL_CONFIGURATIONS:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_configurations);
            break;
         case MENU_ENUM_LABEL_SCREEN_RESOLUTION:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_menu_video_resolution);
            break;
         case MENU_ENUM_LABEL_PLAYLISTS_TAB:
         case MENU_ENUM_LABEL_LOAD_CONTENT_HISTORY:
         case MENU_ENUM_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST:
         case MENU_ENUM_LABEL_FAVORITES:
         case MENU_ENUM_LABEL_CORE_OPTIONS:
         case MENU_ENUM_LABEL_CORE_CHEAT_OPTIONS:
         case MENU_ENUM_LABEL_SHADER_OPTIONS:
         case MENU_ENUM_LABEL_VIDEO_SHADER_PARAMETERS:
         case MENU_ENUM_LABEL_VIDEO_SHADER_PRESET_PARAMETERS:
         case MENU_ENUM_LABEL_VIDEO_SHADER_PRESET_SAVE:
         case MENU_ENUM_LABEL_VIDEO_SHADER_PRESET_SAVE_AS:
         case MENU_ENUM_LABEL_CHEAT_FILE_SAVE_AS:
         case MENU_ENUM_LABEL_FRONTEND_COUNTERS:
         case MENU_ENUM_LABEL_CORE_COUNTERS:
         case MENU_ENUM_LABEL_DATABASE_MANAGER_LIST:
         case MENU_ENUM_LABEL_CURSOR_MANAGER_LIST:
         case MENU_ENUM_LABEL_RESTART_CONTENT:
         case MENU_ENUM_LABEL_CLOSE_CONTENT:
         case MENU_ENUM_LABEL_RESUME_CONTENT:
         case MENU_ENUM_LABEL_TAKE_SCREENSHOT:
         case MENU_ENUM_LABEL_CORE_INPUT_REMAPPING_OPTIONS:
         case MENU_ENUM_LABEL_CORE_INFORMATION:
         case MENU_ENUM_LABEL_SYSTEM_INFORMATION:
         case MENU_ENUM_LABEL_ACHIEVEMENT_LIST:
         case MENU_ENUM_LABEL_ACHIEVEMENT_LIST_HARDCORE:
         case MENU_ENUM_LABEL_SAVE_STATE:
         case MENU_ENUM_LABEL_LOAD_STATE:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_menu_more);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_DEFAULT_CORE:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_playlist_associations);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_playlist_label_display_mode);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_playlist_right_thumbnail_mode);
            break;
         case MENU_ENUM_LABEL_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_playlist_left_thumbnail_mode);
            break;
         default:
            return - 1;
      }
   }
   else
   {
      return -1;
   }

   return 0;
}