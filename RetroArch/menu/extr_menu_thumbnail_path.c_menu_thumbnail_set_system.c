#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_3__ {char* right_path; char* left_path; char* system; void* playlist_left_mode; void* playlist_right_mode; } ;
typedef  TYPE_1__ menu_thumbnail_path_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_LEFT ; 
 void* PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_RIGHT ; 
 char const* file_path_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 char* path_remove_extension (char*) ; 
 char* playlist_get_conf_path (int /*<<< orphan*/ *) ; 
 void* playlist_get_thumbnail_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int string_is_equal (char const*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

bool menu_thumbnail_set_system(menu_thumbnail_path_data_t *path_data,
      const char *system, playlist_t *playlist)
{
   if (!path_data)
      return false;
   
   /* When system is updated, must regenerate right/left
    * thumbnail paths */
   path_data->right_path[0] = '\0';
   path_data->left_path[0] = '\0';
   
   /* 'Reset' path_data system string */
   path_data->system[0] = '\0';
   
   /* Must also reset playlist thumbnail display modes */
   path_data->playlist_right_mode = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   path_data->playlist_left_mode  = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   
   if (string_is_empty(system))
      return false;
   
   /* Hack: There is only one MAME thumbnail repo,
    * so filter any input starting with 'MAME...' */
   if (strncmp(system, "MAME", 4) == 0)
      strlcpy(path_data->system, "MAME", sizeof(path_data->system));
   else
      strlcpy(path_data->system, system, sizeof(path_data->system));
   
   /* Addendum: Now that we have per-playlist thumbnail display
    * modes, we must extract them here - otherwise
    * menu_thumbnail_is_enabled() will go out of sync */
   if (playlist)
   {
      const char *playlist_path = playlist_get_conf_path(playlist);
      const char *playlist_file = NULL;
      bool playlist_valid       = false;
      
      /* Note: This is not considered an error
       * (just means that input playlist is ignored) */
      if (string_is_empty(playlist_path))
         return true;
      
      playlist_file = path_basename(playlist_path);
      
      /* Note: This is not considered an error
       * (just means that input playlist is ignored) */
      if (string_is_empty(playlist_file))
         return true;
      
      /* Check for history/favourites playlists */
      playlist_valid =
            (string_is_equal(system, "history") &&
             string_is_equal(playlist_file,
                file_path_str(FILE_PATH_CONTENT_HISTORY))) ||
            (string_is_equal(system, "favorites") &&
             string_is_equal(playlist_file,
                file_path_str(FILE_PATH_CONTENT_FAVORITES)));
      
      if (!playlist_valid)
      {
         /* This means we have to work a little harder
          * i.e. check whether the cached playlist file
          * matches the database name */
         char *playlist_name = NULL;
         char tmp[PATH_MAX_LENGTH];
         
         tmp[0] = '\0';
         
         strlcpy(tmp, playlist_file, sizeof(tmp));
         playlist_name  = path_remove_extension(tmp);
         playlist_valid = string_is_equal(playlist_name, system);
      }
      
      /* If we have a valid playlist, extract thumbnail modes */
      if (playlist_valid)
      {
         path_data->playlist_right_mode =
               playlist_get_thumbnail_mode(playlist, PLAYLIST_THUMBNAIL_RIGHT);
         path_data->playlist_left_mode =
               playlist_get_thumbnail_mode(playlist, PLAYLIST_THUMBNAIL_LEFT);
      }
   }
   
   return true;
}