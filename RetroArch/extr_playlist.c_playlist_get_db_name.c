#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  conf_path; TYPE_1__* entries; } ;
typedef  TYPE_2__ playlist_t ;
struct TYPE_4__ {char const* db_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_IMAGE_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_MUSIC_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_VIDEO_HISTORY ; 
 int /*<<< orphan*/  file_path_str (int /*<<< orphan*/ ) ; 
 char* path_basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (char const*,int /*<<< orphan*/ ) ; 

void playlist_get_db_name(playlist_t *playlist, size_t idx,
      const char **db_name)
{
   if (!playlist)
      return;

   if (db_name)
   {
      if (!string_is_empty(playlist->entries[idx].db_name))
         *db_name = playlist->entries[idx].db_name;
      else
      {
         const char *conf_path_basename = path_basename(playlist->conf_path);

         /* Only use file basename if this is a 'collection' playlist
          * (i.e. ignore history/favourites) */
         if (!string_is_empty(conf_path_basename)                                                 &&
             !string_is_equal(conf_path_basename, file_path_str(FILE_PATH_CONTENT_FAVORITES))     &&
             !string_is_equal(conf_path_basename, file_path_str(FILE_PATH_CONTENT_HISTORY))       &&
             !string_is_equal(conf_path_basename, file_path_str(FILE_PATH_CONTENT_IMAGE_HISTORY)) &&
             !string_is_equal(conf_path_basename, file_path_str(FILE_PATH_CONTENT_MUSIC_HISTORY)) &&
             !string_is_equal(conf_path_basename, file_path_str(FILE_PATH_CONTENT_VIDEO_HISTORY)))
            *db_name = conf_path_basename;
      }
   }
}