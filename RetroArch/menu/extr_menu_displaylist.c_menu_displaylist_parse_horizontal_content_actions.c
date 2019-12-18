#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  system ;
struct playlist_entry {char* path; } ;
struct TYPE_12__ {int /*<<< orphan*/  kiosk_mode_enable; scalar_t__ quick_menu_show_download_thumbnails; scalar_t__ quick_menu_show_information; scalar_t__ quick_menu_show_reset_core_association; scalar_t__ quick_menu_show_set_core_association; scalar_t__ quick_menu_show_add_to_favorites; scalar_t__ playlist_entry_rename; } ;
struct TYPE_11__ {scalar_t__ playlist_entry_remove_enable; } ;
struct TYPE_13__ {TYPE_2__ bools; TYPE_1__ uints; } ;
typedef  TYPE_3__ settings_t ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_14__ {unsigned int rpl_entry_selection_ptr; char* deferred_path; } ;
typedef  TYPE_4__ menu_handle_t ;
struct TYPE_15__ {int /*<<< orphan*/  list; } ;
typedef  TYPE_5__ menu_displaylist_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int /*<<< orphan*/  FILE_TYPE_PLAYLIST_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TO_FAVORITES_PLAYLIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TO_MIXER ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_ADD_TO_MIXER_AND_PLAY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DELETE_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_DOWNLOAD_PL_ENTRY_THUMBNAILS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_INFORMATION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_RENAME_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_RESET_CORE_ASSOCIATION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_RUN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_SET_CORE_ASSOCIATION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ADD_TO_FAVORITES_PLAYLIST ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ADD_TO_MIXER ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_ADD_TO_MIXER_AND_PLAY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_DELETE_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_DOWNLOAD_PL_ENTRY_THUMBNAILS ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_INFORMATION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RENAME_ENTRY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RESET_CORE_ASSOCIATION ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_RUN ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_SET_CORE_ASSOCIATION ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION ; 
 int /*<<< orphan*/  MENU_SETTING_ACTION_DELETE_ENTRY ; 
 int PATH_MAX_LENGTH ; 
 scalar_t__ PLAYLIST_ENTRY_REMOVE_ENABLE_ALL ; 
 scalar_t__ PLAYLIST_ENTRY_REMOVE_ENABLE_HIST_FAV ; 
 int /*<<< orphan*/  RARCH_CTL_IS_DUMMY_CORE ; 
 int /*<<< orphan*/  RARCH_PATH_CONTENT ; 
 int /*<<< orphan*/  RARCH_PATH_CORE ; 
 scalar_t__ audio_driver_mixer_extension_supported (char const*) ; 
 TYPE_3__* config_get_ptr () ; 
 char* file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_displaylist_parse_load_content_settings (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  menu_driver_get_thumbnail_system (char*,int) ; 
 int /*<<< orphan*/  menu_entries_append_enum (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 char* path_get (int /*<<< orphan*/ ) ; 
 char* path_get_extension (char*) ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 char* playlist_get_conf_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,unsigned int,struct playlist_entry const**) ; 
 int playlist_index_is_valid (int /*<<< orphan*/ *,unsigned int,char const*,char const*) ; 
 int /*<<< orphan*/  rarch_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char const*) ; 

__attribute__((used)) static int menu_displaylist_parse_horizontal_content_actions(
      menu_handle_t *menu,
      menu_displaylist_info_t *info)
{
   bool content_loaded             = false;
   playlist_t *playlist            = playlist_get_cached();
   settings_t *settings            = config_get_ptr();
   const char *fullpath            = path_get(RARCH_PATH_CONTENT);
   unsigned idx                    = menu->rpl_entry_selection_ptr;
   const struct playlist_entry *entry  = NULL;

   if (playlist)
      playlist_get_index(playlist, idx, &entry);

   content_loaded = !rarch_ctl(RARCH_CTL_IS_DUMMY_CORE, NULL)
         && string_is_equal(menu->deferred_path, fullpath);

   if (content_loaded)
      menu_displaylist_parse_load_content_settings(menu, info);
   else
   {
#ifdef HAVE_AUDIOMIXER
      const char *ext = NULL;

      if (entry && !string_is_empty(entry->path))
         ext = path_get_extension(entry->path);

      if (!string_is_empty(ext) &&
            audio_driver_mixer_extension_supported(ext))
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ADD_TO_MIXER),
               msg_hash_to_str(MENU_ENUM_LABEL_ADD_TO_MIXER),
               MENU_ENUM_LABEL_ADD_TO_MIXER,
               FILE_TYPE_PLAYLIST_ENTRY, 0, idx);

         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ADD_TO_MIXER_AND_PLAY),
               msg_hash_to_str(MENU_ENUM_LABEL_ADD_TO_MIXER_AND_PLAY),
               MENU_ENUM_LABEL_ADD_TO_MIXER_AND_PLAY,
               FILE_TYPE_PLAYLIST_ENTRY, 0, idx);
      }
#endif

      menu_entries_append_enum(info->list,
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RUN),
            msg_hash_to_str(MENU_ENUM_LABEL_RUN),
            MENU_ENUM_LABEL_RUN, FILE_TYPE_PLAYLIST_ENTRY, 0, idx);

      if (settings->bools.playlist_entry_rename &&
            !settings->bools.kiosk_mode_enable)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RENAME_ENTRY),
               msg_hash_to_str(MENU_ENUM_LABEL_RENAME_ENTRY),
               MENU_ENUM_LABEL_RENAME_ENTRY,
               FILE_TYPE_PLAYLIST_ENTRY, 0, idx);

      if (!settings->bools.kiosk_mode_enable)
      {
         bool remove_entry_enabled = false;

         if (settings->uints.playlist_entry_remove_enable == PLAYLIST_ENTRY_REMOVE_ENABLE_ALL)
            remove_entry_enabled = true;
         else if (settings->uints.playlist_entry_remove_enable == PLAYLIST_ENTRY_REMOVE_ENABLE_HIST_FAV)
         {
            char system[PATH_MAX_LENGTH];
            system[0] = '\0';

            menu_driver_get_thumbnail_system(system, sizeof(system));

            if (!string_is_empty(system))
               remove_entry_enabled = string_is_equal(system, "history") ||
                                      string_is_equal(system, "favorites") ||
                                      string_is_equal(system, "images_history") ||
                                      string_is_equal(system, "music_history") ||
                                      string_is_equal(system, "video_history");

            /* An annoyance: if the user navigates to the information menu,
             * then to the database entry, the thumbnail system will be changed.
             * This breaks the above 'remove_entry_enabled' check for the
             * history and favorites playlists. We therefore have to check
             * the playlist file name as well... */
            if (!remove_entry_enabled && settings->bools.quick_menu_show_information)
            {
               const char *playlist_path = playlist_get_conf_path(playlist);

               if (!string_is_empty(playlist_path))
               {
                  const char *playlist_file = path_basename(playlist_path);

                  if (!string_is_empty(playlist_file))
                     remove_entry_enabled = string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_HISTORY)) ||
                                            string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_FAVORITES));
               }
            }
         }

         if (remove_entry_enabled)
            menu_entries_append_enum(info->list,
                  msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DELETE_ENTRY),
                  msg_hash_to_str(MENU_ENUM_LABEL_DELETE_ENTRY),
                  MENU_ENUM_LABEL_DELETE_ENTRY,
                  MENU_SETTING_ACTION_DELETE_ENTRY, 0, 0);
      }

      if (settings->bools.quick_menu_show_add_to_favorites)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ADD_TO_FAVORITES_PLAYLIST),
               msg_hash_to_str(MENU_ENUM_LABEL_ADD_TO_FAVORITES_PLAYLIST),
               MENU_ENUM_LABEL_ADD_TO_FAVORITES_PLAYLIST, FILE_TYPE_PLAYLIST_ENTRY, 0, 0);
      }

      if (settings->bools.quick_menu_show_set_core_association && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SET_CORE_ASSOCIATION),
               msg_hash_to_str(MENU_ENUM_LABEL_SET_CORE_ASSOCIATION),
               MENU_ENUM_LABEL_SET_CORE_ASSOCIATION, FILE_TYPE_PLAYLIST_ENTRY, 0, 0);
      }

      if (settings->bools.quick_menu_show_reset_core_association && !settings->bools.kiosk_mode_enable)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_RESET_CORE_ASSOCIATION),
               msg_hash_to_str(MENU_ENUM_LABEL_RESET_CORE_ASSOCIATION),
               MENU_ENUM_LABEL_RESET_CORE_ASSOCIATION, FILE_TYPE_PLAYLIST_ENTRY, 0, 0);
      }

      if (settings->bools.quick_menu_show_information)
      {
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_INFORMATION),
               msg_hash_to_str(MENU_ENUM_LABEL_INFORMATION),
               MENU_ENUM_LABEL_INFORMATION, MENU_SETTING_ACTION, 0, 0);
      }
   }

#ifdef HAVE_NETWORKING
   if (settings->bools.quick_menu_show_download_thumbnails && !settings->bools.kiosk_mode_enable)
   {
      bool download_enabled = true;

      /* If content is currently running, have to make sure
       * we have a valid playlist to work with */
      if (content_loaded)
      {
         const char *core_path = path_get(RARCH_PATH_CORE);

         download_enabled = false;
         if (!string_is_empty(fullpath) && !string_is_empty(core_path))
            download_enabled = playlist_index_is_valid(
                  playlist, idx, fullpath, core_path);
      }

      if (download_enabled)
      {
         char system[PATH_MAX_LENGTH];

         system[0] = '\0';

         /* Only show 'download thumbnails' on supported playlists */
         download_enabled = false;
         menu_driver_get_thumbnail_system(system, sizeof(system));

         if (!string_is_empty(system))
            download_enabled = !string_is_equal(system, "images_history") &&
                               !string_is_equal(system, "music_history") &&
                               !string_is_equal(system, "video_history");
      }

      if (download_enabled)
         menu_entries_append_enum(info->list,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_DOWNLOAD_PL_ENTRY_THUMBNAILS),
               msg_hash_to_str(MENU_ENUM_LABEL_DOWNLOAD_PL_ENTRY_THUMBNAILS),
               MENU_ENUM_LABEL_DOWNLOAD_PL_ENTRY_THUMBNAILS, FILE_TYPE_PLAYLIST_ENTRY, 0, 0);
   }
#endif

   return 0;
}