#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* data; scalar_t__ undo_save; struct TYPE_9__* file; } ;
typedef  TYPE_1__ save_task_state_t ;
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_10__ {TYPE_1__* data; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  intfstream_close (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ task_get_cancelled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_get_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  task_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_finished (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ undo_save_buf ; 

__attribute__((used)) static void task_save_handler_finished(retro_task_t *task,
      save_task_state_t *state)
{
   save_task_state_t *task_data = NULL;

   task_set_finished(task, true);

   intfstream_close(state->file);
   free(state->file);

   if (!task_get_error(task) && task_get_cancelled(task))
      task_set_error(task, strdup("Task canceled"));

   task_data = (save_task_state_t*)calloc(1, sizeof(*task_data));
   memcpy(task_data, state, sizeof(*state));

   task_set_data(task, task_data);

   if (state->data)
   {
      if (state->undo_save && state->data == undo_save_buf.data)
         undo_save_buf.data = NULL;
      free(state->data);
      state->data = NULL;
   }

   free(state);
}