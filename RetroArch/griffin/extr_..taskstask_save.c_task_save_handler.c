#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
struct TYPE_13__ {char* path; int size; int written; scalar_t__ state_slot; scalar_t__ undo_save; scalar_t__ data; scalar_t__ file; } ;
typedef  TYPE_1__ save_task_state_t ;
struct TYPE_14__ {scalar_t__ state; } ;
typedef  TYPE_2__ retro_task_t ;
typedef  int /*<<< orphan*/  new_msg ;
typedef  int /*<<< orphan*/  err ;
struct TYPE_15__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_FAILED_TO_SAVE_STATE_TO ; 
 int /*<<< orphan*/  MSG_FAILED_TO_UNDO_SAVE_STATE ; 
 int /*<<< orphan*/  MSG_RESTORED_OLD_SAVE_STATE ; 
 int /*<<< orphan*/  MSG_SAVED_STATE_TO_SLOT ; 
 int /*<<< orphan*/  MSG_SAVED_STATE_TO_SLOT_AUTO ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_HINT_NONE ; 
 int /*<<< orphan*/  RETRO_VFS_FILE_ACCESS_WRITE ; 
 int /*<<< orphan*/  SAVE_STATE_CHUNK ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_serialized_data (char*,int) ; 
 scalar_t__ intfstream_open_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intfstream_write (scalar_t__,int /*<<< orphan*/ *,int) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__,...) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  task_free_title (TYPE_2__*) ; 
 scalar_t__ task_get_cancelled (TYPE_2__*) ; 
 int /*<<< orphan*/  task_get_mute (TYPE_2__*) ; 
 int /*<<< orphan*/  task_save_handler_finished (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  task_set_error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  task_set_progress (TYPE_2__*,float) ; 
 int /*<<< orphan*/  task_set_title (TYPE_2__*,char*) ; 
 TYPE_3__ undo_save_buf ; 

__attribute__((used)) static void task_save_handler(retro_task_t *task)
{
   int written;
   ssize_t remaining;
   save_task_state_t *state = (save_task_state_t*)task->state;

   if (!state->file)
   {
      state->file   = intfstream_open_file(
            state->path, RETRO_VFS_FILE_ACCESS_WRITE,
            RETRO_VFS_FILE_ACCESS_HINT_NONE);

      if (!state->file)
         return;
   }

   if (!state->data)
      state->data  = get_serialized_data(state->path, state->size);

   remaining       = MIN(state->size - state->written, SAVE_STATE_CHUNK);

   if (state->data)
      written      = (int)intfstream_write(state->file,
         (uint8_t*)state->data + state->written, remaining);
   else
      written      = 0;

   state->written += written;

   task_set_progress(task, (state->written / (float)state->size) * 100);

   if (task_get_cancelled(task) || written != remaining)
   {
      char err[8192];

      err[0] = '\0';

      if (state->undo_save)
      {
         RARCH_ERR("%s \"%s\".\n",
            msg_hash_to_str(MSG_FAILED_TO_UNDO_SAVE_STATE),
            undo_save_buf.path);

         snprintf(err, sizeof(err), "%s \"%s\".",
                  msg_hash_to_str(MSG_FAILED_TO_UNDO_SAVE_STATE),
                  "RAM");
      }
      else
         snprintf(err, sizeof(err),
               "%s %s",
               msg_hash_to_str(MSG_FAILED_TO_SAVE_STATE_TO), state->path);

      task_set_error(task, strdup(err));
      task_save_handler_finished(task, state);
      return;
   }

   if (state->written == state->size)
   {
      char       *msg      = NULL;

      task_free_title(task);

      if (state->undo_save)
         msg = strdup(msg_hash_to_str(MSG_RESTORED_OLD_SAVE_STATE));
      else if (state->state_slot < 0)
         msg = strdup(msg_hash_to_str(MSG_SAVED_STATE_TO_SLOT_AUTO));
      else
      {
         char new_msg[128];
         new_msg[0] = '\0';

         snprintf(new_msg, sizeof(new_msg), msg_hash_to_str(MSG_SAVED_STATE_TO_SLOT),
               state->state_slot);
         msg = strdup(new_msg);
      }

      if (!task_get_mute(task) && msg)
      {
         task_set_title(task, msg);
         msg = NULL;
      }

      task_save_handler_finished(task, state);

      if (!string_is_empty(msg))
         free(msg);

      return;
   }
}