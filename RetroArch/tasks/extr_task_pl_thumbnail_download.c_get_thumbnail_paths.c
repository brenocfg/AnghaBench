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
typedef  int /*<<< orphan*/  tmp_buf ;
typedef  int /*<<< orphan*/  raw_url ;
struct TYPE_3__ {char* dir_thumbnails; int /*<<< orphan*/  thumbnail_path_data; int /*<<< orphan*/  type_idx; } ;
typedef  TYPE_1__ pl_thumb_handle_t ;
typedef  int /*<<< orphan*/  content_dir ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CORE_THUMBNAILS_URL ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_pathname_join (char*,char*,char const*,size_t) ; 
 int /*<<< orphan*/  menu_thumbnail_get_content_dir (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  menu_thumbnail_get_db_name (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_get_img_name (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_get_sub_directory (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_get_system (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  net_http_urlencode_full (char*,char*,size_t) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool get_thumbnail_paths(
   pl_thumb_handle_t *pl_thumb,
   char *path, size_t path_size,
   char *url, size_t url_size)
{
   const char *system      = NULL;
   const char *db_name     = NULL;
   const char *img_name    = NULL;
   const char *sub_dir     = NULL;
   const char *system_name = NULL;
   char content_dir[PATH_MAX_LENGTH];
   char raw_url[2048];
   char tmp_buf[PATH_MAX_LENGTH];
   
   content_dir[0] = '\0';
   raw_url[0]     = '\0';
   tmp_buf[0]     = '\0';
   
   if (!pl_thumb->thumbnail_path_data)
      return false;
   
   if (string_is_empty(pl_thumb->dir_thumbnails))
      return false;
   
   /* Extract required strings */
   menu_thumbnail_get_system(pl_thumb->thumbnail_path_data, &system);
   menu_thumbnail_get_db_name(pl_thumb->thumbnail_path_data, &db_name);
   if (!menu_thumbnail_get_img_name(pl_thumb->thumbnail_path_data, &img_name))
      return false;
   if (!menu_thumbnail_get_sub_directory(pl_thumb->type_idx, &sub_dir))
      return false;
   
   /* Dermine system name */
   if (string_is_empty(db_name))
   {
      if (string_is_empty(system))
         return false;
      
      /* If this is a content history or favorites playlist
       * then the current 'path_data->system' string is
       * meaningless. In this case, we fall back to the
       * content directory name */
      if (string_is_equal(system, "history") ||
          string_is_equal(system, "favorites"))
      {
         if (!menu_thumbnail_get_content_dir(
               pl_thumb->thumbnail_path_data, content_dir, sizeof(content_dir)))
            return false;
         
         system_name = content_dir;
      }
      else
         system_name = system;
   }
   else
      system_name = db_name;
   
   /* Generate local path */
   fill_pathname_join(path, pl_thumb->dir_thumbnails,
         system_name, path_size);
   fill_pathname_join(tmp_buf, path, sub_dir, sizeof(tmp_buf));
   fill_pathname_join(path, tmp_buf, img_name, path_size);
   
   if (string_is_empty(path))
      return false;
   
   /* Generate remote path */
   strlcpy(raw_url, file_path_str(FILE_PATH_CORE_THUMBNAILS_URL), sizeof(raw_url));
   strlcat(raw_url, "/", sizeof(raw_url));
   strlcat(raw_url, system_name, sizeof(raw_url));
   strlcat(raw_url, "/", sizeof(raw_url));
   strlcat(raw_url, sub_dir, sizeof(raw_url));
   strlcat(raw_url, "/", sizeof(raw_url));
   strlcat(raw_url, img_name, sizeof(raw_url));
   
   if (string_is_empty(raw_url))
      return false;
   
   net_http_urlencode_full(url, raw_url, url_size);
   
   if (string_is_empty(url))
      return false;
   
   return true;
}