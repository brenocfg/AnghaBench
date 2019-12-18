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
 int /*<<< orphan*/  BIND_ACTION_RIGHT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  FILE_TYPE_AUDIOFILTER 165 
#define  FILE_TYPE_CARCHIVE 164 
#define  FILE_TYPE_CHEAT 163 
#define  FILE_TYPE_CONFIG 162 
#define  FILE_TYPE_CONTENTLIST_ENTRY 161 
#define  FILE_TYPE_CORE 160 
#define  FILE_TYPE_CURSOR 159 
#define  FILE_TYPE_DIRECTORY 158 
#define  FILE_TYPE_DOWNLOAD_CORE 157 
#define  FILE_TYPE_DOWNLOAD_CORE_CONTENT 156 
#define  FILE_TYPE_DOWNLOAD_THUMBNAIL_CONTENT 155 
#define  FILE_TYPE_DOWNLOAD_URL 154 
#define  FILE_TYPE_FONT 153 
#define  FILE_TYPE_IMAGE 152 
#define  FILE_TYPE_IMAGEVIEWER 151 
#define  FILE_TYPE_IN_CARCHIVE 150 
#define  FILE_TYPE_MOVIE 149 
#define  FILE_TYPE_MUSIC 148 
#define  FILE_TYPE_OVERLAY 147 
#define  FILE_TYPE_PARENT_DIRECTORY 146 
#define  FILE_TYPE_PLAIN 145 
#define  FILE_TYPE_PLAYLIST_COLLECTION 144 
#define  FILE_TYPE_PLAYLIST_ENTRY 143 
#define  FILE_TYPE_RDB 142 
#define  FILE_TYPE_RDB_ENTRY 141 
#define  FILE_TYPE_REMAP 140 
#define  FILE_TYPE_RPL_ENTRY 139 
#define  FILE_TYPE_SCAN_DIRECTORY 138 
#define  FILE_TYPE_SHADER 137 
#define  FILE_TYPE_SHADER_PRESET 136 
#define  FILE_TYPE_USE_DIRECTORY 135 
#define  FILE_TYPE_VIDEOFILTER 134 
#define  FILE_TYPE_VIDEO_LAYOUT 133 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HISTORY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_HORIZONTAL_MENU ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_IMAGES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_MUSIC_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_NETPLAY_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLISTS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SETTINGS_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VIDEO_TAB ; 
#define  MENU_INFO_MESSAGE 132 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_BEGIN ; 
 unsigned int MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_END ; 
 unsigned int MENU_SETTINGS_CHEAT_BEGIN ; 
 unsigned int MENU_SETTINGS_CHEAT_END ; 
 unsigned int MENU_SETTINGS_CHEEVOS_START ; 
#define  MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_INDEX 131 
#define  MENU_SETTINGS_CORE_INFO_NONE 130 
 unsigned int MENU_SETTINGS_CORE_OPTION_START ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_END ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_KBD_BEGIN ; 
 unsigned int MENU_SETTINGS_INPUT_DESC_KBD_END ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PARAMETER_LAST ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_0 ; 
 unsigned int MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST ; 
#define  MENU_SETTING_ACTION 129 
#define  MENU_SETTING_GROUP 128 
 int /*<<< orphan*/  action_right_cheat ; 
 int /*<<< orphan*/  action_right_input_desc ; 
 int /*<<< orphan*/  action_right_input_desc_kbd ; 
 int /*<<< orphan*/  action_right_mainmenu ; 
 int /*<<< orphan*/  action_right_scroll ; 
 int /*<<< orphan*/  audio_mixer_stream_volume_right ; 
 int /*<<< orphan*/  core_setting_right ; 
 int /*<<< orphan*/  disk_options_disk_idx_right ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shader_action_parameter_right ; 
 int /*<<< orphan*/  string_is_equal (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int menu_cbs_init_bind_right_compare_type(menu_file_list_cbs_t *cbs,
      unsigned type, const char *menu_label)
{
   if (type >= MENU_SETTINGS_CHEAT_BEGIN
         && type <= MENU_SETTINGS_CHEAT_END)
   {
      BIND_ACTION_RIGHT(cbs, action_right_cheat);
   }
#ifdef HAVE_AUDIOMIXER
   else if (type >= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_BEGIN
         && type <= MENU_SETTINGS_AUDIO_MIXER_STREAM_ACTIONS_VOLUME_END)
   {
      BIND_ACTION_RIGHT(cbs, audio_mixer_stream_volume_right);
   }
#endif
#if defined(HAVE_CG) || defined(HAVE_GLSL) || defined(HAVE_SLANG) || defined(HAVE_HLSL)
   else if (type >= MENU_SETTINGS_SHADER_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PARAMETER_LAST)
   {
      BIND_ACTION_RIGHT(cbs, shader_action_parameter_right);
   }
   else if (type >= MENU_SETTINGS_SHADER_PRESET_PARAMETER_0
         && type <= MENU_SETTINGS_SHADER_PRESET_PARAMETER_LAST)
   {
      BIND_ACTION_RIGHT(cbs, shader_action_parameter_right);
   }
#endif
   else if (type >= MENU_SETTINGS_INPUT_DESC_BEGIN
         && type <= MENU_SETTINGS_INPUT_DESC_END)
   {
      BIND_ACTION_RIGHT(cbs, action_right_input_desc);
   }
   else if (type >= MENU_SETTINGS_INPUT_DESC_KBD_BEGIN
      && type <= MENU_SETTINGS_INPUT_DESC_KBD_END)
   {
      BIND_ACTION_RIGHT(cbs, action_right_input_desc_kbd);
   }
   else if ((type >= MENU_SETTINGS_CORE_OPTION_START) &&
            (type < MENU_SETTINGS_CHEEVOS_START))
   {
      BIND_ACTION_RIGHT(cbs, core_setting_right);
   }
   else
   {
      switch (type)
      {
         case MENU_SETTINGS_CORE_DISK_OPTIONS_DISK_INDEX:
            BIND_ACTION_RIGHT(cbs, disk_options_disk_idx_right);
            break;
         case FILE_TYPE_PLAIN:
         case FILE_TYPE_DIRECTORY:
         case FILE_TYPE_PARENT_DIRECTORY:
         case FILE_TYPE_CARCHIVE:
         case FILE_TYPE_IN_CARCHIVE:
         case FILE_TYPE_CORE:
         case FILE_TYPE_RDB:
         case FILE_TYPE_RDB_ENTRY:
         case FILE_TYPE_RPL_ENTRY:
         case FILE_TYPE_CURSOR:
         case FILE_TYPE_SHADER:
         case FILE_TYPE_SHADER_PRESET:
         case FILE_TYPE_IMAGE:
         case FILE_TYPE_OVERLAY:
#ifdef HAVE_VIDEO_LAYOUT
         case FILE_TYPE_VIDEO_LAYOUT:
#endif
         case FILE_TYPE_VIDEOFILTER:
         case FILE_TYPE_AUDIOFILTER:
         case FILE_TYPE_CONFIG:
         case FILE_TYPE_USE_DIRECTORY:
         case FILE_TYPE_PLAYLIST_ENTRY:
         case MENU_INFO_MESSAGE:
         case FILE_TYPE_DOWNLOAD_CORE:
         case FILE_TYPE_CHEAT:
         case FILE_TYPE_REMAP:
         case FILE_TYPE_MOVIE:
         case FILE_TYPE_MUSIC:
         case FILE_TYPE_IMAGEVIEWER:
         case FILE_TYPE_PLAYLIST_COLLECTION:
         case FILE_TYPE_DOWNLOAD_CORE_CONTENT:
         case FILE_TYPE_DOWNLOAD_THUMBNAIL_CONTENT:
         case FILE_TYPE_DOWNLOAD_URL:
         case FILE_TYPE_SCAN_DIRECTORY:
         case FILE_TYPE_FONT:
         case MENU_SETTING_GROUP:
         case MENU_SETTINGS_CORE_INFO_NONE:
            if (  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_HISTORY_TAB))   ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_FAVORITES_TAB)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_PLAYLISTS_TAB)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_ADD_TAB)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_NETPLAY_TAB)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_MUSIC_TAB)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_IMAGES_TAB)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_VIDEO_TAB)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_HORIZONTAL_MENU)) ||
                  string_is_equal(menu_label, msg_hash_to_str(MENU_ENUM_LABEL_SETTINGS_TAB))
                  )
            {
               BIND_ACTION_RIGHT(cbs, action_right_mainmenu);
               break;
            }
            BIND_ACTION_RIGHT(cbs, action_right_scroll);
            break;
         case MENU_SETTING_ACTION:
         case FILE_TYPE_CONTENTLIST_ENTRY:
            BIND_ACTION_RIGHT(cbs, action_right_mainmenu);
            break;
         default:
            return -1;
      }
   }

   return 0;
}