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
struct TYPE_4__ {int /*<<< orphan*/  directory_playlist; } ;
struct TYPE_5__ {TYPE_1__ paths; } ;
typedef  TYPE_2__ settings_t ;
typedef  int /*<<< orphan*/  playlist_path ;

/* Variables and functions */
 int PATH_MAX_LENGTH ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  fill_pathname_join (char*,int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_push_pl_thumbnail_download (char const*,char*) ; 

__attribute__((used)) static int action_ok_pl_content_thumbnails(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
#ifdef HAVE_NETWORKING
   settings_t *settings = config_get_ptr();
   char playlist_path[PATH_MAX_LENGTH];

   playlist_path[0] = '\0';

   if (!settings)
      return -1;

   if (string_is_empty(settings->paths.directory_playlist))
      return -1;

   fill_pathname_join(
         playlist_path,
         settings->paths.directory_playlist, label,
         sizeof(playlist_path));

   task_push_pl_thumbnail_download(path, playlist_path);
   return 0;
#else
   return -1;
#endif
}