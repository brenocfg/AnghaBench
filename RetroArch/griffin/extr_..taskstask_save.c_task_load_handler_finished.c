#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* file; } ;
typedef  TYPE_1__ save_task_state_t ;
typedef  int /*<<< orphan*/  retro_task_t ;
typedef  int /*<<< orphan*/  load_task_data_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  intfstream_close (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ task_get_cancelled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_get_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_finished (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void task_load_handler_finished(retro_task_t *task,
      save_task_state_t *state)
{
   load_task_data_t *task_data = NULL;

   task_set_finished(task, true);

   if (state->file)
   {
      intfstream_close(state->file);
      free(state->file);
   }

   if (!task_get_error(task) && task_get_cancelled(task))
      task_set_error(task, strdup("Task canceled"));

   task_data = (load_task_data_t*)calloc(1, sizeof(*task_data));

   if (!task_data)
      return;

   memcpy(task_data, state, sizeof(*task_data));

   task_set_data(task, task_data);

   free(state);
}