#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  scan_without_core_match; } ;
struct TYPE_10__ {TYPE_1__ bools; } ;
typedef  TYPE_2__ settings_t ;
struct TYPE_11__ {int alternative_look; int show_hidden_files; int is_directory; void* content_database_path; int /*<<< orphan*/ * playlist_directory; void* fullpath; int /*<<< orphan*/  scan_without_core_match; int /*<<< orphan*/  progress_cb; void* title; int /*<<< orphan*/  callback; struct TYPE_11__* state; int /*<<< orphan*/  handler; } ;
typedef  TYPE_3__ retro_task_t ;
typedef  int /*<<< orphan*/  retro_task_callback_t ;
typedef  TYPE_3__ db_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PREPARING_FOR_CONTENT_SCAN ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_2__* config_get_ptr () ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 char const* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  task_database_handler ; 
 int /*<<< orphan*/  task_database_progress_cb ; 
 TYPE_3__* task_init () ; 
 int /*<<< orphan*/  task_queue_push (TYPE_3__*) ; 

bool task_push_dbscan(
      const char *playlist_directory,
      const char *content_database,
      const char *fullpath,
      bool directory,
      bool db_dir_show_hidden_files,
      retro_task_callback_t cb)
{
   retro_task_t *t      = task_init();
#ifdef RARCH_INTERNAL
   settings_t *settings = config_get_ptr();
#endif
   db_handle_t *db      = (db_handle_t*)calloc(1, sizeof(db_handle_t));

   if (!t || !db)
      goto error;

   t->handler                = task_database_handler;
   t->state                  = db;
   t->callback               = cb;
   t->title                  = strdup(msg_hash_to_str(MSG_PREPARING_FOR_CONTENT_SCAN));
   t->alternative_look       = true;

#ifdef RARCH_INTERNAL
   t->progress_cb            = task_database_progress_cb;
   db->scan_without_core_match = settings->bools.scan_without_core_match;
#endif
   db->show_hidden_files     = db_dir_show_hidden_files;
   db->is_directory          = directory;
   db->playlist_directory    = NULL;
   db->fullpath              = strdup(fullpath);
   db->playlist_directory    = strdup(playlist_directory);
   db->content_database_path = strdup(content_database);

   task_queue_push(t);

   return true;

error:
   if (t)
      free(t);
   if (db)
      free(db);
   return false;
}