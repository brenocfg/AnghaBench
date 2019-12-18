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
typedef  int /*<<< orphan*/  task_title ;
struct playlist_entry {char* label; char* path; char* core_path; char* core_name; int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
typedef  int /*<<< orphan*/  playlist_t ;
struct TYPE_11__ {int status; int list_size; int list_index; char* playlist_name; int /*<<< orphan*/  playlist_path; int /*<<< orphan*/  playlist; } ;
typedef  TYPE_2__ pl_manager_handle_t ;
typedef  int /*<<< orphan*/  entry_name ;

/* Variables and functions */
 int /*<<< orphan*/  COLLECTION_SIZE ; 
 int /*<<< orphan*/  MSG_PLAYLIST_MANAGER_CORES_RESET ; 
 int /*<<< orphan*/  MSG_PLAYLIST_MANAGER_RESETTING_CORES ; 
 int PATH_MAX_LENGTH ; 
#define  PL_MANAGER_BEGIN 130 
#define  PL_MANAGER_END 129 
#define  PL_MANAGER_ITERATE_ENTRY 128 
 int /*<<< orphan*/  fill_pathname_base_noext (char*,char*,int) ; 
 int /*<<< orphan*/  free_pl_manager_handle (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_free_cached () ; 
 int /*<<< orphan*/ * playlist_get_cached () ; 
 int /*<<< orphan*/  playlist_get_conf_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  playlist_get_index (int /*<<< orphan*/ ,int,struct playlist_entry const**) ; 
 int /*<<< orphan*/  playlist_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_init_cached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int playlist_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  playlist_update (int /*<<< orphan*/ ,int,struct playlist_entry*) ; 
 int /*<<< orphan*/  playlist_write_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  string_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_free_title (TYPE_1__*) ; 
 scalar_t__ task_get_cancelled (TYPE_1__*) ; 
 int /*<<< orphan*/  task_set_finished (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_progress (TYPE_1__*,int) ; 
 int /*<<< orphan*/  task_set_title (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_pl_manager_reset_cores_handler(retro_task_t *task)
{
   pl_manager_handle_t *pl_manager = NULL;
   
   if (!task)
      goto task_finished;
   
   pl_manager = (pl_manager_handle_t*)task->state;
   
   if (!pl_manager)
      goto task_finished;
   
   if (task_get_cancelled(task))
      goto task_finished;
   
   switch (pl_manager->status)
   {
      case PL_MANAGER_BEGIN:
         {
            /* Load playlist */
            if (!path_is_valid(pl_manager->playlist_path))
               goto task_finished;
            
            pl_manager->playlist = playlist_init(pl_manager->playlist_path, COLLECTION_SIZE);
            
            if (!pl_manager->playlist)
               goto task_finished;
            
            pl_manager->list_size = playlist_size(pl_manager->playlist);
            
            if (pl_manager->list_size < 1)
               goto task_finished;
            
            /* All good - can start iterating */
            pl_manager->status = PL_MANAGER_ITERATE_ENTRY;
         }
         break;
      case PL_MANAGER_ITERATE_ENTRY:
         {
            const struct playlist_entry *entry = NULL;
            
            /* Get current entry */
            playlist_get_index(
                  pl_manager->playlist, pl_manager->list_index, &entry);
            
            if (entry)
            {
               struct playlist_entry update_entry = {0};
               char task_title[PATH_MAX_LENGTH];
               char detect_string[PATH_MAX_LENGTH];
               
               task_title[0]    = '\0';
               detect_string[0] = '\0';
               
               /* Update progress display */
               task_free_title(task);
               
               strlcpy(
                     task_title, msg_hash_to_str(MSG_PLAYLIST_MANAGER_RESETTING_CORES),
                     sizeof(task_title));
               
               if (!string_is_empty(entry->label))
                  strlcat(task_title, entry->label, sizeof(task_title));
               else if (!string_is_empty(entry->path))
               {
                  char entry_name[PATH_MAX_LENGTH];
                  entry_name[0] = '\0';
                  
                  fill_pathname_base_noext(entry_name, entry->path, sizeof(entry_name));
                  strlcat(task_title, entry_name, sizeof(task_title));
               }
               
               task_set_title(task, strdup(task_title));
               task_set_progress(task, (pl_manager->list_index * 100) / pl_manager->list_size);
               
               /* Reset core association */
               detect_string[0] = 'D';
               detect_string[1] = 'E';
               detect_string[2] = 'T';
               detect_string[3] = 'E';
               detect_string[4] = 'C';
               detect_string[5] = 'T';
               detect_string[6] = '\0';
               
               update_entry.core_path = detect_string;
               update_entry.core_name = detect_string;
               
               playlist_update(
                     pl_manager->playlist, pl_manager->list_index, &update_entry);
            }
            
            /* Increment entry index */
            pl_manager->list_index++;
            if (pl_manager->list_index >= pl_manager->list_size)
               pl_manager->status = PL_MANAGER_END;
         }
         break;
      case PL_MANAGER_END:
         {
            playlist_t *cached_playlist = playlist_get_cached();
            char task_title[PATH_MAX_LENGTH];
            
            task_title[0] = '\0';
            
            /* Save playlist changes to disk */
            playlist_write_file(pl_manager->playlist);
            
            /* If this is the currently cached playlist, then
             * it must be re-cached (otherwise changes will be
             * lost if the currently cached playlist is saved
             * to disk for any reason...) */
            if (cached_playlist)
            {
               if (string_is_equal(pl_manager->playlist_path, playlist_get_conf_path(cached_playlist)))
               {
                  playlist_free_cached();
                  playlist_init_cached(pl_manager->playlist_path, COLLECTION_SIZE);
               }
            }
            
            /* Update progress display */
            task_free_title(task);
            
            strlcpy(
                  task_title, msg_hash_to_str(MSG_PLAYLIST_MANAGER_CORES_RESET),
                  sizeof(task_title));
            strlcat(task_title, pl_manager->playlist_name, sizeof(task_title));
            
            task_set_title(task, strdup(task_title));
         }
         /* fall-through */
      default:
         task_set_progress(task, 100);
         goto task_finished;
   }
   
   return;
   
task_finished:
   
   if (task)
      task_set_finished(task, true);
   
   free_pl_manager_handle(pl_manager);
}