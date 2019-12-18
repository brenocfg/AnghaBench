#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  finished; int /*<<< orphan*/  progress; } ;
typedef  TYPE_1__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_display_server_set_window_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void http_transfer_progress_cb(retro_task_t *task)
{
#ifdef RARCH_INTERNAL
   if (task)
      video_display_server_set_window_progress(task->progress, task->finished);
#endif
}