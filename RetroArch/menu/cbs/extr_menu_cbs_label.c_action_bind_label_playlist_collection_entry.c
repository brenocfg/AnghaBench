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
typedef  int /*<<< orphan*/  playlist_name ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_FAVORITES_TAB ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_HISTORY_TAB ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char const*) ; 
 int /*<<< orphan*/  path_get_extension (char const*) ; 
 int /*<<< orphan*/  path_remove_extension (char*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ string_is_equal_noncase (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static int action_bind_label_playlist_collection_entry(
      file_list_t *list,
      unsigned type, unsigned i,
      const char *label, const char *path,
      char *s, size_t len)
{
   const char *playlist_file = NULL;

   if (string_is_empty(path))
      return 0;

   playlist_file = path_basename(path);

   if (string_is_empty(playlist_file))
      return 0;

   if (string_is_equal_noncase(path_get_extension(playlist_file),
            "lpl"))
   {
      /* Handle content history */
      if (string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_HISTORY)))
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_HISTORY_TAB), len);
      /* Handle favourites */
      else if (string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_FAVORITES)))
         strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_FAVORITES_TAB), len);
      /* Handle collection playlists */
      else
      {
         char playlist_name[PATH_MAX_LENGTH];

         playlist_name[0] = '\0';

         strlcpy(playlist_name, playlist_file, sizeof(playlist_name));
         path_remove_extension(playlist_name);

         strlcpy(s, playlist_name, len);
      }
   }
   /* This should never happen, but if it does just set
    * the label to the file name (it's better than nothing...) */
   else
      strlcpy(s, playlist_file, len);

   return 0;
}