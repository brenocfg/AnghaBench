#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp_buf ;
struct playlist_entry {char* path; char* label; char* core_name; char* db_name; } ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_4__ {char* right_path; char* left_path; char* content_path; char* content_label; char* content_core_name; char* content_db_name; char* content_img; void* playlist_left_mode; void* playlist_right_mode; } ;
typedef  TYPE_1__ menu_thumbnail_path_data_t ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_LEFT ; 
 void* PLAYLIST_THUMBNAIL_MODE_DEFAULT ; 
 int /*<<< orphan*/  PLAYLIST_THUMBNAIL_RIGHT ; 
 int /*<<< orphan*/  fill_content_img (TYPE_1__*) ; 
 int /*<<< orphan*/  fill_short_pathname_representation (char*,char const*,int) ; 
 char* path_remove_extension (char*) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ *,size_t,struct playlist_entry const**) ; 
 size_t playlist_get_size (int /*<<< orphan*/ *) ; 
 void* playlist_get_thumbnail_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

bool menu_thumbnail_set_content_playlist(menu_thumbnail_path_data_t *path_data, playlist_t *playlist, size_t idx)
{
   const char *content_path  = NULL;
   const char *content_label = NULL;
   const char *core_name     = NULL;
   const char *db_name       = NULL;
   const struct playlist_entry *entry = NULL;
   
   if (!path_data)
      return false;
   
   /* When content is updated, must regenerate right/left
    * thumbnail paths */
   path_data->right_path[0]        = '\0';
   path_data->left_path[0]         = '\0';
   
   /* 'Reset' path_data content strings */
   path_data->content_path[0]      = '\0';
   path_data->content_label[0]     = '\0';
   path_data->content_core_name[0] = '\0';
   path_data->content_db_name[0]   = '\0';
   path_data->content_img[0]       = '\0';
   
   /* Must also reset playlist thumbnail display modes */
   path_data->playlist_right_mode  = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   path_data->playlist_left_mode   = PLAYLIST_THUMBNAIL_MODE_DEFAULT;
   
   if (!playlist)
      return false;
   
   if (idx >= playlist_get_size(playlist))
      return false;
   
   /* Read playlist values */
   playlist_get_index(playlist, idx, &entry);

   content_path  = entry->path;
   content_label = entry->label;
   core_name     = entry->core_name;
   db_name       = entry->db_name;

   /* Content without a path is invalid by definition */
   if (string_is_empty(content_path))
      return false;
   
   /* Cache content path
    * (This is required for imageviewer, history and favourites content) */
   strlcpy(path_data->content_path,
            content_path, sizeof(path_data->content_path));
   
   /* Cache core name
    * (This is required for imageviewer content) */
   if (!string_is_empty(core_name))
      strlcpy(path_data->content_core_name,
            core_name, sizeof(path_data->content_core_name));
   
   /* Get content label */
   if (!string_is_empty(content_label))
      strlcpy(path_data->content_label,
            content_label, sizeof(path_data->content_label));
   else
      fill_short_pathname_representation(path_data->content_label,
            content_path, sizeof(path_data->content_label));
   
   /* Determine content image name */
   fill_content_img(path_data);
   
   /* Redundant error check... */
   if (string_is_empty(path_data->content_img))
      return false;
   
   /* Thumbnail image name is done -> now check if
    * per-content database name is defined */
   if (!string_is_empty(db_name))
   {
      /* Hack: There is only one MAME thumbnail repo,
       * so filter any input starting with 'MAME...' */
      if (strncmp(db_name, "MAME", 4) == 0)
         strlcpy(path_data->content_db_name, "MAME",
               sizeof(path_data->content_db_name));
      else
      {
         char *db_name_no_ext = NULL;
         char tmp_buf[PATH_MAX_LENGTH];
         tmp_buf[0] = '\0';
         
         /* Remove .lpl extension
          * > path_remove_extension() requires a char * (not const)
          *   so have to use a temporary buffer... */
         strlcpy(tmp_buf, db_name, sizeof(tmp_buf));
         db_name_no_ext = path_remove_extension(tmp_buf);
         
         if (!string_is_empty(db_name_no_ext))
            strlcpy(path_data->content_db_name,
                  db_name_no_ext, sizeof(path_data->content_db_name));
         else
            strlcpy(path_data->content_db_name,
                  tmp_buf, sizeof(path_data->content_db_name));
      }
   }
   
   /* Playlist entry is valid -> it is now 'safe' to
    * extract any remaining playlist metadata
    * (i.e. thumbnail display modes) */
   path_data->playlist_right_mode =
         playlist_get_thumbnail_mode(playlist, PLAYLIST_THUMBNAIL_RIGHT);
   path_data->playlist_left_mode =
         playlist_get_thumbnail_mode(playlist, PLAYLIST_THUMBNAIL_LEFT);
   
   return true;
}