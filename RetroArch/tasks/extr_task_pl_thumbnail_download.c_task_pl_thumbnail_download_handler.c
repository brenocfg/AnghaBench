#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_12__ {int status; int list_size; int list_index; int type_idx; int /*<<< orphan*/ * http_task; int /*<<< orphan*/  thumbnail_path_data; int /*<<< orphan*/  playlist; int /*<<< orphan*/  system; int /*<<< orphan*/  playlist_path; } ;
typedef  TYPE_2__ pl_thumb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  COLLECTION_SIZE ; 
#define  PL_THUMB_BEGIN 131 
#define  PL_THUMB_END 130 
#define  PL_THUMB_ITERATE_ENTRY 129 
#define  PL_THUMB_ITERATE_TYPE 128 
 int /*<<< orphan*/  download_pl_thumbnail (TYPE_2__*) ; 
 int /*<<< orphan*/  free_pl_thumb_handle (TYPE_2__*,int) ; 
 int /*<<< orphan*/  menu_thumbnail_get_label (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  menu_thumbnail_path_init () ; 
 int /*<<< orphan*/  menu_thumbnail_set_content_playlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  menu_thumbnail_set_system (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int playlist_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  task_free_title (TYPE_1__*) ; 
 scalar_t__ task_get_cancelled (TYPE_1__*) ; 
 int /*<<< orphan*/  task_get_finished (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_finished (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_progress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_title (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_pl_thumbnail_download_handler(retro_task_t *task)
{
   pl_thumb_handle_t *pl_thumb = NULL;
   
   if (!task)
      goto task_finished;
   
   pl_thumb = (pl_thumb_handle_t*)task->state;
   
   if (!pl_thumb)
      goto task_finished;
   
   if (task_get_cancelled(task))
      goto task_finished;
   
   switch (pl_thumb->status)
   {
      case PL_THUMB_BEGIN:
         {
            /* Load playlist */
            if (!path_is_valid(pl_thumb->playlist_path))
               goto task_finished;
            
            pl_thumb->playlist = playlist_init(pl_thumb->playlist_path, COLLECTION_SIZE);
            
            if (!pl_thumb->playlist)
               goto task_finished;
            
            pl_thumb->list_size = playlist_size(pl_thumb->playlist);
            
            if (pl_thumb->list_size < 1)
               goto task_finished;
            
            /* Initialise thumbnail path data */
            pl_thumb->thumbnail_path_data = menu_thumbnail_path_init();
            
            if (!pl_thumb->thumbnail_path_data)
               goto task_finished;
            
            if (!menu_thumbnail_set_system(
                  pl_thumb->thumbnail_path_data, pl_thumb->system, pl_thumb->playlist))
               goto task_finished;
            
            /* All good - can start iterating */
            pl_thumb->status = PL_THUMB_ITERATE_ENTRY;
         }
         break;
      case PL_THUMB_ITERATE_ENTRY:
         {
            /* Set current thumbnail content */
            if (menu_thumbnail_set_content_playlist(
                  pl_thumb->thumbnail_path_data, pl_thumb->playlist, pl_thumb->list_index))
            {
               const char *label = NULL;
               
               /* Update progress display */
               task_free_title(task);
               if (menu_thumbnail_get_label(pl_thumb->thumbnail_path_data, &label))
                  task_set_title(task, strdup(label));
               else
                  task_set_title(task, strdup(""));
               task_set_progress(task, (pl_thumb->list_index * 100) / pl_thumb->list_size);
               
               /* Start iterating over thumbnail type */
               pl_thumb->type_idx = 1;
               pl_thumb->status = PL_THUMB_ITERATE_TYPE;
            }
            else
            {
               /* Current playlist entry is broken - advance to
                * the next one */
               pl_thumb->list_index++;
               if (pl_thumb->list_index >= pl_thumb->list_size)
                  pl_thumb->status = PL_THUMB_END;
            }
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
               /* Time to move on to the next entry */
               pl_thumb->list_index++;
               if (pl_thumb->list_index < pl_thumb->list_size)
                  pl_thumb->status = PL_THUMB_ITERATE_ENTRY;
               else
                  pl_thumb->status = PL_THUMB_END;
               break;
            }
            
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
   
   free_pl_thumb_handle(pl_thumb, true);
}