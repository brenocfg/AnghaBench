#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {void* userdata; int /*<<< orphan*/  func; } ;
typedef  TYPE_2__ task_finder_data_t ;
struct TYPE_11__ {char const* directory_thumbnails; } ;
struct TYPE_13__ {TYPE_1__ paths; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_14__ {int alternative_look; int type_idx; int overwrite; int /*<<< orphan*/  status; scalar_t__ list_index; scalar_t__ list_size; int /*<<< orphan*/ * http_task; int /*<<< orphan*/ * thumbnail_path_data; int /*<<< orphan*/ * playlist; void* dir_thumbnails; void* playlist_path; void* system; scalar_t__ progress; void* title; struct TYPE_14__* state; int /*<<< orphan*/  handler; } ;
typedef  TYPE_4__ retro_task_t ;
typedef  TYPE_4__ pl_thumb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_PATH_CONTENT_FAVORITES ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_IMAGE_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_MUSIC_HISTORY ; 
 int /*<<< orphan*/  FILE_PATH_CONTENT_VIDEO_HISTORY ; 
 int /*<<< orphan*/  PL_THUMB_BEGIN ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 char* file_path_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 char* path_basename (char const*) ; 
 void* strdup (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 TYPE_4__* task_init () ; 
 int /*<<< orphan*/  task_pl_thumbnail_download_handler ; 
 int /*<<< orphan*/  task_pl_thumbnail_finder ; 
 scalar_t__ task_queue_find (TYPE_2__*) ; 
 int /*<<< orphan*/  task_queue_push (TYPE_4__*) ; 

bool task_push_pl_thumbnail_download(
      const char *system, const char *playlist_path)
{
   task_finder_data_t find_data;
   settings_t *settings          = config_get_ptr();
   retro_task_t *task            = task_init();
   pl_thumb_handle_t *pl_thumb   = (pl_thumb_handle_t*)calloc(1, sizeof(pl_thumb_handle_t));
   const char *playlist_file     = path_basename(playlist_path);
   
   /* Sanity check */
   if (!settings || !task || !pl_thumb)
      goto error;
   
   if (string_is_empty(system) ||
       string_is_empty(playlist_path) ||
       string_is_empty(playlist_file) ||
       string_is_empty(settings->paths.directory_thumbnails))
      goto error;
   
   /* Only parse supported playlist types */
   if (string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_HISTORY)) ||
       string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_FAVORITES)) ||
       string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_MUSIC_HISTORY)) ||
       string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_VIDEO_HISTORY)) ||
       string_is_equal(playlist_file, file_path_str(FILE_PATH_CONTENT_IMAGE_HISTORY)) ||
       string_is_equal(system, "history") ||
       string_is_equal(system, "favorites") ||
       string_is_equal(system, "images_history"))
      goto error;
   
   /* Concurrent download of thumbnails for the same
    * playlist is not allowed */
   find_data.func                = task_pl_thumbnail_finder;
   find_data.userdata            = (void*)playlist_path;
   
   if (task_queue_find(&find_data))
      goto error;
   
   /* Configure task */
   task->handler                 = task_pl_thumbnail_download_handler;
   task->state                   = pl_thumb;
   task->title                   = strdup(system);
   task->alternative_look        = true;
   task->progress                = 0;
   
   /* Configure handle */
   pl_thumb->system              = strdup(system);
   pl_thumb->playlist_path       = strdup(playlist_path);
   pl_thumb->dir_thumbnails      = strdup(settings->paths.directory_thumbnails);
   pl_thumb->playlist            = NULL;
   pl_thumb->thumbnail_path_data = NULL;
   pl_thumb->http_task           = NULL;
   pl_thumb->list_size           = 0;
   pl_thumb->list_index          = 0;
   pl_thumb->type_idx            = 1;
   pl_thumb->overwrite           = false;
   pl_thumb->status              = PL_THUMB_BEGIN;
   
   task_queue_push(task);
   
   return true;
   
error:
   
   if (task)
   {
      free(task);
      task = NULL;
   }
   
   if (pl_thumb)
   {
      free(pl_thumb);
      pl_thumb = NULL;
   }
   
   return false;
}