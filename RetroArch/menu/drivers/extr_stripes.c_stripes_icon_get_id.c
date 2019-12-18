#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {uintptr_t content_icon; } ;
typedef  TYPE_2__ stripes_node_t ;
struct TYPE_8__ {uintptr_t* list; } ;
struct TYPE_10__ {int depth; TYPE_1__ textures; int /*<<< orphan*/  categories_selection_ptr; } ;
typedef  TYPE_3__ stripes_handle_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
#define  FILE_TYPE_CARCHIVE 194 
#define  FILE_TYPE_CORE 193 
#define  FILE_TYPE_CURSOR 192 
#define  FILE_TYPE_DIRECTORY 191 
#define  FILE_TYPE_DIRECT_LOAD 190 
#define  FILE_TYPE_IMAGE 189 
#define  FILE_TYPE_IMAGEVIEWER 188 
#define  FILE_TYPE_IN_CARCHIVE 187 
#define  FILE_TYPE_MOVIE 186 
#define  FILE_TYPE_MUSIC 185 
#define  FILE_TYPE_PLAIN 184 
#define  FILE_TYPE_PLAYLIST_ENTRY 183 
#define  FILE_TYPE_RDB 182 
#define  FILE_TYPE_RDB_ENTRY 181 
#define  FILE_TYPE_RPL_ENTRY 180 
#define  MENU_ENUM_LABEL_ACHIEVEMENT_LIST 179 
#define  MENU_ENUM_LABEL_ACHIEVEMENT_LIST_HARDCORE 178 
#define  MENU_ENUM_LABEL_ADD_TO_FAVORITES 177 
#define  MENU_ENUM_LABEL_ADD_TO_FAVORITES_PLAYLIST 176 
#define  MENU_ENUM_LABEL_CORE_CHEAT_OPTIONS 175 
#define  MENU_ENUM_LABEL_CORE_INPUT_REMAPPING_OPTIONS 174 
#define  MENU_ENUM_LABEL_CORE_OPTIONS 173 
#define  MENU_ENUM_LABEL_DELETE_ENTRY 172 
#define  MENU_ENUM_LABEL_DISK_OPTIONS 171 
#define  MENU_ENUM_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST 170 
#define  MENU_ENUM_LABEL_FAVORITES 169 
#define  MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR 168 
#define  MENU_ENUM_LABEL_LOAD_STATE 167 
#define  MENU_ENUM_LABEL_NAVIGATION_BROWSER_FILTER_SUPPORTED_EXTENSIONS_ENABLE 166 
#define  MENU_ENUM_LABEL_PARENT_DIRECTORY 165 
#define  MENU_ENUM_LABEL_PLAYLIST_MANAGER_RESET_CORES 164 
#define  MENU_ENUM_LABEL_RENAME_ENTRY 163 
#define  MENU_ENUM_LABEL_RESET_CORE_ASSOCIATION 162 
#define  MENU_ENUM_LABEL_RESTART_CONTENT 161 
#define  MENU_ENUM_LABEL_RESUME_CONTENT 160 
#define  MENU_ENUM_LABEL_SAVE_CURRENT_CONFIG_OVERRIDE_CORE 159 
#define  MENU_ENUM_LABEL_SAVE_CURRENT_CONFIG_OVERRIDE_GAME 158 
#define  MENU_ENUM_LABEL_SAVE_STATE 157 
#define  MENU_ENUM_LABEL_SET_CORE_ASSOCIATION 156 
#define  MENU_ENUM_LABEL_SHADER_OPTIONS 155 
#define  MENU_ENUM_LABEL_TAKE_SCREENSHOT 154 
#define  MENU_ENUM_LABEL_UNDO_LOAD_STATE 153 
#define  MENU_ENUM_LABEL_UNDO_SAVE_STATE 152 
#define  MENU_INFO_MESSAGE 151 
#define  MENU_ROOM 150 
#define  MENU_ROOM_LAN 149 
#define  MENU_ROOM_MITM 148 
 unsigned int MENU_SETTINGS_CHEEVOS_START ; 
 unsigned int MENU_SETTINGS_NETPLAY_ROOMS_START ; 
#define  MENU_SETTING_ACTION 147 
#define  MENU_SETTING_ACTION_CLOSE 146 
#define  MENU_SETTING_ACTION_CORE_CHEAT_OPTIONS 145 
#define  MENU_SETTING_ACTION_CORE_DISK_OPTIONS 144 
#define  MENU_SETTING_ACTION_CORE_INFORMATION 143 
#define  MENU_SETTING_ACTION_CORE_INPUT_REMAPPING_OPTIONS 142 
#define  MENU_SETTING_ACTION_CORE_OPTIONS 141 
#define  MENU_SETTING_ACTION_CORE_SHADER_OPTIONS 140 
#define  MENU_SETTING_ACTION_DELETE_ENTRY 139 
#define  MENU_SETTING_ACTION_LOADSTATE 138 
#define  MENU_SETTING_ACTION_RESET 137 
#define  MENU_SETTING_ACTION_RUN 136 
#define  MENU_SETTING_ACTION_SAVESTATE 135 
#define  MENU_SETTING_ACTION_SCREENSHOT 134 
#define  MENU_SETTING_GROUP 133 
#define  MENU_WIFI 132 
#define  STRIPES_SYSTEM_TAB_FAVORITES 131 
#define  STRIPES_SYSTEM_TAB_IMAGES 130 
#define  STRIPES_SYSTEM_TAB_MUSIC 129 
#define  STRIPES_SYSTEM_TAB_VIDEO 128 
 size_t STRIPES_TEXTURE_ACHIEVEMENT_LIST ; 
 size_t STRIPES_TEXTURE_ADD_FAVORITE ; 
 size_t STRIPES_TEXTURE_CHEAT_OPTIONS ; 
 size_t STRIPES_TEXTURE_CLOSE ; 
 size_t STRIPES_TEXTURE_CORE ; 
 size_t STRIPES_TEXTURE_CORE_INFO ; 
 size_t STRIPES_TEXTURE_CORE_OPTIONS ; 
 size_t STRIPES_TEXTURE_CURSOR ; 
 size_t STRIPES_TEXTURE_DISK_OPTIONS ; 
 size_t STRIPES_TEXTURE_FAVORITE ; 
 size_t STRIPES_TEXTURE_FILE ; 
 size_t STRIPES_TEXTURE_FOLDER ; 
 size_t STRIPES_TEXTURE_IMAGE ; 
 size_t STRIPES_TEXTURE_INPUT_REMAPPING_OPTIONS ; 
 size_t STRIPES_TEXTURE_LOADSTATE ; 
 size_t STRIPES_TEXTURE_MOVIE ; 
 size_t STRIPES_TEXTURE_MUSIC ; 
 size_t STRIPES_TEXTURE_RDB ; 
 size_t STRIPES_TEXTURE_RELOAD ; 
 size_t STRIPES_TEXTURE_RENAME ; 
 size_t STRIPES_TEXTURE_RESUME ; 
 size_t STRIPES_TEXTURE_ROOM ; 
 size_t STRIPES_TEXTURE_ROOM_LAN ; 
 size_t STRIPES_TEXTURE_ROOM_MITM ; 
 size_t STRIPES_TEXTURE_RUN ; 
 size_t STRIPES_TEXTURE_SAVESTATE ; 
 size_t STRIPES_TEXTURE_SCREENSHOT ; 
 size_t STRIPES_TEXTURE_SETTING ; 
 size_t STRIPES_TEXTURE_SHADER_OPTIONS ; 
 size_t STRIPES_TEXTURE_SUBSETTING ; 
 size_t STRIPES_TEXTURE_UNDO ; 
 size_t STRIPES_TEXTURE_WIFI ; 
 size_t STRIPES_TEXTURE_ZIP ; 
 uintptr_t get_badge_texture (int) ; 
 int /*<<< orphan*/  stripes_get_system_tab (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static uintptr_t stripes_icon_get_id(stripes_handle_t *stripes,
      stripes_node_t *core_node, stripes_node_t *node,
      enum msg_hash_enums enum_idx, unsigned type, bool active)
{
   switch (enum_idx)
   {
      case MENU_ENUM_LABEL_CORE_OPTIONS:
      case MENU_ENUM_LABEL_NAVIGATION_BROWSER_FILTER_SUPPORTED_EXTENSIONS_ENABLE:
         return stripes->textures.list[STRIPES_TEXTURE_CORE_OPTIONS];
      case MENU_ENUM_LABEL_ADD_TO_FAVORITES:
      case MENU_ENUM_LABEL_ADD_TO_FAVORITES_PLAYLIST:
         return stripes->textures.list[STRIPES_TEXTURE_ADD_FAVORITE];
      case MENU_ENUM_LABEL_RESET_CORE_ASSOCIATION:
      case MENU_ENUM_LABEL_PLAYLIST_MANAGER_RESET_CORES:
         return stripes->textures.list[STRIPES_TEXTURE_RENAME];
      case MENU_ENUM_LABEL_CORE_INPUT_REMAPPING_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_INPUT_REMAPPING_OPTIONS];
      case MENU_ENUM_LABEL_CORE_CHEAT_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_CHEAT_OPTIONS];
      case MENU_ENUM_LABEL_DISK_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_DISK_OPTIONS];
      case MENU_ENUM_LABEL_SHADER_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_SHADER_OPTIONS];
      case MENU_ENUM_LABEL_ACHIEVEMENT_LIST:
         return stripes->textures.list[STRIPES_TEXTURE_ACHIEVEMENT_LIST];
      case MENU_ENUM_LABEL_ACHIEVEMENT_LIST_HARDCORE:
         return stripes->textures.list[STRIPES_TEXTURE_ACHIEVEMENT_LIST];
      case MENU_ENUM_LABEL_SAVE_STATE:
         return stripes->textures.list[STRIPES_TEXTURE_SAVESTATE];
      case MENU_ENUM_LABEL_LOAD_STATE:
         return stripes->textures.list[STRIPES_TEXTURE_LOADSTATE];
      case MENU_ENUM_LABEL_PARENT_DIRECTORY:
      case MENU_ENUM_LABEL_UNDO_LOAD_STATE:
      case MENU_ENUM_LABEL_UNDO_SAVE_STATE:
         return stripes->textures.list[STRIPES_TEXTURE_UNDO];
      case MENU_ENUM_LABEL_TAKE_SCREENSHOT:
         return stripes->textures.list[STRIPES_TEXTURE_SCREENSHOT];
      case MENU_ENUM_LABEL_DELETE_ENTRY:
         return stripes->textures.list[STRIPES_TEXTURE_CLOSE];
      case MENU_ENUM_LABEL_RESTART_CONTENT:
         return stripes->textures.list[STRIPES_TEXTURE_RELOAD];
      case MENU_ENUM_LABEL_RENAME_ENTRY:
         return stripes->textures.list[STRIPES_TEXTURE_RENAME];
      case MENU_ENUM_LABEL_RESUME_CONTENT:
         return stripes->textures.list[STRIPES_TEXTURE_RESUME];
      case MENU_ENUM_LABEL_SAVE_CURRENT_CONFIG_OVERRIDE_CORE:
      case MENU_ENUM_LABEL_SAVE_CURRENT_CONFIG_OVERRIDE_GAME:
         return stripes->textures.list[STRIPES_TEXTURE_SAVESTATE];
      case MENU_ENUM_LABEL_FAVORITES:
      case MENU_ENUM_LABEL_DOWNLOADED_FILE_DETECT_CORE_LIST:
         return stripes->textures.list[STRIPES_TEXTURE_FOLDER];
      case MENU_ENUM_LABEL_FILE_DETECT_CORE_LIST_PUSH_DIR:
         return stripes->textures.list[STRIPES_TEXTURE_RDB];
      default:
         break;
   }

   switch(type)
   {
      case FILE_TYPE_DIRECTORY:
         return stripes->textures.list[STRIPES_TEXTURE_FOLDER];
      case FILE_TYPE_PLAIN:
      case FILE_TYPE_IN_CARCHIVE:
         return stripes->textures.list[STRIPES_TEXTURE_FILE];
      case FILE_TYPE_RPL_ENTRY:
         if (core_node)
            return core_node->content_icon;

         switch (stripes_get_system_tab(stripes,
                  (unsigned)stripes->categories_selection_ptr))
         {
            case STRIPES_SYSTEM_TAB_FAVORITES:
               return stripes->textures.list[STRIPES_TEXTURE_FAVORITE];
            case STRIPES_SYSTEM_TAB_MUSIC:
               return stripes->textures.list[STRIPES_TEXTURE_MUSIC];
#ifdef HAVE_IMAGEVIEWER
            case STRIPES_SYSTEM_TAB_IMAGES:
               return stripes->textures.list[STRIPES_TEXTURE_IMAGE];
#endif
#ifdef HAVE_FFMPEG
            case STRIPES_SYSTEM_TAB_VIDEO:
               return stripes->textures.list[STRIPES_TEXTURE_MOVIE];
#endif
            default:
               break;
         }
         return stripes->textures.list[STRIPES_TEXTURE_FILE];
      case FILE_TYPE_CARCHIVE:
         return stripes->textures.list[STRIPES_TEXTURE_ZIP];
      case FILE_TYPE_MUSIC:
         return stripes->textures.list[STRIPES_TEXTURE_MUSIC];
      case FILE_TYPE_IMAGE:
      case FILE_TYPE_IMAGEVIEWER:
         return stripes->textures.list[STRIPES_TEXTURE_IMAGE];
      case FILE_TYPE_MOVIE:
         return stripes->textures.list[STRIPES_TEXTURE_MOVIE];
      case FILE_TYPE_CORE:
      case FILE_TYPE_DIRECT_LOAD:
         return stripes->textures.list[STRIPES_TEXTURE_CORE];
      case FILE_TYPE_RDB:
         return stripes->textures.list[STRIPES_TEXTURE_RDB];
      case FILE_TYPE_CURSOR:
         return stripes->textures.list[STRIPES_TEXTURE_CURSOR];
      case FILE_TYPE_PLAYLIST_ENTRY:
      case MENU_SETTING_ACTION_RUN:
         return stripes->textures.list[STRIPES_TEXTURE_RUN];
      case MENU_SETTING_ACTION_CLOSE:
         return stripes->textures.list[STRIPES_TEXTURE_CLOSE];
      case MENU_SETTING_ACTION_SAVESTATE:
         return stripes->textures.list[STRIPES_TEXTURE_SAVESTATE];
      case MENU_SETTING_ACTION_LOADSTATE:
         return stripes->textures.list[STRIPES_TEXTURE_LOADSTATE];
      case FILE_TYPE_RDB_ENTRY:
      case MENU_SETTING_ACTION_CORE_INFORMATION:
         return stripes->textures.list[STRIPES_TEXTURE_CORE_INFO];
      case MENU_SETTING_ACTION_CORE_OPTIONS:
      case MENU_ENUM_LABEL_SET_CORE_ASSOCIATION:
         return stripes->textures.list[STRIPES_TEXTURE_CORE_OPTIONS];
      case MENU_SETTING_ACTION_CORE_INPUT_REMAPPING_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_INPUT_REMAPPING_OPTIONS];
      case MENU_SETTING_ACTION_CORE_CHEAT_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_CHEAT_OPTIONS];
      case MENU_SETTING_ACTION_CORE_DISK_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_DISK_OPTIONS];
      case MENU_SETTING_ACTION_CORE_SHADER_OPTIONS:
         return stripes->textures.list[STRIPES_TEXTURE_SHADER_OPTIONS];
      case MENU_SETTING_ACTION_SCREENSHOT:
         return stripes->textures.list[STRIPES_TEXTURE_SCREENSHOT];
      case MENU_SETTING_ACTION_DELETE_ENTRY:
         return stripes->textures.list[STRIPES_TEXTURE_CLOSE];
      case MENU_SETTING_ACTION_RESET:
         return stripes->textures.list[STRIPES_TEXTURE_RELOAD];
      case MENU_SETTING_ACTION:
         if (stripes->depth == 3)
            return stripes->textures.list[STRIPES_TEXTURE_SUBSETTING];
         return stripes->textures.list[STRIPES_TEXTURE_SETTING];
      case MENU_SETTING_GROUP:
         return stripes->textures.list[STRIPES_TEXTURE_SETTING];
      case MENU_INFO_MESSAGE:
         return stripes->textures.list[STRIPES_TEXTURE_CORE_INFO];
      case MENU_WIFI:
         return stripes->textures.list[STRIPES_TEXTURE_WIFI];
#ifdef HAVE_NETWORKING
      case MENU_ROOM:
         return stripes->textures.list[STRIPES_TEXTURE_ROOM];
#if 0
      /* stub these out until we have the icons */
      case MENU_ROOM_LAN:
         return stripes->textures.list[STRIPES_TEXTURE_ROOM_LAN];
      case MENU_ROOM_MITM:
         return stripes->textures.list[STRIPES_TEXTURE_ROOM_MITM];
#endif
#endif
   }

#ifdef HAVE_CHEEVOS
   if (
         (type >= MENU_SETTINGS_CHEEVOS_START) &&
         (type < MENU_SETTINGS_NETPLAY_ROOMS_START)
      )
   {
      int new_id = type - MENU_SETTINGS_CHEEVOS_START;
      if (get_badge_texture(new_id) != 0)
         return get_badge_texture(new_id);
      /* Should be replaced with placeholder badge icon. */
      return stripes->textures.list[STRIPES_TEXTURE_SUBSETTING];
   }
#endif

   return stripes->textures.list[STRIPES_TEXTURE_SUBSETTING];
}