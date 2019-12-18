#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t size; TYPE_4__* elems; } ;
struct retro_subsystem_info {size_t num_roms; TYPE_2__* roms; } ;
struct TYPE_16__ {int menu_navigation_browser_filter_supported_extensions_enable; scalar_t__ multimedia_builtin_imageviewer_enable; scalar_t__ multimedia_builtin_mediaplayer_enable; int /*<<< orphan*/  show_hidden_files; } ;
struct TYPE_17__ {TYPE_5__ bools; } ;
typedef  TYPE_6__ settings_t ;
struct TYPE_12__ {struct retro_subsystem_info* data; } ;
struct TYPE_18__ {TYPE_1__ subsystem; } ;
typedef  TYPE_7__ rarch_system_info_t ;
struct TYPE_19__ {char* path; scalar_t__ type_default; int /*<<< orphan*/  list; int /*<<< orphan*/ * exts; int /*<<< orphan*/  label; } ;
typedef  TYPE_8__ menu_displaylist_info_t ;
typedef  enum msg_hash_enums { ____Placeholder_msg_hash_enums } msg_hash_enums ;
typedef  enum msg_file_type { ____Placeholder_msg_file_type } msg_file_type ;
typedef  enum menu_displaylist_ctl_state { ____Placeholder_menu_displaylist_ctl_state } menu_displaylist_ctl_state ;
struct TYPE_14__ {int i; } ;
struct TYPE_15__ {char* data; TYPE_3__ attr; } ;
struct TYPE_13__ {int /*<<< orphan*/ * valid_extensions; } ;

/* Variables and functions */
#define  DISPLAYLIST_CORES_DETECTED 142 
 int DISPLAYLIST_IMAGES ; 
#define  FILEBROWSER_SCAN_DIR 141 
 int FILEBROWSER_SELECT_COLLECTION ; 
#define  FILEBROWSER_SELECT_DIR 140 
 int FILEBROWSER_SELECT_FILE_SUBSYSTEM ; 
 int FILEBROWSER_SELECT_FONT ; 
 int FILEBROWSER_SELECT_IMAGE ; 
 int FILE_TYPE_CARCHIVE ; 
#define  FILE_TYPE_DIRECTORY 139 
 int FILE_TYPE_FONT ; 
#define  FILE_TYPE_IMAGE 138 
#define  FILE_TYPE_IMAGEVIEWER 137 
 int FILE_TYPE_IN_CARCHIVE ; 
#define  FILE_TYPE_MOVIE 136 
#define  FILE_TYPE_MUSIC 135 
 int FILE_TYPE_NONE ; 
 int /*<<< orphan*/  FILE_TYPE_PARENT_DIRECTORY ; 
#define  FILE_TYPE_PLAIN 134 
 int FILE_TYPE_PLAYLIST_COLLECTION ; 
 int /*<<< orphan*/  FILE_TYPE_SCAN_DIRECTORY ; 
 scalar_t__ FILE_TYPE_SHADER ; 
 scalar_t__ FILE_TYPE_SHADER_PRESET ; 
 int /*<<< orphan*/  FILE_TYPE_USE_DIRECTORY ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_DIRECTORY ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_IMAGE ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_IMAGE_OPEN_WITH_VIEWER ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_MOVIE_OPEN ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_MUSIC_OPEN ; 
 int MENU_ENUM_LABEL_FILE_BROWSER_PLAIN_FILE ; 
 int MENU_ENUM_LABEL_NO_ITEMS ; 
 int MENU_ENUM_LABEL_PARENT_DIRECTORY ; 
 int MENU_ENUM_LABEL_SCAN_FILE ; 
 int MENU_ENUM_LABEL_SCAN_THIS_DIRECTORY ; 
 int MENU_ENUM_LABEL_USE_THIS_DIRECTORY ; 
 int MENU_ENUM_LABEL_VALUE_DIRECTORY_NOT_FOUND ; 
 int MENU_ENUM_LABEL_VALUE_NO_ITEMS ; 
 int MENU_ENUM_LABEL_VALUE_PARENT_DIRECTORY ; 
 int MENU_ENUM_LABEL_VALUE_SCAN_THIS_DIRECTORY ; 
 int MENU_ENUM_LABEL_VALUE_UNABLE_TO_READ_COMPRESSED_FILE ; 
 int MENU_ENUM_LABEL_VALUE_USE_THIS_DIRECTORY ; 
 int MENU_SETTING_NO_ITEM ; 
 int MSG_UNKNOWN ; 
#define  RARCH_COMPRESSED_ARCHIVE 133 
#define  RARCH_COMPRESSED_FILE_IN_ARCHIVE 132 
#define  RARCH_CONTENT_IMAGE 131 
#define  RARCH_CONTENT_MOVIE 130 
 int RARCH_CONTENT_MUSIC ; 
#define  RARCH_DIRECTORY 129 
#define  RARCH_PLAIN_FILE 128 
 TYPE_6__* config_get_ptr () ; 
 int content_get_subsystem () ; 
 size_t content_get_subsystem_rom_id () ; 
 struct string_list* dir_list_new (char const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dir_list_sort (struct string_list*,int) ; 
 struct string_list* file_archive_get_file_list (char const*,int /*<<< orphan*/ *) ; 
 int filebrowser_types ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,char const*,char const*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entries_prepend (int /*<<< orphan*/ ,char const*,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char const* msg_hash_to_str (int) ; 
 char* path_basename (char const*) ; 
 int path_is_compressed_file (char const*) ; 
 int path_is_media_type (char const*) ; 
 TYPE_7__* runloop_get_system_info () ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 scalar_t__ subsystem_current_count ; 
 struct retro_subsystem_info* subsystem_data ; 

void filebrowser_parse(menu_displaylist_info_t *info, unsigned type_data)
{
   size_t i, list_size;
   struct string_list *str_list         = NULL;
   unsigned items_found                 = 0;
   unsigned files_count                 = 0;
   unsigned dirs_count                  = 0;
   settings_t *settings                 = config_get_ptr();
   enum menu_displaylist_ctl_state type = (enum menu_displaylist_ctl_state)
                                          type_data;
   const char *path                     = info ? info->path : NULL;
   bool path_is_compressed              = !string_is_empty(path)
      ? path_is_compressed_file(path) : false;
   bool filter_ext                      =
      settings->bools.menu_navigation_browser_filter_supported_extensions_enable;

   rarch_system_info_t *system = runloop_get_system_info();
   const struct retro_subsystem_info *subsystem;

   /* Core fully loaded, use the subsystem data */
   if (system->subsystem.data)
      subsystem = system->subsystem.data + content_get_subsystem();
   /* Core not loaded completely, use the data we peeked on load core */
   else
      subsystem = subsystem_data + content_get_subsystem();

   if (info && (info->type_default == FILE_TYPE_SHADER_PRESET ||
                info->type_default == FILE_TYPE_SHADER))
      filter_ext = true;

   if (info && string_is_equal(info->label,
            msg_hash_to_str(MENU_ENUM_LABEL_SCAN_FILE)))
      filter_ext = false;

   if (info && path_is_compressed)
   {
      if (filebrowser_types != FILEBROWSER_SELECT_FILE_SUBSYSTEM)
         str_list = file_archive_get_file_list(path, info->exts);
      else if (subsystem && subsystem_current_count > 0)
         str_list  = file_archive_get_file_list(path, subsystem->roms[content_get_subsystem_rom_id()].valid_extensions);
   }
   else if (!string_is_empty(path))
   {
      if (filebrowser_types == FILEBROWSER_SELECT_FILE_SUBSYSTEM)
      {
         if (subsystem && subsystem_current_count > 0 && content_get_subsystem_rom_id() < subsystem->num_roms)
            str_list = dir_list_new(path,
                  (filter_ext && info) ? subsystem->roms[content_get_subsystem_rom_id()].valid_extensions : NULL,
                  true, settings->bools.show_hidden_files, true, false);
      }
      else
         str_list = dir_list_new(path,
               (filter_ext && info) ? info->exts : NULL,
               true, settings->bools.show_hidden_files, true, false);
   }

   switch (filebrowser_types)
   {
      case FILEBROWSER_SCAN_DIR:
#ifdef HAVE_LIBRETRODB
         if (info)
            menu_entries_prepend(info->list,
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SCAN_THIS_DIRECTORY),
                  msg_hash_to_str(MENU_ENUM_LABEL_SCAN_THIS_DIRECTORY),
                  MENU_ENUM_LABEL_SCAN_THIS_DIRECTORY,
                  FILE_TYPE_SCAN_DIRECTORY, 0 ,0);
#endif
         break;
      case FILEBROWSER_SELECT_DIR:
         if (info)
            menu_entries_prepend(info->list,
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_USE_THIS_DIRECTORY),
                  msg_hash_to_str(MENU_ENUM_LABEL_USE_THIS_DIRECTORY),
                  MENU_ENUM_LABEL_USE_THIS_DIRECTORY,
                  FILE_TYPE_USE_DIRECTORY, 0 ,0);
         break;
      default:
         break;
   }

   if (!str_list)
   {
      const char *str = path_is_compressed
         ? msg_hash_to_str(MENU_ENUM_LABEL_VALUE_UNABLE_TO_READ_COMPRESSED_FILE)
         : msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DIRECTORY_NOT_FOUND);

      if (info)
         menu_entries_append_enum(info->list, str, "",
               MENU_ENUM_LABEL_VALUE_DIRECTORY_NOT_FOUND, 0, 0, 0);
      goto end;
   }

   dir_list_sort(str_list, true);

   list_size = str_list->size;

   if (list_size == 0)
   {
      string_list_free(str_list);
      str_list = NULL;
   }
   else
   {
      for (i = 0; i < list_size; i++)
      {
         char label[64];
         bool is_dir                   = false;
         enum msg_hash_enums enum_idx  = MSG_UNKNOWN;
         enum msg_file_type file_type  = FILE_TYPE_NONE;
         const char *path              = str_list->elems[i].data;

         label[0] = '\0';

         switch (str_list->elems[i].attr.i)
         {
            case RARCH_DIRECTORY:
               file_type = FILE_TYPE_DIRECTORY;
               break;
            case RARCH_COMPRESSED_ARCHIVE:
               file_type = FILE_TYPE_CARCHIVE;
               break;
            case RARCH_COMPRESSED_FILE_IN_ARCHIVE:
               file_type = FILE_TYPE_IN_CARCHIVE;
               break;
            case RARCH_PLAIN_FILE:
            default:
               if (filebrowser_types == FILEBROWSER_SELECT_FONT)
                  file_type = FILE_TYPE_FONT;
               else
                  file_type = (enum msg_file_type)info->type_default;
               switch (type)
               {
                  /* in case of deferred_core_list we have to interpret
                   * every archive as an archive to disallow instant loading
                   */
                  case DISPLAYLIST_CORES_DETECTED:
                     if (path_is_compressed_file(path))
                        file_type = FILE_TYPE_CARCHIVE;
                     break;
                  default:
                     break;
               }
               break;
         }

         is_dir = (file_type == FILE_TYPE_DIRECTORY);

         if (!is_dir)
         {
            if (filebrowser_types == FILEBROWSER_SELECT_DIR)
               continue;
            if (filebrowser_types == FILEBROWSER_SCAN_DIR)
               continue;
         }

         /* Need to preserve slash first time. */

         if (!string_is_empty(path) && !path_is_compressed)
            path = path_basename(path);

         if (filebrowser_types == FILEBROWSER_SELECT_COLLECTION)
         {
            if (is_dir)
               file_type = FILE_TYPE_DIRECTORY;
            else
               file_type = FILE_TYPE_PLAYLIST_COLLECTION;
         }

         if (!is_dir && path_is_media_type(path) == RARCH_CONTENT_MUSIC)
            file_type = FILE_TYPE_MUSIC;
         else if (!is_dir &&
               (settings->bools.multimedia_builtin_mediaplayer_enable ||
                settings->bools.multimedia_builtin_imageviewer_enable))
         {
            switch (path_is_media_type(path))
            {
               case RARCH_CONTENT_MOVIE:
#if defined(HAVE_FFMPEG) || defined(HAVE_MPV)
                  if (settings->bools.multimedia_builtin_mediaplayer_enable)
                     file_type = FILE_TYPE_MOVIE;
#endif
                  break;
               case RARCH_CONTENT_IMAGE:
#ifdef HAVE_IMAGEVIEWER
                  if (settings->bools.multimedia_builtin_imageviewer_enable
                        && type != DISPLAYLIST_IMAGES)
                     file_type = FILE_TYPE_IMAGEVIEWER;
                  else
                     file_type = FILE_TYPE_IMAGE;
#endif
                  if (filebrowser_types == FILEBROWSER_SELECT_IMAGE)
                     file_type = FILE_TYPE_IMAGE;
                  break;
               default:
                  break;
            }
         }

         switch (file_type)
         {
            case FILE_TYPE_PLAIN:
#if 0
               enum_idx = MENU_ENUM_LABEL_FILE_BROWSER_PLAIN_FILE;
#endif
               files_count++;
               break;
            case FILE_TYPE_MOVIE:
               enum_idx = MENU_ENUM_LABEL_FILE_BROWSER_MOVIE_OPEN;
               files_count++;
               break;
            case FILE_TYPE_MUSIC:
               enum_idx = MENU_ENUM_LABEL_FILE_BROWSER_MUSIC_OPEN;
               files_count++;
               break;
            case FILE_TYPE_IMAGE:
               enum_idx = MENU_ENUM_LABEL_FILE_BROWSER_IMAGE;
               files_count++;
               break;
            case FILE_TYPE_IMAGEVIEWER:
               enum_idx = MENU_ENUM_LABEL_FILE_BROWSER_IMAGE_OPEN_WITH_VIEWER;
               files_count++;
               break;
            case FILE_TYPE_DIRECTORY:
               enum_idx = MENU_ENUM_LABEL_FILE_BROWSER_DIRECTORY;
               dirs_count++;
               break;
            default:
               break;
         }

         items_found++;
         menu_entries_append_enum(info->list, path, label,
               enum_idx,
               file_type, 0, 0);
      }
   }

   if (str_list && str_list->size > 0)
      string_list_free(str_list);

   if (items_found == 0)
   {
      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_ITEMS),
            msg_hash_to_str(MENU_ENUM_LABEL_NO_ITEMS),
            MENU_ENUM_LABEL_NO_ITEMS,
            MENU_SETTING_NO_ITEM, 0, 0);
   }

end:
   if (info && !path_is_compressed)
      menu_entries_prepend(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PARENT_DIRECTORY),
            path,
            MENU_ENUM_LABEL_PARENT_DIRECTORY,
            FILE_TYPE_PARENT_DIRECTORY, 0, 0);
}