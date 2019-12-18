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
#define  STRIPES_TEXTURE_ACHIEVEMENT_LIST 177 
#define  STRIPES_TEXTURE_ADD 176 
#define  STRIPES_TEXTURE_ADD_FAVORITE 175 
#define  STRIPES_TEXTURE_ARROW 174 
#define  STRIPES_TEXTURE_BATTERY_CHARGING 173 
#define  STRIPES_TEXTURE_BATTERY_FULL 172 
#define  STRIPES_TEXTURE_CHEAT_OPTIONS 171 
#define  STRIPES_TEXTURE_CLOCK 170 
#define  STRIPES_TEXTURE_CLOSE 169 
#define  STRIPES_TEXTURE_CORE 168 
#define  STRIPES_TEXTURE_CORE_INFO 167 
#define  STRIPES_TEXTURE_CORE_OPTIONS 166 
#define  STRIPES_TEXTURE_CURSOR 165 
#define  STRIPES_TEXTURE_DIALOG_SLICE 164 
#define  STRIPES_TEXTURE_DISK_OPTIONS 163 
#define  STRIPES_TEXTURE_FAVORITE 162 
#define  STRIPES_TEXTURE_FAVORITES 161 
#define  STRIPES_TEXTURE_FILE 160 
#define  STRIPES_TEXTURE_FOLDER 159 
#define  STRIPES_TEXTURE_HISTORY 158 
#define  STRIPES_TEXTURE_IMAGE 157 
#define  STRIPES_TEXTURE_IMAGES 156 
#define  STRIPES_TEXTURE_INPUT_REMAPPING_OPTIONS 155 
#define  STRIPES_TEXTURE_KEY 154 
#define  STRIPES_TEXTURE_KEY_HOVER 153 
#define  STRIPES_TEXTURE_LOADSTATE 152 
#define  STRIPES_TEXTURE_MAIN_MENU 151 
#define  STRIPES_TEXTURE_MOVIE 150 
#define  STRIPES_TEXTURE_MOVIES 149 
#define  STRIPES_TEXTURE_MUSIC 148 
#define  STRIPES_TEXTURE_MUSICS 147 
#define  STRIPES_TEXTURE_NETPLAY 146 
#define  STRIPES_TEXTURE_POINTER 145 
#define  STRIPES_TEXTURE_RDB 144 
#define  STRIPES_TEXTURE_RELOAD 143 
#define  STRIPES_TEXTURE_RENAME 142 
#define  STRIPES_TEXTURE_RESUME 141 
#define  STRIPES_TEXTURE_ROOM 140 
#define  STRIPES_TEXTURE_RUN 139 
#define  STRIPES_TEXTURE_SAVESTATE 138 
#define  STRIPES_TEXTURE_SCREENSHOT 137 
#define  STRIPES_TEXTURE_SETTING 136 
#define  STRIPES_TEXTURE_SETTINGS 135 
#define  STRIPES_TEXTURE_SHADER_OPTIONS 134 
#define  STRIPES_TEXTURE_SUBSETTING 133 
#define  STRIPES_TEXTURE_SWITCH_OFF 132 
#define  STRIPES_TEXTURE_SWITCH_ON 131 
#define  STRIPES_TEXTURE_UNDO 130 
#define  STRIPES_TEXTURE_WIFI 129 
#define  STRIPES_TEXTURE_ZIP 128 

__attribute__((used)) static const char *stripes_texture_path(unsigned id)
{
   switch (id)
   {
      case STRIPES_TEXTURE_MAIN_MENU:
#if defined(HAVE_LAKKA)
         return "lakka.png";
#else
         return "retroarch.png";
#endif
      case STRIPES_TEXTURE_SETTINGS:
         return "settings.png";
      case STRIPES_TEXTURE_HISTORY:
         return "history.png";
      case STRIPES_TEXTURE_FAVORITES:
         return "favorites.png";
      case STRIPES_TEXTURE_ADD_FAVORITE:
         return "add-favorite.png";
      case STRIPES_TEXTURE_MUSICS:
         return "musics.png";
#ifdef HAVE_FFMPEG
      case STRIPES_TEXTURE_MOVIES:
         return "movies.png";
#endif
#ifdef HAVE_IMAGEVIEWER
      case STRIPES_TEXTURE_IMAGES:
         return "images.png";
#endif
      case STRIPES_TEXTURE_SETTING:
         return "setting.png";
      case STRIPES_TEXTURE_SUBSETTING:
         return "subsetting.png";
      case STRIPES_TEXTURE_ARROW:
         return "arrow.png";
      case STRIPES_TEXTURE_RUN:
         return "run.png";
      case STRIPES_TEXTURE_CLOSE:
         return "close.png";
      case STRIPES_TEXTURE_RESUME:
         return "resume.png";
      case STRIPES_TEXTURE_CLOCK:
         return "clock.png";
      case STRIPES_TEXTURE_BATTERY_FULL:
         return "battery-full.png";
      case STRIPES_TEXTURE_BATTERY_CHARGING:
         return "battery-charging.png";
      case STRIPES_TEXTURE_POINTER:
         return "pointer.png";
      case STRIPES_TEXTURE_SAVESTATE:
         return "savestate.png";
      case STRIPES_TEXTURE_LOADSTATE:
         return "loadstate.png";
      case STRIPES_TEXTURE_UNDO:
         return "undo.png";
      case STRIPES_TEXTURE_CORE_INFO:
         return "core-infos.png";
      case STRIPES_TEXTURE_WIFI:
         return "wifi.png";
      case STRIPES_TEXTURE_CORE_OPTIONS:
         return "core-options.png";
      case STRIPES_TEXTURE_INPUT_REMAPPING_OPTIONS:
         return "core-input-remapping-options.png";
      case STRIPES_TEXTURE_CHEAT_OPTIONS:
         return "core-cheat-options.png";
      case STRIPES_TEXTURE_DISK_OPTIONS:
         return "core-disk-options.png";
      case STRIPES_TEXTURE_SHADER_OPTIONS:
         return "core-shader-options.png";
      case STRIPES_TEXTURE_ACHIEVEMENT_LIST:
         return "achievement-list.png";
      case STRIPES_TEXTURE_SCREENSHOT:
         return "screenshot.png";
      case STRIPES_TEXTURE_RELOAD:
         return "reload.png";
      case STRIPES_TEXTURE_RENAME:
         return "rename.png";
      case STRIPES_TEXTURE_FILE:
         return "file.png";
      case STRIPES_TEXTURE_FOLDER:
         return "folder.png";
      case STRIPES_TEXTURE_ZIP:
         return "zip.png";
      case STRIPES_TEXTURE_MUSIC:
         return "music.png";
      case STRIPES_TEXTURE_FAVORITE:
         return "favorites-content.png";
      case STRIPES_TEXTURE_IMAGE:
         return "image.png";
      case STRIPES_TEXTURE_MOVIE:
         return "movie.png";
      case STRIPES_TEXTURE_CORE:
         return "core.png";
      case STRIPES_TEXTURE_RDB:
         return "database.png";
      case STRIPES_TEXTURE_CURSOR:
         return "cursor.png";
      case STRIPES_TEXTURE_SWITCH_ON:
         return "on.png";
      case STRIPES_TEXTURE_SWITCH_OFF:
         return "off.png";
      case STRIPES_TEXTURE_ADD:
         return "add.png";
#ifdef HAVE_NETWORKING
      case STRIPES_TEXTURE_NETPLAY:
         return "netplay.png";
      case STRIPES_TEXTURE_ROOM:
         return "room.png";
      /* stub these out until we have the icons
      case STRIPES_TEXTURE_ROOM_LAN:
         return "room_lan.png";
      case STRIPES_TEXTURE_ROOM_MITM:
         return "room_mitm.png";
      */
#endif
      case STRIPES_TEXTURE_KEY:
         return "key.png";
      case STRIPES_TEXTURE_KEY_HOVER:
         return "key-hover.png";
      case STRIPES_TEXTURE_DIALOG_SLICE:
         return "dialog-slice.png";

   }

   return NULL;
}