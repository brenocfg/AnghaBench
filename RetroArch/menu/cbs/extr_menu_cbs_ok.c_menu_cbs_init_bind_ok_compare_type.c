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
typedef  int uint32_t ;
struct TYPE_4__ {int enum_idx; } ;
typedef  TYPE_1__ menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_OK (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FILEBROWSER_SCAN_FILE ; 
#define  FILE_TYPE_AUDIOFILTER 215 
#define  FILE_TYPE_CARCHIVE 214 
#define  FILE_TYPE_CHEAT 213 
#define  FILE_TYPE_CONFIG 212 
#define  FILE_TYPE_CONTENTLIST_ENTRY 211 
#define  FILE_TYPE_CORE 210 
#define  FILE_TYPE_CURSOR 209 
#define  FILE_TYPE_DIRECTORY 208 
#define  FILE_TYPE_DIRECT_LOAD 207 
#define  FILE_TYPE_DOWNLOAD_CORE 206 
#define  FILE_TYPE_DOWNLOAD_CORE_CONTENT 205 
#define  FILE_TYPE_DOWNLOAD_CORE_INFO 204 
#define  FILE_TYPE_DOWNLOAD_LAKKA 203 
#define  FILE_TYPE_DOWNLOAD_PL_THUMBNAIL_CONTENT 202 
#define  FILE_TYPE_DOWNLOAD_THUMBNAIL 201 
#define  FILE_TYPE_DOWNLOAD_THUMBNAIL_CONTENT 200 
#define  FILE_TYPE_DOWNLOAD_URL 199 
#define  FILE_TYPE_FONT 198 
#define  FILE_TYPE_IMAGE 197 
#define  FILE_TYPE_IMAGEVIEWER 196 
#define  FILE_TYPE_IN_CARCHIVE 195 
#define  FILE_TYPE_MOVIE 194 
#define  FILE_TYPE_MUSIC 193 
#define  FILE_TYPE_OVERLAY 192 
#define  FILE_TYPE_PARENT_DIRECTORY 191 
#define  FILE_TYPE_PLAIN 190 
#define  FILE_TYPE_PLAYLIST_COLLECTION 189 
#define  FILE_TYPE_PLAYLIST_ENTRY 188 
#define  FILE_TYPE_RDB 187 
#define  FILE_TYPE_RDB_ENTRY 186 
#define  FILE_TYPE_RECORD_CONFIG 185 
#define  FILE_TYPE_REMAP 184 
#define  FILE_TYPE_RGUI_THEME_PRESET 183 
#define  FILE_TYPE_RPL_ENTRY 182 
#define  FILE_TYPE_SCAN_DIRECTORY 181 
#define  FILE_TYPE_SHADER 180 
#define  FILE_TYPE_SHADER_PRESET 179 
#define  FILE_TYPE_STREAM_CONFIG 178 
#define  FILE_TYPE_USE_DIRECTORY 177 
#define  FILE_TYPE_VIDEOFILTER 176 
#define  FILE_TYPE_VIDEO_LAYOUT 175 
#define  MENU_ENUM_LABEL_CORE_UPDATER_LIST 174 
#define  MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE 173 
#define  MENU_ENUM_LABEL_DISK_IMAGE_APPEND 172 
#define  MENU_ENUM_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST 171 
#define  MENU_ENUM_LABEL_FAVORITES 170 
#define  MENU_ENUM_LABEL_SUBSYSTEM_ADD 169 
 int MENU_LABEL_AUDIO_DSP_PLUGIN ; 
 int MENU_LABEL_CHEAT_FILE_LOAD_APPEND ; 
#define  MENU_LABEL_CORE_LIST 168 
#define  MENU_LABEL_CURSOR_MANAGER_LIST 167 
#define  MENU_LABEL_DATABASE_MANAGER_LIST 166 
#define  MENU_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE 165 
#define  MENU_LABEL_DEFERRED_CORE_LIST 164 
#define  MENU_LABEL_DEFERRED_CORE_LIST_SET 163 
#define  MENU_LABEL_DEFERRED_DATABASE_MANAGER_LIST 162 
#define  MENU_LABEL_DISK_IMAGE_APPEND 161 
#define  MENU_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST 160 
#define  MENU_LABEL_FAVORITES 159 
 int MENU_LABEL_PLAYLISTS_TAB ; 
 int MENU_LABEL_RDB_ENTRY_START_CONTENT ; 
#define  MENU_LABEL_SIDELOAD_CORE_LIST 158 
#define  MENU_LABEL_SUBSYSTEM_ADD 157 
 int MENU_LABEL_VIDEO_FILTER ; 
 int MENU_LABEL_VIDEO_FONT_PATH ; 
 int MENU_LABEL_XMB_FONT ; 
#define  MENU_NETPLAY_LAN_SCAN 156 
#define  MENU_SETTINGS 155 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_END ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_LOOPED_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_LOOPED_END ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_SEQUENTIAL_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_SEQUENTIAL_END ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_REMOVE_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_REMOVE_END ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_STOP_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_STOP_END ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_END ; 
 unsigned int MENU_SETTINGS_CHEAT_BEGIN ; 
 unsigned int MENU_SETTINGS_CHEAT_END ; 
 unsigned int MENU_SETTINGS_CHEEVOS_START ; 
#define  MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_CYCLE_TRAY_STATUS 154 
#define  MENU_SETTINGS_CORE_OPTION_CREATE 153 
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 unsigned int MENU_SETTINGS_CUSTOM_BIND ; 
 unsigned int MENU_SETTINGS_CUSTOM_BIND_KEYBOARD ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_LAST ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST ; 
#define  MENU_SETTING_ACTION_CORE_DISK_OPTIONS 152 
#define  MENU_SETTING_DROPDOWN_ITEM 151 
#define  MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_DEFAULT_CORE 150 
#define  MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_LABEL_DISPLAY_MODE 149 
#define  MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_LEFT_THUMBNAIL_MODE 148 
#define  MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_RIGHT_THUMBNAIL_MODE 147 
#define  MENU_SETTING_DROPDOWN_ITEM_RESOLUTION 146 
#define  MENU_SETTING_DROPDOWN_SETTING_CORE_OPTIONS_ITEM 145 
#define  MENU_SETTING_DROPDOWN_SETTING_CORE_OPTIONS_ITEM_SPECIAL 144 
#define  MENU_SETTING_DROPDOWN_SETTING_FLOAT_ITEM 143 
#define  MENU_SETTING_DROPDOWN_SETTING_FLOAT_ITEM_SPECIAL 142 
#define  MENU_SETTING_DROPDOWN_SETTING_INT_ITEM 141 
#define  MENU_SETTING_DROPDOWN_SETTING_INT_ITEM_SPECIAL 140 
#define  MENU_SETTING_DROPDOWN_SETTING_STRING_OPTIONS_ITEM 139 
#define  MENU_SETTING_DROPDOWN_SETTING_STRING_OPTIONS_ITEM_SPECIAL 138 
#define  MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM 137 
#define  MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM_SPECIAL 136 
#define  MENU_SETTING_GROUP 135 
#define  MENU_SETTING_SUBGROUP 134 
 unsigned int MENU_SET_CDROM_INFO ; 
 unsigned int MENU_SET_CDROM_LIST ; 
 unsigned int MENU_SET_LOAD_CDROM_LIST ; 
#define  MENU_SET_SWITCH_BRIGHTNESS 133 
#define  MENU_SET_SWITCH_CPU_PROFILE 132 
#define  MENU_SET_SWITCH_GPU_PROFILE 131 
#define  MENU_VALUE_HORIZONTAL_MENU 130 
#define  MENU_WIFI 129 
#define  MSG_UNKNOWN 128 
 int /*<<< orphan*/ * action_ok_cdrom_info_list ; 
 int /*<<< orphan*/ * action_ok_cheat ; 
 int /*<<< orphan*/ * action_ok_cheat_file_load ; 
 int /*<<< orphan*/ * action_ok_cheat_file_load_append ; 
 int /*<<< orphan*/ * action_ok_compressed_archive_push ; 
 int /*<<< orphan*/ * action_ok_compressed_archive_push_detect_core ; 
 int /*<<< orphan*/ * action_ok_config_load ; 
 int /*<<< orphan*/ * action_ok_core_content_download ; 
 int /*<<< orphan*/ * action_ok_core_content_thumbnails ; 
 int /*<<< orphan*/ * action_ok_core_deferred_set ; 
 int /*<<< orphan*/ * action_ok_core_option_dropdown_list ; 
 int /*<<< orphan*/ * action_ok_core_updater_download ; 
 int /*<<< orphan*/ * action_ok_cursor_manager_list ; 
 int /*<<< orphan*/ * action_ok_database_manager_list ; 
 int /*<<< orphan*/ * action_ok_deferred_list_stub ; 
 int /*<<< orphan*/ * action_ok_directory_push ; 
 int /*<<< orphan*/ * action_ok_disk_cycle_tray_status ; 
 int /*<<< orphan*/ * action_ok_disk_image_append ; 
 int /*<<< orphan*/ * action_ok_download_url ; 
 int /*<<< orphan*/ * action_ok_dump_cdrom ; 
 int /*<<< orphan*/ * action_ok_file_load ; 
 int /*<<< orphan*/ * action_ok_file_load_ffmpeg ; 
 int /*<<< orphan*/ * action_ok_file_load_imageviewer ; 
 int /*<<< orphan*/ * action_ok_file_load_music ; 
 int /*<<< orphan*/ * action_ok_file_load_with_detect_core ; 
 int /*<<< orphan*/ * action_ok_file_load_with_detect_core_carchive ; 
 int /*<<< orphan*/ * action_ok_lakka_download ; 
 int /*<<< orphan*/ * action_ok_load_cdrom ; 
 int /*<<< orphan*/ * action_ok_load_core ; 
 int /*<<< orphan*/ * action_ok_load_core_deferred ; 
 int /*<<< orphan*/ * action_ok_lookup_setting ; 
 int /*<<< orphan*/ * action_ok_menu_wallpaper_load ; 
 int /*<<< orphan*/ * action_ok_mixer_stream_action_play ; 
 int /*<<< orphan*/ * action_ok_mixer_stream_action_play_looped ; 
 int /*<<< orphan*/ * action_ok_mixer_stream_action_play_sequential ; 
 int /*<<< orphan*/ * action_ok_mixer_stream_action_remove ; 
 int /*<<< orphan*/ * action_ok_mixer_stream_action_stop ; 
 int /*<<< orphan*/ * action_ok_mixer_stream_actions ; 
 int /*<<< orphan*/ * action_ok_netplay_lan_scan ; 
 int /*<<< orphan*/ * action_ok_option_create ; 
 int /*<<< orphan*/ * action_ok_parent_directory_push ; 
 int /*<<< orphan*/ * action_ok_path_scan_directory ; 
 int /*<<< orphan*/ * action_ok_path_use_directory ; 
 int /*<<< orphan*/ * action_ok_pl_content_thumbnails ; 
 int /*<<< orphan*/ * action_ok_playlist_collection ; 
 int /*<<< orphan*/ * action_ok_playlist_entry ; 
 int /*<<< orphan*/ * action_ok_playlist_entry_collection ; 
 int /*<<< orphan*/ * action_ok_playlist_entry_start_content ; 
 int /*<<< orphan*/ * action_ok_push_default ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_item ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_item_playlist_default_core ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_item_playlist_label_display_mode ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_item_playlist_left_thumbnail_mode ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_item_playlist_right_thumbnail_mode ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_item_resolution ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_core_options_item ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_core_options_item_special ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_float_item ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_float_item_special ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_int_item ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_int_item_special ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_string_options_item ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_string_options_item_special ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_uint_item ; 
 int /*<<< orphan*/ * action_ok_push_dropdown_setting_uint_item_special ; 
 int /*<<< orphan*/ * action_ok_push_generic_list ; 
 int /*<<< orphan*/ * action_ok_push_random_dir ; 
 int /*<<< orphan*/ * action_ok_rdb_entry ; 
 int /*<<< orphan*/ * action_ok_record_configfile_load ; 
 int /*<<< orphan*/ * action_ok_remap_file_load ; 
 int /*<<< orphan*/ * action_ok_rgui_menu_theme_preset_load ; 
 int /*<<< orphan*/ * action_ok_rpl_entry ; 
 int /*<<< orphan*/ * action_ok_scan_file ; 
 int /*<<< orphan*/ * action_ok_set_path ; 
 int /*<<< orphan*/ * action_ok_set_path_audiofilter ; 
 int /*<<< orphan*/ * action_ok_set_path_overlay ; 
 int /*<<< orphan*/ * action_ok_set_path_video_layout ; 
 int /*<<< orphan*/ * action_ok_set_path_videofilter ; 
 int /*<<< orphan*/ * action_ok_set_switch_backlight ; 
 int /*<<< orphan*/ * action_ok_set_switch_cpu_profile ; 
 int /*<<< orphan*/ * action_ok_set_switch_gpu_profile ; 
 int /*<<< orphan*/ * action_ok_shader_pass_load ; 
 int /*<<< orphan*/ * action_ok_shader_preset_load ; 
 int /*<<< orphan*/ * action_ok_sideload_core ; 
 int /*<<< orphan*/ * action_ok_stream_configfile_load ; 
 int /*<<< orphan*/ * action_ok_subsystem_add ; 
 int /*<<< orphan*/ * action_ok_thumbnails_updater_download ; 
 int /*<<< orphan*/ * action_ok_wifi ; 
 int /*<<< orphan*/  filebrowser_get_type () ; 

__attribute__((used)) static int menu_cbs_init_bind_ok_compare_type(menu_file_list_cbs_t *cbs,
      uint32_t label_hash, uint32_t menu_label_hash, unsigned type)
{
   if (type == MENU_SET_CDROM_LIST)
   {
      BIND_ACTION_OK(cbs, action_ok_dump_cdrom);
   }
   else if (type == MENU_SET_CDROM_INFO)
   {
      BIND_ACTION_OK(cbs, action_ok_cdrom_info_list);
   }
   else if (type == MENU_SET_LOAD_CDROM_LIST)
   {
      BIND_ACTION_OK(cbs, action_ok_load_cdrom);
   }
   else if (type == MENU_SETTINGS_CUSTOM_BIND_KEYBOARD ||
         type == MENU_SETTINGS_CUSTOM_BIND)
   {
      BIND_ACTION_OK(cbs, action_ok_lookup_setting);
   }
#ifdef HAVE_AUDIOMIXER
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_BEGIN
      && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_END)
   {
      BIND_ACTION_OK(cbs, action_ok_mixer_stream_action_play);
   }
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_LOOPED_BEGIN
      && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_LOOPED_END)
   {
      BIND_ACTION_OK(cbs, action_ok_mixer_stream_action_play_looped);
   }
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_SEQUENTIAL_BEGIN
      && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_PLAY_SEQUENTIAL_END)
   {
      BIND_ACTION_OK(cbs, action_ok_mixer_stream_action_play_sequential);
   }
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_REMOVE_BEGIN
      && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_REMOVE_END)
   {
      BIND_ACTION_OK(cbs, action_ok_mixer_stream_action_remove);
   }
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_STOP_BEGIN
      && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_STOP_END)
   {
      BIND_ACTION_OK(cbs, action_ok_mixer_stream_action_stop);
   }
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_BEGIN
      && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_END)
   {
      BIND_ACTION_OK(cbs, action_ok_mixer_stream_actions);
   }
#endif
   else if (type >= MENU_SETTINGS_SHADER_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PARAMETER_LAST)
   {
      BIND_ACTION_OK(cbs, NULL);
   }
   else if (type >= MENU_SETTINGS_SHADER_PRESET_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST)
   {
      BIND_ACTION_OK(cbs, NULL);
   }
   else if (type >= MENU_SETTINGS_CHEAT_BEGIN
         && type <= MENU_SETTINGS_CHEAT_END)
   {
      BIND_ACTION_OK(cbs, action_ok_cheat);
   }
   else if ((type >= MENU_SETTINGS_CORE_OPTION_START) &&
            (type < MENU_SETTINGS_CHEEVOS_START))
   {
      BIND_ACTION_OK(cbs, action_ok_core_option_dropdown_list);
   }
   else
   {
      switch (type)
      {
         case MENU_SETTING_DROPDOWN_SETTING_CORE_OPTIONS_ITEM:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_core_options_item);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_STRING_OPTIONS_ITEM:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_string_options_item);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_INT_ITEM:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_int_item);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_FLOAT_ITEM:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_float_item);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_uint_item);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_CORE_OPTIONS_ITEM_SPECIAL:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_core_options_item_special);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_STRING_OPTIONS_ITEM_SPECIAL:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_string_options_item_special);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_INT_ITEM_SPECIAL:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_int_item_special);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_FLOAT_ITEM_SPECIAL:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_float_item_special);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM_SPECIAL:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_setting_uint_item_special);
            break;
         case MENU_SETTING_DROPDOWN_ITEM:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_item);
            break;
         case MENU_SETTING_DROPDOWN_ITEM_RESOLUTION:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_item_resolution);
            break;
         case MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_DEFAULT_CORE:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_item_playlist_default_core);
            break;
         case MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_LABEL_DISPLAY_MODE:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_item_playlist_label_display_mode);
            break;
         case MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_RIGHT_THUMBNAIL_MODE:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_item_playlist_right_thumbnail_mode);
            break;
         case MENU_SETTING_DROPDOWN_ITEM_PLAYLIST_LEFT_THUMBNAIL_MODE:
            BIND_ACTION_OK(cbs, action_ok_push_dropdown_item_playlist_left_thumbnail_mode);
            break;
         case MENU_SETTING_ACTION_CORE_DISK_OPTIONS:
            BIND_ACTION_OK(cbs, action_ok_push_default);
            break;
         case FILE_TYPE_PLAYLIST_ENTRY:
            if (label_hash == MENU_LABEL_PLAYLISTS_TAB)
            {
               BIND_ACTION_OK(cbs, action_ok_playlist_entry_collection);
            }
            else if (label_hash == MENU_LABEL_RDB_ENTRY_START_CONTENT)
            {
               BIND_ACTION_OK(cbs, action_ok_playlist_entry_start_content);
            }
            else
            {
               BIND_ACTION_OK(cbs, action_ok_playlist_entry);
            }
            break;
#ifdef HAVE_LAKKA_SWITCH
         case MENU_SET_SWITCH_GPU_PROFILE:
            BIND_ACTION_OK(cbs, action_ok_set_switch_gpu_profile);
            break;
         case MENU_SET_SWITCH_BRIGHTNESS:
            BIND_ACTION_OK(cbs, action_ok_set_switch_backlight);
            break;
#endif
#if defined(HAVE_LAKKA_SWITCH) || defined(HAVE_LIBNX)
         case MENU_SET_SWITCH_CPU_PROFILE:
            BIND_ACTION_OK(cbs, action_ok_set_switch_cpu_profile);
            break;
#endif
         case FILE_TYPE_RPL_ENTRY:
            BIND_ACTION_OK(cbs, action_ok_rpl_entry);
            break;
         case FILE_TYPE_PLAYLIST_COLLECTION:
            BIND_ACTION_OK(cbs, action_ok_playlist_collection);
            break;
         case FILE_TYPE_CONTENTLIST_ENTRY:
            BIND_ACTION_OK(cbs, action_ok_push_generic_list);
            break;
         case FILE_TYPE_CHEAT:
            if (menu_label_hash == MENU_LABEL_CHEAT_FILE_LOAD_APPEND)
            {
               BIND_ACTION_OK(cbs, action_ok_cheat_file_load_append);
            }
            else
            {
               BIND_ACTION_OK(cbs, action_ok_cheat_file_load);
            }
            break;
         case FILE_TYPE_RECORD_CONFIG:
            BIND_ACTION_OK(cbs, action_ok_record_configfile_load);
            break;
         case FILE_TYPE_STREAM_CONFIG:
            BIND_ACTION_OK(cbs, action_ok_stream_configfile_load);
            break;
         case FILE_TYPE_RGUI_THEME_PRESET:
            BIND_ACTION_OK(cbs, action_ok_rgui_menu_theme_preset_load);
            break;
         case FILE_TYPE_REMAP:
            BIND_ACTION_OK(cbs, action_ok_remap_file_load);
            break;
         case FILE_TYPE_SHADER_PRESET:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            /* TODO/FIXME - handle scan case */
            BIND_ACTION_OK(cbs, action_ok_shader_preset_load);
#endif
            break;
         case FILE_TYPE_SHADER:
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
            /* TODO/FIXME - handle scan case */
            BIND_ACTION_OK(cbs, action_ok_shader_pass_load);
#endif
            break;
         case FILE_TYPE_IMAGE:
            /* TODO/FIXME - handle scan case */
            BIND_ACTION_OK(cbs, action_ok_menu_wallpaper_load);
            break;
         case FILE_TYPE_USE_DIRECTORY:
            BIND_ACTION_OK(cbs, action_ok_path_use_directory);
            break;
#ifdef HAVE_LIBRETRODB
         case FILE_TYPE_SCAN_DIRECTORY:
            BIND_ACTION_OK(cbs, action_ok_path_scan_directory);
            break;
#endif
         case FILE_TYPE_CONFIG:
            BIND_ACTION_OK(cbs, action_ok_config_load);
            break;
         case FILE_TYPE_PARENT_DIRECTORY:
            BIND_ACTION_OK(cbs, action_ok_parent_directory_push);
            break;
         case FILE_TYPE_DIRECTORY:
            if (cbs->enum_idx != MSG_UNKNOWN
                  || menu_label_hash == MENU_LABEL_DISK_IMAGE_APPEND
                  || menu_label_hash == MENU_LABEL_SUBSYSTEM_ADD
                  || menu_label_hash == MENU_LABEL_VIDEO_FONT_PATH
                  || menu_label_hash == MENU_LABEL_XMB_FONT
                  || menu_label_hash == MENU_LABEL_AUDIO_DSP_PLUGIN
                  || menu_label_hash == MENU_LABEL_VIDEO_FILTER)
               BIND_ACTION_OK(cbs, action_ok_directory_push);
            else
               BIND_ACTION_OK(cbs, action_ok_push_random_dir);
            break;
         case FILE_TYPE_CARCHIVE:
            if (filebrowser_get_type() == FILEBROWSER_SCAN_FILE)
            {
#ifdef HAVE_LIBRETRODB
               BIND_ACTION_OK(cbs, action_ok_scan_file);
#endif
            }
            else
            {
               switch (menu_label_hash)
               {
                  case MENU_LABEL_FAVORITES:
                     BIND_ACTION_OK(cbs, action_ok_compressed_archive_push_detect_core);
                     break;
                  default:
                     BIND_ACTION_OK(cbs, action_ok_compressed_archive_push);
                     break;
               }
            }
            break;
         case FILE_TYPE_CORE:
            if (cbs->enum_idx != MSG_UNKNOWN)
            {
               switch (cbs->enum_idx)
               {
                  case MENU_ENUM_LABEL_CORE_UPDATER_LIST:
                     BIND_ACTION_OK(cbs, action_ok_deferred_list_stub);
                     break;
                  case MSG_UNKNOWN:
                  default:
                     break;
               }
            }
            else
            {
               switch (menu_label_hash)
               {
                  case MENU_LABEL_DEFERRED_CORE_LIST:
                     BIND_ACTION_OK(cbs, action_ok_load_core_deferred);
                     break;
                  case MENU_LABEL_DEFERRED_CORE_LIST_SET:
                     BIND_ACTION_OK(cbs, action_ok_core_deferred_set);
                     break;
                  case MENU_LABEL_CORE_LIST:
                     BIND_ACTION_OK(cbs, action_ok_load_core);
                     break;
                  case MENU_LABEL_SIDELOAD_CORE_LIST:
                     BIND_ACTION_OK(cbs, action_ok_sideload_core);
                     break;
               }
            }
            break;
         case FILE_TYPE_DOWNLOAD_CORE_CONTENT:
            BIND_ACTION_OK(cbs, action_ok_core_content_download);
            break;
         case FILE_TYPE_DOWNLOAD_THUMBNAIL_CONTENT:
            BIND_ACTION_OK(cbs, action_ok_core_content_thumbnails);
            break;
         case FILE_TYPE_DOWNLOAD_PL_THUMBNAIL_CONTENT:
            BIND_ACTION_OK(cbs, action_ok_pl_content_thumbnails);
            break;
         case FILE_TYPE_DOWNLOAD_CORE:
            BIND_ACTION_OK(cbs, action_ok_core_updater_download);
            break;
         case FILE_TYPE_DOWNLOAD_URL:
            BIND_ACTION_OK(cbs, action_ok_download_url);
            break;
         case FILE_TYPE_DOWNLOAD_THUMBNAIL:
            BIND_ACTION_OK(cbs, action_ok_thumbnails_updater_download);
            break;
         case FILE_TYPE_DOWNLOAD_LAKKA:
            BIND_ACTION_OK(cbs, action_ok_lakka_download);
            break;
         case FILE_TYPE_DOWNLOAD_CORE_INFO:
            break;
         case FILE_TYPE_RDB:
            switch (menu_label_hash)
            {
               case MENU_LABEL_DEFERRED_DATABASE_MANAGER_LIST:
                  BIND_ACTION_OK(cbs, action_ok_deferred_list_stub);
                  break;
               case MENU_LABEL_DATABASE_MANAGER_LIST:
               case MENU_VALUE_HORIZONTAL_MENU:
                  BIND_ACTION_OK(cbs, action_ok_database_manager_list);
                  break;
            }
            break;
         case FILE_TYPE_RDB_ENTRY:
            BIND_ACTION_OK(cbs, action_ok_rdb_entry);
            break;
         case MENU_WIFI:
            BIND_ACTION_OK(cbs, action_ok_wifi);
            break;
         case MENU_NETPLAY_LAN_SCAN:
            BIND_ACTION_OK(cbs, action_ok_netplay_lan_scan);
            break;
         case FILE_TYPE_CURSOR:
            switch (menu_label_hash)
            {
               case MENU_LABEL_DEFERRED_DATABASE_MANAGER_LIST:
                  BIND_ACTION_OK(cbs, action_ok_deferred_list_stub);
                  break;
               case MENU_LABEL_CURSOR_MANAGER_LIST:
                  BIND_ACTION_OK(cbs, action_ok_cursor_manager_list);
                  break;
            }
            break;
         case FILE_TYPE_VIDEOFILTER:
            BIND_ACTION_OK(cbs, action_ok_set_path_videofilter);
            break;
         case FILE_TYPE_FONT:
            BIND_ACTION_OK(cbs, action_ok_set_path);
            break;
         case FILE_TYPE_OVERLAY:
            BIND_ACTION_OK(cbs, action_ok_set_path_overlay);
            break;
#ifdef HAVE_VIDEO_LAYOUT
         case FILE_TYPE_VIDEO_LAYOUT:
            BIND_ACTION_OK(cbs, action_ok_set_path_video_layout);
            break;
#endif
         case FILE_TYPE_AUDIOFILTER:
            BIND_ACTION_OK(cbs, action_ok_set_path_audiofilter);
            break;
         case FILE_TYPE_IN_CARCHIVE:
         case FILE_TYPE_PLAIN:
            if (filebrowser_get_type() == FILEBROWSER_SCAN_FILE)
            {
#ifdef HAVE_LIBRETRODB
               BIND_ACTION_OK(cbs, action_ok_scan_file);
#endif
            }
            else if (cbs->enum_idx != MSG_UNKNOWN)
            {
               switch (cbs->enum_idx)
               {
                  case MENU_ENUM_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST:
                  case MENU_ENUM_LABEL_FAVORITES:
                  case MENU_ENUM_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE:
#ifdef HAVE_COMPRESSION
                     if (type == FILE_TYPE_IN_CARCHIVE)
                     {
                        BIND_ACTION_OK(cbs, action_ok_file_load_with_detect_core_carchive);
                     }
                     else
#endif
                     {
                        BIND_ACTION_OK(cbs, action_ok_file_load_with_detect_core);
                     }
                     break;
                  case MENU_ENUM_LABEL_DISK_IMAGE_APPEND:
                     BIND_ACTION_OK(cbs, action_ok_disk_image_append);
                     break;
                  case MENU_ENUM_LABEL_SUBSYSTEM_ADD:
                     BIND_ACTION_OK(cbs, action_ok_subsystem_add);
                     break;
                  default:
                     BIND_ACTION_OK(cbs, action_ok_file_load);
                     break;
               }
            }
            else
            {
               switch (menu_label_hash)
               {
                  case MENU_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST:
                  case MENU_LABEL_FAVORITES:
                  case MENU_LABEL_DEFERRED_ARCHIVE_OPEN_DETECT_CORE:
#ifdef HAVE_COMPRESSION
                     if (type == FILE_TYPE_IN_CARCHIVE)
                     {
                        BIND_ACTION_OK(cbs, action_ok_file_load_with_detect_core_carchive);
                     }
                     else
#endif
                     {
                        BIND_ACTION_OK(cbs, action_ok_file_load_with_detect_core);
                     }
                     break;
                  case MENU_LABEL_DISK_IMAGE_APPEND:
                     BIND_ACTION_OK(cbs, action_ok_disk_image_append);
                     break;
                  case MENU_LABEL_SUBSYSTEM_ADD:
                     BIND_ACTION_OK(cbs, action_ok_subsystem_add);
                     break;
                  default:
                     BIND_ACTION_OK(cbs, action_ok_file_load);
                     break;
               }
            }
            break;
         case FILE_TYPE_MOVIE:
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
            /* TODO/FIXME - handle scan case */
            BIND_ACTION_OK(cbs, action_ok_file_load_ffmpeg);
#endif
            break;
         case FILE_TYPE_MUSIC:
            BIND_ACTION_OK(cbs, action_ok_file_load_music);
            break;
         case FILE_TYPE_IMAGEVIEWER:
            /* TODO/FIXME - handle scan case */
            BIND_ACTION_OK(cbs, action_ok_file_load_imageviewer);
            break;
         case FILE_TYPE_DIRECT_LOAD:
            BIND_ACTION_OK(cbs, action_ok_file_load);
            break;
         case MENU_SETTINGS:
         case MENU_SETTING_GROUP:
         case MENU_SETTING_SUBGROUP:
            BIND_ACTION_OK(cbs, action_ok_push_default);
            break;
         case MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_CYCLE_TRAY_STATUS:
            BIND_ACTION_OK(cbs, action_ok_disk_cycle_tray_status);
            break;
         case MENU_SETTINGS_CORE_OPTION_CREATE:
            BIND_ACTION_OK(cbs, action_ok_option_create);
            break;
         default:
            return -1;
      }
   }

   return 0;
}