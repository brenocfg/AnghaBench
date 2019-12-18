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
typedef  int /*<<< orphan*/  menu_file_list_cbs_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIND_ACTION_GET_VALUE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  FILE_TYPE_AUDIOFILTER 166 
#define  FILE_TYPE_CARCHIVE 165 
#define  FILE_TYPE_CHEAT 164 
#define  FILE_TYPE_CONFIG 163 
#define  FILE_TYPE_CORE 162 
#define  FILE_TYPE_CURSOR 161 
#define  FILE_TYPE_DIRECTORY 160 
#define  FILE_TYPE_DIRECT_LOAD 159 
#define  FILE_TYPE_DOWNLOAD_CORE 158 
#define  FILE_TYPE_FONT 157 
#define  FILE_TYPE_IMAGE 156 
#define  FILE_TYPE_IMAGEVIEWER 155 
#define  FILE_TYPE_IN_CARCHIVE 154 
#define  FILE_TYPE_MOVIE 153 
#define  FILE_TYPE_MUSIC 152 
#define  FILE_TYPE_OVERLAY 151 
#define  FILE_TYPE_PARENT_DIRECTORY 150 
#define  FILE_TYPE_PLAIN 149 
#define  FILE_TYPE_RDB 148 
#define  FILE_TYPE_SHADER 147 
#define  FILE_TYPE_SHADER_PRESET 146 
#define  FILE_TYPE_USE_DIRECTORY 145 
#define  FILE_TYPE_VIDEOFILTER 144 
#define  FILE_TYPE_VIDEO_LAYOUT 143 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_END ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_END ; 
 unsigned int MENU_SETTINGS_CHEAT_BEGIN ; 
 unsigned int MENU_SETTINGS_CHEAT_END ; 
#define  MENU_SETTINGS_CHEAT_MATCH 142 
#define  MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_INDEX 141 
#define  MENU_SETTINGS_CORE_OPTION_CREATE 140 
#define  MENU_SETTINGS_CUSTOM_BIND_ALL 139 
#define  MENU_SETTINGS_CUSTOM_BIND_DEFAULT_ALL 138 
 unsigned int MENU_SETTINGS_INPUT_DESC_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_END ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_KBD_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_KBD_END ; 
 unsigned int MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_BEGIN ; 
 unsigned int MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_END ; 
 unsigned int MENU_SETTINGS_PERF_COUNTERS_BEGIN ; 
 unsigned int MENU_SETTINGS_PERF_COUNTERS_END ; 
#define  MENU_SETTING_ACTION 137 
#define  MENU_SETTING_ACTION_CORE_DISK_OPTIONS 136 
#define  MENU_SETTING_ACTION_DELETE_ENTRY 135 
#define  MENU_SETTING_ACTION_LOADSTATE 134 
#define  MENU_SETTING_DROPDOWN_ITEM 133 
#define  MENU_SETTING_DROPDOWN_SETTING_FLOAT_ITEM 132 
#define  MENU_SETTING_DROPDOWN_SETTING_INT_ITEM 131 
#define  MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM 130 
#define  MENU_SETTING_NO_ITEM 129 
#define  MENU_SETTING_SUBGROUP 128 
 int /*<<< orphan*/  RARCH_LOG (char*,unsigned int) ; 
 int /*<<< orphan*/  menu_action_setting_audio_mixer_stream_name ; 
 int /*<<< orphan*/  menu_action_setting_audio_mixer_stream_volume ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_cheat ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_cheat_match ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_core_option_create ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_db_entry ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_entry ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_entry_url ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_input_desc ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_input_desc_kbd ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_libretro_perf_counters ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_disk_index ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_carchive ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_cheat ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_config ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_core ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_cursor ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_directory ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_filter ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_font ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_imageviewer ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_in_carchive ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_overlay ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_parent_directory ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_plain ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_rdb ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_shader ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_shader_preset ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_url_core ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_use_directory ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_file_video_layout ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_menu_more ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_movie ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_music ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_no_items ; 
 int /*<<< orphan*/  menu_action_setting_disp_set_label_perf_counters ; 

__attribute__((used)) static int menu_cbs_init_bind_get_string_representation_compare_type(
      menu_file_list_cbs_t *cbs, unsigned type)
{
#ifdef HAVE_AUDIOMIXER
   if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_BEGIN
      && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_END)
   {
      BIND_ACTION_GET_VALUE(cbs,
         menu_action_setting_audio_mixer_stream_name);
      return 0;
   }
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_BEGIN
         && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_END)
   {
      BIND_ACTION_GET_VALUE(cbs,
         menu_action_setting_audio_mixer_stream_volume);
   }
   else
#endif
   if (type >= MENU_SETTINGS_INPUT_DESC_BEGIN
         && type <= MENU_SETTINGS_INPUT_DESC_END)
   {
      BIND_ACTION_GET_VALUE(cbs,
         menu_action_setting_disp_set_label_input_desc);
   }
   else if (type >= MENU_SETTINGS_CHEAT_BEGIN
         && type <= MENU_SETTINGS_CHEAT_END)
   {
      BIND_ACTION_GET_VALUE(cbs,
         menu_action_setting_disp_set_label_cheat);
   }
   else if (type >= MENU_SETTINGS_PERF_COUNTERS_BEGIN
         && type <= MENU_SETTINGS_PERF_COUNTERS_END)
   {
      BIND_ACTION_GET_VALUE(cbs,
         menu_action_setting_disp_set_label_perf_counters);
   }
   else if (type >= MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_BEGIN
         && type <= MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_END)
   {
      BIND_ACTION_GET_VALUE(cbs,
         menu_action_setting_disp_set_label_libretro_perf_counters);
   }
   else if (type >= MENU_SETTINGS_INPUT_DESC_KBD_BEGIN
      && type <= MENU_SETTINGS_INPUT_DESC_KBD_END)
   {
      BIND_ACTION_GET_VALUE(cbs,
         menu_action_setting_disp_set_label_input_desc_kbd);
   }
   else
   {
      switch (type)
      {
         case MENU_SETTINGS_CORE_OPTION_CREATE:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_core_option_create);
            break;
         case FILE_TYPE_CORE:
         case FILE_TYPE_DIRECT_LOAD:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_core);
            break;
         case FILE_TYPE_PLAIN:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_plain);
            break;
         case FILE_TYPE_MOVIE:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_movie);
            break;
         case FILE_TYPE_MUSIC:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_music);
            break;
         case FILE_TYPE_IMAGE:
         case FILE_TYPE_IMAGEVIEWER:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_imageviewer);
            break;
         case FILE_TYPE_USE_DIRECTORY:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_use_directory);
            break;
         case FILE_TYPE_DIRECTORY:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_directory);
            break;
         case FILE_TYPE_PARENT_DIRECTORY:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_parent_directory);
            break;
         case FILE_TYPE_CARCHIVE:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_carchive);
            break;
         case FILE_TYPE_OVERLAY:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_overlay);
            break;
#ifdef HAVE_VIDEO_LAYOUT
         case FILE_TYPE_VIDEO_LAYOUT:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_video_layout);
            break;
#endif
         case FILE_TYPE_FONT:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_font);
            break;
         case FILE_TYPE_SHADER:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_shader);
            break;
         case FILE_TYPE_SHADER_PRESET:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_shader_preset);
            break;
         case FILE_TYPE_CONFIG:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_config);
            break;
         case FILE_TYPE_IN_CARCHIVE:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_in_carchive);
            break;
         case FILE_TYPE_VIDEOFILTER:
         case FILE_TYPE_AUDIOFILTER:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_filter);
            break;
         case FILE_TYPE_DOWNLOAD_CORE:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_url_core);
            break;
         case FILE_TYPE_RDB:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_rdb);
            break;
         case FILE_TYPE_CURSOR:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_cursor);
            break;
         case FILE_TYPE_CHEAT:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_file_cheat);
            break;
         case MENU_SETTINGS_CHEAT_MATCH:
            BIND_ACTION_GET_VALUE(cbs,
                  menu_action_setting_disp_set_label_cheat_match);
            break;
         case MENU_SETTING_SUBGROUP:
         case MENU_SETTINGS_CUSTOM_BIND_ALL:
         case MENU_SETTINGS_CUSTOM_BIND_DEFAULT_ALL:
         case MENU_SETTING_ACTION:
         case MENU_SETTING_ACTION_LOADSTATE:
         case 7:   /* Run */
         case MENU_SETTING_ACTION_DELETE_ENTRY:
         case MENU_SETTING_ACTION_CORE_DISK_OPTIONS:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_more);
            break;
         case MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_INDEX:
            BIND_ACTION_GET_VALUE(cbs,
               menu_action_setting_disp_set_label_menu_disk_index);
            break;
         case 31: /* Database entry */
            BIND_ACTION_GET_VALUE(cbs, menu_action_setting_disp_set_label_db_entry);
            break;
         case 25: /* URL directory entries */
         case 26: /* URL entries */
            BIND_ACTION_GET_VALUE(cbs, menu_action_setting_disp_set_label_entry_url);
            break;
         case MENU_SETTING_DROPDOWN_SETTING_INT_ITEM:
         case MENU_SETTING_DROPDOWN_SETTING_UINT_ITEM:
         case MENU_SETTING_DROPDOWN_SETTING_FLOAT_ITEM:
         case MENU_SETTING_DROPDOWN_ITEM:
         case MENU_SETTING_NO_ITEM:
            BIND_ACTION_GET_VALUE(cbs, menu_action_setting_disp_set_label_no_items);
            break;
         case 32: /* Recent history entry */
         case 65535: /* System info entry */
            BIND_ACTION_GET_VALUE(cbs, menu_action_setting_disp_set_label_entry);
            break;
         default:
#if 0
            RARCH_LOG("type: %d\n", type);
#endif
            BIND_ACTION_GET_VALUE(cbs, menu_action_setting_disp_set_label);
            break;
      }
   }

   return 0;
}