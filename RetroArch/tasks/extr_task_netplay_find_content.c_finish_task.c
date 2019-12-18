#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  task_free_title (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_finished (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  task_set_progress (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  task_set_title (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void finish_task(retro_task_t *task, const char *title)
{
   task_set_progress(task, 100);
   task_free_title(task);
   task_set_title(task, strdup(title));
   task_set_finished(task, true);
}