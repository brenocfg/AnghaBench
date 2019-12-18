#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t size; TYPE_3__* elems; } ;
struct TYPE_8__ {int /*<<< orphan*/  show_hidden_files; scalar_t__ menu_content_show_video; scalar_t__ menu_content_show_music; scalar_t__ menu_content_show_images; scalar_t__ menu_content_show_favorites; scalar_t__ menu_content_show_add; } ;
struct TYPE_11__ {TYPE_1__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_12__ {char* path; int /*<<< orphan*/  list; int /*<<< orphan*/  type_default; } ;
typedef  TYPE_5__ menu_displaylist_info_t ;
typedef  enum msg_file_type { ____Placeholder_msg_file_type } msg_file_type ;
struct TYPE_9__ {int i; } ;
struct TYPE_10__ {char* data; TYPE_2__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_IMAGE_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_MUSIC_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_VIDEO_HISTORY ; 
 int FILE_TYPE_DIRECTORY ; 
 int FILE_TYPE_NONE ; 
 int FILE_TYPE_PLAYLIST_COLLECTION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_GOTO_FAVORITES ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_GOTO_IMAGES ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_GOTO_MUSIC ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_GOTO_VIDEO ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_PLAYLIST_COLLECTION_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SCAN_DIRECTORY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SCAN_FILE ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_GOTO_FAVORITES ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_GOTO_IMAGES ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_GOTO_MUSIC ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_GOTO_VIDEO ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SCAN_DIRECTORY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SCAN_FILE ; 
 int MENU_SETTING_ACTION ; 
 int /*<<< orphan*/  MSG_UNKNOWN ; 
#define  RARCH_DIRECTORY 129 
#define  RARCH_PLAIN_FILE 128 
 TYPE_4__* config_get_ptr () ; 
 struct string_list* dir_list_new (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dir_list_sort (struct string_list*,int) ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 int frontend_driver_parse_drive_list (int /*<<< orphan*/ ,int) ; 
 scalar_t__ menu_entries_append_enum (int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_equal_noncase (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 

__attribute__((used)) static unsigned menu_displaylist_parse_playlists(
      menu_displaylist_info_t *info, bool horizontal)
{
   size_t i, list_size;
   struct string_list *str_list = NULL;
   unsigned count               = 0;
   settings_t *settings         = config_get_ptr();
   const char *path             = info->path;

   if (string_is_empty(path))
   {
      int ret = frontend_driver_parse_drive_list(info->list, true);
      /* TODO/FIXME - we need to know the actual count number here */
      if (ret == 0)
         count++;
      else
         if (menu_entries_append_enum(info->list, "/", "",
               MSG_UNKNOWN, FILE_TYPE_DIRECTORY, 0, 0))
            count++;
      return count;
   }

   if (!horizontal)
   {
#ifdef HAVE_LIBRETRODB
      if (settings->bools.menu_content_show_add)
      {
         if (menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SCAN_DIRECTORY),
               msg_hash_to_str(MENU_ENUM_LABEL_SCAN_DIRECTORY),
               MENU_ENUM_LABEL_SCAN_DIRECTORY,
               MENU_SETTING_ACTION, 0, 0))
            count++;
         if (menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SCAN_FILE),
               msg_hash_to_str(MENU_ENUM_LABEL_SCAN_FILE),
               MENU_ENUM_LABEL_SCAN_FILE,
               MENU_SETTING_ACTION, 0, 0))
            count++;
      }
#endif
     if (settings->bools.menu_content_show_favorites)
      if (menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_GOTO_FAVORITES),
            msg_hash_to_str(MENU_ENUM_LABEL_GOTO_FAVORITES),
            MENU_ENUM_LABEL_GOTO_FAVORITES,
            MENU_SETTING_ACTION, 0, 0))
         count++;
     if (settings->bools.menu_content_show_images)
      if (menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_GOTO_IMAGES),
            msg_hash_to_str(MENU_ENUM_LABEL_GOTO_IMAGES),
            MENU_ENUM_LABEL_GOTO_IMAGES,
            MENU_SETTING_ACTION, 0, 0))
         count++;

     if (settings->bools.menu_content_show_music)
      if (menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_GOTO_MUSIC),
            msg_hash_to_str(MENU_ENUM_LABEL_GOTO_MUSIC),
            MENU_ENUM_LABEL_GOTO_MUSIC,
            MENU_SETTING_ACTION, 0, 0))
         count++;

#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
     if (settings->bools.menu_content_show_video)
      if (menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_GOTO_VIDEO),
            msg_hash_to_str(MENU_ENUM_LABEL_GOTO_VIDEO),
            MENU_ENUM_LABEL_GOTO_VIDEO,
            MENU_SETTING_ACTION, 0, 0))
         count++;
#endif
   }

   str_list = dir_list_new(path, NULL, true,
         settings->bools.show_hidden_files, true, false);

   if (!str_list)
      return count;

   dir_list_sort(str_list, true);

   list_size = str_list->size;

   for (i = 0; i < list_size; i++)
   {
      const char *path             = str_list->elems[i].data;
      const char *playlist_file    = NULL;
      enum msg_file_type file_type = FILE_TYPE_NONE;

      switch (str_list->elems[i].attr.i)
      {
         case RARCH_DIRECTORY:
            file_type = FILE_TYPE_DIRECTORY;
            break;
         case RARCH_PLAIN_FILE:
         default:
            file_type = (enum msg_file_type)info->type_default;
            break;
      }

      if (file_type == FILE_TYPE_DIRECTORY)
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

      /* Ignore history/favourites */
      if (string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_HISTORY)) ||
          string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_MUSIC_HISTORY)) ||
          string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_VIDEO_HISTORY)) ||
          string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_IMAGE_HISTORY)) ||
          string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_FAVORITES)))
         continue;

      file_type = FILE_TYPE_PLAYLIST_COLLECTION;

      if (horizontal)
         path = playlist_file;

      if (menu_entries_append_enum(info->list, path, "",
            MENU_ENUM_LABEL_PLAYLIST_COLLECTION_ENTRY,
            file_type, 0, 0))
         count++;
   }

   string_list_free(str_list);

   return count;
}