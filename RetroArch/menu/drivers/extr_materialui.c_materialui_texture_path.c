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
#define  MUI_TEXTURE_ADD 194 
#define  MUI_TEXTURE_ADD_TO_FAVORITES 193 
#define  MUI_TEXTURE_ADD_TO_MIXER 192 
#define  MUI_TEXTURE_ARCHIVE 191 
#define  MUI_TEXTURE_BACK 190 
#define  MUI_TEXTURE_BATTERY_100 189 
#define  MUI_TEXTURE_BATTERY_20 188 
#define  MUI_TEXTURE_BATTERY_30 187 
#define  MUI_TEXTURE_BATTERY_50 186 
#define  MUI_TEXTURE_BATTERY_60 185 
#define  MUI_TEXTURE_BATTERY_80 184 
#define  MUI_TEXTURE_BATTERY_90 183 
#define  MUI_TEXTURE_BATTERY_CHARGING 182 
#define  MUI_TEXTURE_BATTERY_CRITICAL 181 
#define  MUI_TEXTURE_CHECKMARK 180 
#define  MUI_TEXTURE_CLOSE 179 
#define  MUI_TEXTURE_CONFIGURATIONS 178 
#define  MUI_TEXTURE_CONTROLS 177 
#define  MUI_TEXTURE_CORES 176 
#define  MUI_TEXTURE_CORE_CHEAT_OPTIONS 175 
#define  MUI_TEXTURE_CORE_OPTIONS 174 
#define  MUI_TEXTURE_DATABASE 173 
#define  MUI_TEXTURE_DISK 172 
#define  MUI_TEXTURE_EJECT 171 
#define  MUI_TEXTURE_FILE 170 
#define  MUI_TEXTURE_FOLDER 169 
#define  MUI_TEXTURE_HELP 168 
#define  MUI_TEXTURE_HISTORY 167 
#define  MUI_TEXTURE_IMAGE 166 
#define  MUI_TEXTURE_INFO 165 
#define  MUI_TEXTURE_KEY 164 
#define  MUI_TEXTURE_KEY_HOVER 163 
#define  MUI_TEXTURE_LOAD_CONTENT 162 
#define  MUI_TEXTURE_LOAD_STATE 161 
#define  MUI_TEXTURE_MUSIC 160 
#define  MUI_TEXTURE_NETPLAY 159 
#define  MUI_TEXTURE_PARENT_DIRECTORY 158 
#define  MUI_TEXTURE_PLAYLIST 157 
#define  MUI_TEXTURE_POINTER 156 
#define  MUI_TEXTURE_QUICKMENU 155 
#define  MUI_TEXTURE_QUIT 154 
#define  MUI_TEXTURE_REMOVE 153 
#define  MUI_TEXTURE_RENAME 152 
#define  MUI_TEXTURE_RESTART 151 
#define  MUI_TEXTURE_RESUME 150 
#define  MUI_TEXTURE_RUN 149 
#define  MUI_TEXTURE_SAVE_STATE 148 
#define  MUI_TEXTURE_SCAN 147 
#define  MUI_TEXTURE_SEARCH 146 
#define  MUI_TEXTURE_SETTINGS 145 
#define  MUI_TEXTURE_SHADERS 144 
#define  MUI_TEXTURE_START_CORE 143 
#define  MUI_TEXTURE_STATE_SLOT 142 
#define  MUI_TEXTURE_SWITCH_BG 141 
#define  MUI_TEXTURE_SWITCH_OFF 140 
#define  MUI_TEXTURE_SWITCH_ON 139 
#define  MUI_TEXTURE_SWITCH_VIEW 138 
#define  MUI_TEXTURE_TAB_BACK 137 
#define  MUI_TEXTURE_TAB_MAIN 136 
#define  MUI_TEXTURE_TAB_PLAYLISTS 135 
#define  MUI_TEXTURE_TAB_RESUME 134 
#define  MUI_TEXTURE_TAB_SETTINGS 133 
#define  MUI_TEXTURE_TAKE_SCREENSHOT 132 
#define  MUI_TEXTURE_UNDO_LOAD_STATE 131 
#define  MUI_TEXTURE_UNDO_SAVE_STATE 130 
#define  MUI_TEXTURE_UPDATER 129 
#define  MUI_TEXTURE_VIDEO 128 

__attribute__((used)) static const char *materialui_texture_path(unsigned id)
{
   switch (id)
   {
      case MUI_TEXTURE_POINTER:
         return "pointer.png";
      case MUI_TEXTURE_BACK:
         return "back.png";
      case MUI_TEXTURE_SWITCH_ON:
         return "switch_on.png";
      case MUI_TEXTURE_SWITCH_OFF:
         return "switch_off.png";
      case MUI_TEXTURE_SWITCH_BG:
         return "switch_bg.png";
      case MUI_TEXTURE_TAB_MAIN:
         return "main_tab_passive.png";
      case MUI_TEXTURE_TAB_PLAYLISTS:
         return "playlists_tab_passive.png";
      case MUI_TEXTURE_TAB_SETTINGS:
         return "settings_tab_passive.png";
      case MUI_TEXTURE_TAB_BACK:
         return "back_tab.png";
      case MUI_TEXTURE_TAB_RESUME:
         return "resume_tab.png";
      case MUI_TEXTURE_KEY:
         return "key.png";
      case MUI_TEXTURE_KEY_HOVER:
         return "key-hover.png";
      case MUI_TEXTURE_FOLDER:
         return "folder.png";
      case MUI_TEXTURE_PARENT_DIRECTORY:
         return "parent_directory.png";
      case MUI_TEXTURE_IMAGE:
         return "image.png";
      case MUI_TEXTURE_VIDEO:
         return "video.png";
      case MUI_TEXTURE_MUSIC:
         return "music.png";
      case MUI_TEXTURE_ARCHIVE:
         return "archive.png";
      case MUI_TEXTURE_QUIT:
         return "quit.png";
      case MUI_TEXTURE_HELP:
         return "help.png";
      case MUI_TEXTURE_NETPLAY:
         return "netplay.png";
      case MUI_TEXTURE_CORES:
         return "cores.png";
      case MUI_TEXTURE_CONTROLS:
         return "controls.png";
      case MUI_TEXTURE_RESUME:
         return "resume.png";
      case MUI_TEXTURE_RESTART:
         return "restart.png";
      case MUI_TEXTURE_CLOSE:
         return "close.png";
      case MUI_TEXTURE_CORE_OPTIONS:
         return "core_options.png";
      case MUI_TEXTURE_CORE_CHEAT_OPTIONS:
         return "core_cheat_options.png";
      case MUI_TEXTURE_SHADERS:
         return "shaders.png";
      case MUI_TEXTURE_ADD_TO_FAVORITES:
         return "add_to_favorites.png";
      case MUI_TEXTURE_RUN:
         return "run.png";
      case MUI_TEXTURE_RENAME:
         return "rename.png";
      case MUI_TEXTURE_DATABASE:
         return "database.png";
      case MUI_TEXTURE_ADD_TO_MIXER:
         return "add_to_mixer.png";
      case MUI_TEXTURE_SCAN:
         return "scan.png";
      case MUI_TEXTURE_REMOVE:
         return "remove.png";
      case MUI_TEXTURE_START_CORE:
         return "start_core.png";
      case MUI_TEXTURE_LOAD_STATE:
         return "load_state.png";
      case MUI_TEXTURE_SAVE_STATE:
         return "save_state.png";
      case MUI_TEXTURE_DISK:
         return "disk.png";
      case MUI_TEXTURE_EJECT:
         return "eject.png";
      case MUI_TEXTURE_CHECKMARK:
         return "menu_check.png";
      case MUI_TEXTURE_UNDO_LOAD_STATE:
         return "undo_load_state.png";
      case MUI_TEXTURE_UNDO_SAVE_STATE:
         return "undo_save_state.png";
      case MUI_TEXTURE_STATE_SLOT:
         return "state_slot.png";
      case MUI_TEXTURE_TAKE_SCREENSHOT:
         return "take_screenshot.png";
      case MUI_TEXTURE_CONFIGURATIONS:
         return "configurations.png";
      case MUI_TEXTURE_LOAD_CONTENT:
         return "load_content.png";
      case MUI_TEXTURE_UPDATER:
         return "update.png";
      case MUI_TEXTURE_QUICKMENU:
         return "quickmenu.png";
      case MUI_TEXTURE_HISTORY:
         return "history.png";
      case MUI_TEXTURE_INFO:
         return "information.png";
      case MUI_TEXTURE_ADD:
         return "add.png";
      case MUI_TEXTURE_SETTINGS:
         return "settings.png";
      case MUI_TEXTURE_FILE:
         return "file.png";
      case MUI_TEXTURE_PLAYLIST:
         return "playlist.png";
      case MUI_TEXTURE_SEARCH:
         return "search.png";
      case MUI_TEXTURE_BATTERY_CRITICAL:
         return "battery_critical.png";
      case MUI_TEXTURE_BATTERY_20:
         return "battery_20.png";
      case MUI_TEXTURE_BATTERY_30:
         return "battery_30.png";
      case MUI_TEXTURE_BATTERY_50:
         return "battery_50.png";
      case MUI_TEXTURE_BATTERY_60:
         return "battery_60.png";
      case MUI_TEXTURE_BATTERY_80:
         return "battery_80.png";
      case MUI_TEXTURE_BATTERY_90:
         return "battery_90.png";
      case MUI_TEXTURE_BATTERY_100:
         return "battery_100.png";
      case MUI_TEXTURE_BATTERY_CHARGING:
         return "battery_charging.png";
      case MUI_TEXTURE_SWITCH_VIEW:
         return "switch_view.png";
   }

   return NULL;
}