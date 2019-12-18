#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct string_list {unsigned int size; TYPE_3__* elems; } ;
struct TYPE_13__ {scalar_t__ history_list_enable; } ;
struct TYPE_10__ {int /*<<< orphan*/  directory_playlist; } ;
struct TYPE_14__ {TYPE_4__ bools; TYPE_1__ paths; } ;
typedef  TYPE_5__ settings_t ;
struct TYPE_15__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_6__ menu_displaylist_info_t ;
struct TYPE_16__ {scalar_t__ content_favorites; scalar_t__ content_history; } ;
struct TYPE_11__ {scalar_t__ i; } ;
struct TYPE_12__ {char* data; TYPE_2__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIR_LIST_COLLECTIONS ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_IMAGE_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_MUSIC_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_VIDEO_HISTORY ; 
 scalar_t__ FILE_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLIST_MANAGER_SETTINGS ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION ; 
 TYPE_5__* config_get_ptr () ; 
 struct string_list* dir_list_new_special (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dir_list_sort (struct string_list*,int) ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 TYPE_8__ g_defaults ; 
 scalar_t__ menu_entries_append_enum (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 char const* playlist_get_conf_path (scalar_t__) ; 
 scalar_t__ playlist_size (scalar_t__) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_equal_noncase (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 

__attribute__((used)) static unsigned menu_displaylist_parse_playlist_manager_list(
      menu_displaylist_info_t *info)
{
   settings_t      *settings    = config_get_ptr();
   unsigned count               = 0;
   struct string_list *str_list = NULL;

   if (!settings)
      return count;

   /* Add collection playlists */
   str_list = dir_list_new_special(
         settings->paths.directory_playlist,
         DIR_LIST_COLLECTIONS, NULL);

   if (str_list && str_list->size)
   {
      unsigned i;

      dir_list_sort(str_list, true);

      for (i = 0; i < str_list->size; i++)
      {
         const char *path          = str_list->elems[i].data;
         const char *playlist_file = NULL;

         if (str_list->elems[i].attr.i == FILE_TYPE_DIRECTORY)
            continue;

         if (string_is_empty(path))
            continue;

         playlist_file = path_basename(path);

         if (string_is_empty(playlist_file))
            continue;

         /* Ignore non-playlist files */
         if (!string_is_equal_noncase(path_get_extension(playlist_file),
                  "lpl"))
            continue;

         /* Ignore history/favourites
          * > content_history + favorites are handled separately
          * > music/video/image_history are ignored */
         if (string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_HISTORY)) ||
             string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_MUSIC_HISTORY)) ||
             string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_VIDEO_HISTORY)) ||
             string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_IMAGE_HISTORY)) ||
             string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_FAVORITES)))
            continue;

         menu_entries_append_enum(info->list,
               path,
               "",
               MENU_ENUM_LABEL_PLAYLIST_MANAGER_SETTINGS,
               MENU_SETTING_ACTION,
               0, 0);
         count++;
      }
   }

   /* Not necessary to check for NULL here */
   string_list_free(str_list);

   /* Add content history */
   if (settings->bools.history_list_enable)
      if (g_defaults.content_history)
         if (playlist_size(g_defaults.content_history) > 0)
            if (menu_entries_append_enum(info->list,
                  playlist_get_conf_path(g_defaults.content_history),
                  "",
                  MENU_ENUM_LABEL_PLAYLIST_MANAGER_SETTINGS,
                  MENU_SETTING_ACTION,
                  0, 0))
               count++;

   /* Add favourites */
   if (g_defaults.content_favorites)
      if (playlist_size(g_defaults.content_favorites) > 0)
         if (menu_entries_append_enum(info->list,
               playlist_get_conf_path(g_defaults.content_favorites),
               "",
               MENU_ENUM_LABEL_PLAYLIST_MANAGER_SETTINGS,
               MENU_SETTING_ACTION,
               0, 0))
            count++;

   return count;
}