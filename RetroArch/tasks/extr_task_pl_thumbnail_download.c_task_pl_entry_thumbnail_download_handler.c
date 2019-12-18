#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_11__ {int status; int right_thumbnail_exists; int left_thumbnail_exists; int type_idx; int /*<<< orphan*/ * http_task; int /*<<< orphan*/  thumbnail_path_data; int /*<<< orphan*/  list_index; int /*<<< orphan*/  playlist; int /*<<< orphan*/  system; } ;
typedef  TYPE_2__ pl_thumb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MENU_THUMBNAIL_LEFT ; 
 int /*<<< orphan*/  MENU_THUMBNAIL_RIGHT ; 
#define  PL_THUMB_BEGIN 130 
#define  PL_THUMB_END 129 
#define  PL_THUMB_ITERATE_TYPE 128 
 int /*<<< orphan*/  download_pl_thumbnail (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_thumbnail_get_label (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_path_init () ; 
 int /*<<< orphan*/  menu_thumbnail_set_content_playlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_thumbnail_set_system (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_thumbnail_update_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* path_is_valid (char const*) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  task_free_title (TYPE_1__*) ; 
 scalar_t__ task_get_cancelled (TYPE_1__*) ; 
 int /*<<< orphan*/  task_get_finished (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_finished (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_progress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_title (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_pl_entry_thumbnail_download_handler(retro_task_t *task)
{
   pl_thumb_handle_t *pl_thumb = NULL;
   
   if (!task)
      return;
   
   pl_thumb = (pl_thumb_handle_t*)task->state;
   
   if (!pl_thumb)
      goto task_finished;
   
   if (task_get_cancelled(task))
      goto task_finished;
   
   switch (pl_thumb->status)
   {
      case PL_THUMB_BEGIN:
         {
            const char *label                = NULL;
            const char *right_thumbnail_path = NULL;
            const char *left_thumbnail_path  = NULL;
            
            /* Initialise thumbnail path data */
            pl_thumb->thumbnail_path_data = menu_thumbnail_path_init();
            
            if (!pl_thumb->thumbnail_path_data)
               goto task_finished;
            
            if (!menu_thumbnail_set_system(
                  pl_thumb->thumbnail_path_data, pl_thumb->system, pl_thumb->playlist))
               goto task_finished;
            
            if (!menu_thumbnail_set_content_playlist(
                  pl_thumb->thumbnail_path_data, pl_thumb->playlist, pl_thumb->list_index))
               goto task_finished;
            
            /* Check whether current right/left thumbnails
             * already exist (required for menu refresh callback) */
            pl_thumb->right_thumbnail_exists = false;
            if (menu_thumbnail_update_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT))
               if (menu_thumbnail_get_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_RIGHT, &right_thumbnail_path))
                  pl_thumb->right_thumbnail_exists = path_is_valid(right_thumbnail_path);
            
            pl_thumb->left_thumbnail_exists = false;
            if (menu_thumbnail_update_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_LEFT))
               if (menu_thumbnail_get_path(pl_thumb->thumbnail_path_data, MENU_THUMBNAIL_LEFT, &left_thumbnail_path))
                  pl_thumb->left_thumbnail_exists = path_is_valid(left_thumbnail_path);
            
            /* Set task title */
            task_free_title(task);
            if (menu_thumbnail_get_label(pl_thumb->thumbnail_path_data, &label))
               task_set_title(task, strdup(label));
            else
               task_set_title(task, strdup(""));
            task_set_progress(task, 0);
            
            /* All good - can start iterating */
            pl_thumb->status = PL_THUMB_ITERATE_TYPE;
         }
         break;
      case PL_THUMB_ITERATE_TYPE:
         {
            /* Ensure that we only enqueue one transfer
             * at a time... */
            if (pl_thumb->http_task)
            {
               if (task_get_finished(pl_thumb->http_task))
                  pl_thumb->http_task = NULL;
               else
                  break;
            }
            
            /* Check whether all thumbnail types have been processed */
            if (pl_thumb->type_idx > 3)
            {
               pl_thumb->status = PL_THUMB_END;
               break;
            }
            
            /* Update progress */
            task_set_progress(task, ((pl_thumb->type_idx - 1) * 100) / 3);
            
            /* Download current thumbnail */
            if (pl_thumb)
               download_pl_thumbnail(pl_thumb);
            
            /* Increment thumbnail type */
            pl_thumb->type_idx++;
         }
         break;
      case PL_THUMB_END:
      default:
         task_set_progress(task, 100);
         goto task_finished;
   }
   
   return;
   
task_finished:
   
   if (task)
      task_set_finished(task, true);
}