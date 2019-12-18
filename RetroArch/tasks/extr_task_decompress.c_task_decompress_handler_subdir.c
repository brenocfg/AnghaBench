#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_9__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_11__ {int /*<<< orphan*/  archive; int /*<<< orphan*/  callback_error; TYPE_9__* userdata; int /*<<< orphan*/  valid_ext; int /*<<< orphan*/  source_file; } ;
typedef  TYPE_2__ decompress_state_t ;
struct TYPE_12__ {int /*<<< orphan*/  archive_path; TYPE_2__* dec; } ;

/* Variables and functions */
 int file_archive_parse_file_iterate (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  file_archive_parse_file_iterate_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_archive_parse_file_progress (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_decompressed_subdir ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_decompress_handler_finished (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ task_get_cancelled (TYPE_1__*) ; 
 int /*<<< orphan*/  task_set_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_set_progress (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void task_decompress_handler_subdir(retro_task_t *task)
{
   int ret;
   bool retdec;
   decompress_state_t *dec = (decompress_state_t*)task->state;

   dec->userdata->dec            = dec;
   strlcpy(dec->userdata->archive_path,
         dec->source_file,
         sizeof(dec->userdata->archive_path));

   ret                     = file_archive_parse_file_iterate(
         &dec->archive,
         &retdec, dec->source_file,
         dec->valid_ext, file_decompressed_subdir, dec->userdata);

   task_set_progress(task,
         file_archive_parse_file_progress(&dec->archive));

   if (task_get_cancelled(task) || ret != 0)
   {
      task_set_error(task, dec->callback_error);
      file_archive_parse_file_iterate_stop(&dec->archive);

      task_decompress_handler_finished(task, dec);
   }
}