#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  show_hidden_files; int /*<<< orphan*/  automatically_add_content_to_playlist; } ;
struct TYPE_5__ {int /*<<< orphan*/  path_content_database; int /*<<< orphan*/  directory_playlist; } ;
struct TYPE_7__ {TYPE_2__ bools; TYPE_1__ paths; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  handle_dbscan_finished ; 
 int /*<<< orphan*/  task_push_dbscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void content_add_to_playlist(const char *path)
{
#ifdef HAVE_LIBRETRODB
   settings_t *settings = config_get_ptr();
   if (!settings || !settings->bools.automatically_add_content_to_playlist)
      return;
   task_push_dbscan(
         settings->paths.directory_playlist,
         settings->paths.path_content_database,
         path, false,
         settings->bools.show_hidden_files,
         handle_dbscan_finished);
#endif
}