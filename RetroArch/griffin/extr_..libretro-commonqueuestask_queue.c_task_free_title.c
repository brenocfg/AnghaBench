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
struct TYPE_3__ {int /*<<< orphan*/ * title; } ;
typedef  TYPE_1__ retro_task_t ;

/* Variables and functions */
 int /*<<< orphan*/  SLOCK_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLOCK_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  property_lock ; 

void task_free_title(retro_task_t *task)
{
   SLOCK_LOCK(property_lock);
   if (task->title)
      free(task->title);
   task->title = NULL;
   SLOCK_UNLOCK(property_lock);
}