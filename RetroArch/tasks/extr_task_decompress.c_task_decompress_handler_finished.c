#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  retro_task_t ;
struct TYPE_6__ {TYPE_2__* source_file; } ;
typedef  TYPE_1__ decompress_task_data_t ;
struct TYPE_7__ {struct TYPE_7__* target_dir; struct TYPE_7__* userdata; struct TYPE_7__* valid_ext; struct TYPE_7__* subdir; struct TYPE_7__* source_file; } ;
typedef  TYPE_2__ decompress_state_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ task_get_cancelled (int /*<<< orphan*/ *) ; 
 scalar_t__ task_get_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  task_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_finished (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void task_decompress_handler_finished(retro_task_t *task,
      decompress_state_t *dec)
{
   task_set_finished(task, true);

   if (!task_get_error(task) && task_get_cancelled(task))
      task_set_error(task, strdup("Task canceled"));

   if (task_get_error(task))
      free(dec->source_file);
   else
   {
      decompress_task_data_t *data =
         (decompress_task_data_t*)calloc(1, sizeof(*data));

      data->source_file = dec->source_file;
      task_set_data(task, data);
   }

   if (dec->subdir)
      free(dec->subdir);
   if (dec->valid_ext)
      free(dec->valid_ext);
   if (dec->userdata)
      free(dec->userdata);
   free(dec->target_dir);
   free(dec);
}