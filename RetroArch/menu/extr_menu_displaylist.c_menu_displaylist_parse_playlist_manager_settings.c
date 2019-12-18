#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* menu_driver; } ;
struct TYPE_7__ {TYPE_1__ arrays; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  playlist_t ;
typedef  int /*<<< orphan*/  menu_handle_t ;
struct TYPE_8__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_3__ menu_displaylist_info_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_IMAGE_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_MUSIC_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_VIDEO_HISTORY ; 
 int /*<<< orphan*/  FILE_TYPE_PLAYLIST_ENTRY ; 
 int MENU_ENUM_LABEL_DELETE_PLAYLIST ; 
 int MENU_ENUM_LABEL_PLAYLIST_MANAGER_DEFAULT_CORE ; 
 int MENU_ENUM_LABEL_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE ; 
 int MENU_ENUM_LABEL_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE ; 
 int MENU_ENUM_LABEL_PLAYLIST_MANAGER_RESET_CORES ; 
 int MENU_ENUM_LABEL_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE ; 
 int MENU_ENUM_LABEL_VALUE_DELETE_PLAYLIST ; 
 int MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS ; 
 int MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS_MATERIALUI ; 
 int MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS_OZONE ; 
 int MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS_RGUI ; 
 int MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_DEFAULT_CORE ; 
 int MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE ; 
 int MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_RESET_CORES ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAILS ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAILS_MATERIALUI ; 
 int MENU_ENUM_LABEL_VALUE_THUMBNAILS_RGUI ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_DELETE_PLAYLIST ; 
 int /*<<< orphan*/  MENU_SETTING_PLAYLIST_MANAGER_DEFAULT_CORE ; 
 int /*<<< orphan*/  MENU_SETTING_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE ; 
 int /*<<< orphan*/  MENU_SETTING_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE ; 
 int /*<<< orphan*/  MENU_SETTING_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE ; 
 TYPE_2__* config_get_ptr () ; 
 char* file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_displaylist_set_new_playlist (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_hash_to_str (int) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 

__attribute__((used)) static bool menu_displaylist_parse_playlist_manager_settings(
      menu_handle_t *menu,
      menu_displaylist_info_t *info,
      const char *playlist_path)
{
   enum msg_hash_enums right_thumbnail_label_value;
   enum msg_hash_enums left_thumbnail_label_value;
   settings_t *settings      = config_get_ptr();
   const char *playlist_file = NULL;
   playlist_t *playlist      = NULL;

   if (!settings)
      return false;

   if (string_is_empty(playlist_path))
      return false;

   playlist_file = path_basename(playlist_path);

   if (string_is_empty(playlist_file))
      return false;

   menu_displaylist_set_new_playlist(menu, playlist_path);

   playlist = playlist_get_cached();

   if (!playlist)
      return false;

   /* Default core association
    * > This is only shown for collection playlists
    *   (i.e. it is not relevant for history/favourites) */
   if (!string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_HISTORY)) &&
       !string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_MUSIC_HISTORY)) &&
       !string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_VIDEO_HISTORY)) &&
       !string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_IMAGE_HISTORY)) &&
       !string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_FAVORITES)))
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_DEFAULT_CORE),
            msg_hash_to_str(MENU_ENUM_LABEL_PLAYLIST_MANAGER_DEFAULT_CORE),
            MENU_ENUM_LABEL_PLAYLIST_MANAGER_DEFAULT_CORE,
            MENU_SETTING_PLAYLIST_MANAGER_DEFAULT_CORE, 0, 0);

   /* Reset core associations */
   menu_entries_append_enum(info->list,
         msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_RESET_CORES),
         msg_hash_to_str(MENU_ENUM_LABEL_PLAYLIST_MANAGER_RESET_CORES),
         MENU_ENUM_LABEL_PLAYLIST_MANAGER_RESET_CORES,
         FILE_TYPE_PLAYLIST_ENTRY, 0, 0);

   /* Label display mode */
   menu_entries_append_enum(info->list,
         msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE),
         msg_hash_to_str(MENU_ENUM_LABEL_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE),
         MENU_ENUM_LABEL_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE,
         MENU_SETTING_PLAYLIST_MANAGER_LABEL_DISPLAY_MODE, 0, 0);

   /* Thumbnail modes */

   /* > Get label values */
   if (string_is_equal(settings->arrays.menu_driver, "rgui"))
   {
      right_thumbnail_label_value = MENU_ENUM_LABEL_VALUE_THUMBNAILS_RGUI;
      left_thumbnail_label_value  = MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS_RGUI;
   }
   else if (string_is_equal(settings->arrays.menu_driver, "ozone"))
   {
      right_thumbnail_label_value = MENU_ENUM_LABEL_VALUE_THUMBNAILS;
      left_thumbnail_label_value  = MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS_OZONE;
   }
   else if (string_is_equal(settings->arrays.menu_driver, "glui"))
   {
      right_thumbnail_label_value = MENU_ENUM_LABEL_VALUE_THUMBNAILS_MATERIALUI;
      left_thumbnail_label_value  = MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS_MATERIALUI;
   }
   else
   {
      right_thumbnail_label_value = MENU_ENUM_LABEL_VALUE_THUMBNAILS;
      left_thumbnail_label_value  = MENU_ENUM_LABEL_VALUE_LEFT_THUMBNAILS;
   }

   /* > Right thumbnail mode */
   menu_entries_append_enum(info->list,
         msg_hash_to_str(right_thumbnail_label_value),
         msg_hash_to_str(MENU_ENUM_LABEL_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE),
         MENU_ENUM_LABEL_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE,
         MENU_SETTING_PLAYLIST_MANAGER_RIGHT_THUMBNAIL_MODE, 0, 0);

   /* > Left thumbnail mode */
   menu_entries_append_enum(info->list,
         msg_hash_to_str(left_thumbnail_label_value),
         msg_hash_to_str(MENU_ENUM_LABEL_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE),
         MENU_ENUM_LABEL_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE,
         MENU_SETTING_PLAYLIST_MANAGER_LEFT_THUMBNAIL_MODE, 0, 0);

   /* TODO - Add:
    * - Remove invalid entries */

   menu_entries_append_enum(info->list,
         msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DELETE_PLAYLIST),
         msg_hash_to_str(MENU_ENUM_LABEL_DELETE_PLAYLIST),
         MENU_ENUM_LABEL_DELETE_PLAYLIST,
         MENU_SETTING_ACTION_DELETE_PLAYLIST, 0, 0);

   return true;
}